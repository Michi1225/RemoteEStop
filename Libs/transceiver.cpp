#include "transceiver.h"
#include "CC1101.h"
#include "stm32g4xx_hal_gpio.h"

Transceiver::Transceiver(bool isTransmitter) : cc1101()
{
    this->transmitter = isTransmitter;
}

void Transceiver::init()
{

    // Read channel from rotary encoder
    uint8_t channel =   HAL_GPIO_ReadPin(CH0_GPIO_Port, CH0_Pin)
                    | (HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin) << 1)
                    | (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin) << 2)
                    | (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin) << 3);

    channel = 0;


    this->cc1101.addr.ADDR = ADDRESS;
    this->cc1101.channr.CHANR = channel;
    this->cc1101.pktlen.PACKET_LENGTH = PACKET_LEN;
    this->cc1101.pktctrl1.APPEND_STATUS = APPEND_STATUS;

    cc1101.init();

    if(this->transmitter)
    {
        // Configure CC1101 for TX
        CC1101_State state =  cc1101.state_transition(cc1101_strobe_t::CC1101_Strobe_STX);
        HAL_RNG_GenerateRandomNumber(&hrng, &(this->txCounter)); //seed counter with random value
    }
    else
    {
        // Configure CC1101 for RX
        CC1101_State state =  cc1101.state_transition(cc1101_strobe_t::CC1101_Strobe_SRX);
        htim1.Init.Period = VALID_FRAME_TIMEOUT_US - 1;
        HAL_TIM_Base_Start_IT(&htim1);

    }

}

void Transceiver::run()
{
    if(this->transmitter)
    {
        // Transmitter logic here
        switch (ESTOP)
        {
        case true:
            /* code */
            break;
        case false:
            this->xferData[0] = ADDRESS; //first byte is address
            uint32_t cypher = codec::encode32(this->prevCounter);
            memcpy(xferData + 1, &cypher, 4);
            cc1101.write_tx_fifo(xferData);
            ++this->txCounter;
        
            HAL_Delay(TX_PERIOD_MS - 1);
            break;
        }
    }
    else
    {
        // Receiver logic here

        // Clear xferData buffer
        for(size_t i = 0; i < 7; ++i)
        {
            this->xferData[i] = 0;
        }
        uint8_t rssi = cc1101.read_status_reg(cc1101_statusreg_t::CC1101_STATUS_REG_RSSI);
        if(HAL_GPIO_ReadPin(GDO0_GPIO_Port, GDO0_Pin) == GPIO_PIN_RESET) return; //no packet received
        // while(HAL_GPIO_ReadPin(GDO0_GPIO_Port, GDO0_Pin) == GPIO_PIN_RESET){__NOP();} //wait for end of packet
        cc1101.read_rx_fifo(xferData);
        uint32_t cypher = 0;
        memcpy(&cypher, xferData + 1, 4);
        uint32_t rxCount= codec::decode32(cypher);
        int64_t diff = (rxCount - this->prevCounter + (1ULL<<32)) % (1ULL<<32); //handle overflow

        if(this->ESTOP)
        {
            if(diff > 0 && diff <= MAX_LOST_PACKETS)
            {
                // Valid packet received, inccrement valid packet count and reset timeout counter
                this->validPacketCount += 1;
                TIM1->CNT = 0; //reset timer counter
            }
            else
            {
                // Invalid packet received, reset valid packet count
                this->validPacketCount = 0;
            }
            this->prevCounter = rxCount;
            if(this->validPacketCount >= VALID_PACKET_THRESHOLD)
            {
                // Valid packet threshold reached, disable ESTOP
                this->ESTOP = false; //disable ESTOP
                this->validPacketCount = 0;
                HAL_GPIO_WritePin(nWD_RST_GPIO_Port, nWD_RST_Pin, GPIO_PIN_RESET); //reset watchdog
                HAL_Delay(0);
                HAL_GPIO_WritePin(nWD_RST_GPIO_Port, nWD_RST_Pin, GPIO_PIN_SET);
            }            
        }
        else
        {
            if(diff > 0 && diff <= MAX_LOST_PACKETS)
            {
                this->prevCounter = rxCount;
                this->lostPacketCount = 0;
                TIM1->CNT = 0; //reset timer counter
            }
            else
            {
                this->lostPacketCount += 1;
                if(this->lostPacketCount >= MAX_LOST_PACKETS)
                {
                    this->ESTOP = true; //enable ESTOP
                    this->lostPacketCount = 0;
                }
            }
        }
    }
}

void Transceiver::timeout()
{
    if(!this->transmitter)
    {
        // Receiver timeout logic here
        this->validPacketCount = 0;
        this->ESTOP = true;
        TIM1->CNT = 0; //reset timer counter
    }
}
