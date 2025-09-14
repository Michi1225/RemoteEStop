/*
 * CC2500.cpp
 *
 *  Created on: Jan 10, 2025
 *      Author: Michi
 */
#include "CC2500.h"


/*
 * @brief  Update the state from the MARCSTATE register
 * @retval Returns the current FSM state
 */
CC2500_State CC2500::read_fsm_state()
{
	std::array<uint8_t,2> txData = {CC2500_REG_MARCSTATE, CC2500_Strobe_SNOP};
	std::array<uint8_t,2> rxData = {0, 0};

	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData.data(), rxData.data(), 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_SET);

	this->state = (CC2500_State)rxData.at(1);

    return this->state; 
}

/*
 * @brief	Perform a FSM state transition
 * @param	strobe: Command strobe as defined at P.57.
 * @retval	State right after state transition
 *
 * Note: The state right after the transition might not be the target state.
 * 		 E.g. when transitioning from RX to TX, the FSM has a transition state
 * 		 TXRX_SETTLING.
 */
CC2500_State CC2500::state_transition(CC2500_Strobe strobe)
{
	std::array<uint8_t,2> txData = {strobe, CC2500_Strobe_SNOP};
	std::array<uint8_t,2> rxData = {0, 0};

	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData.data(), rxData.data(), 2, HAL_MAX_DELAY);
	txData.at(0) = CC2500_REG_MARCSTATE;
	HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData.data(), rxData.data(), 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_SET);

	this->state = (CC2500_State)rxData.at(1);

    return this->state; 
}

/*
 * @brief 	Initialize all CC2500 registers to the default values
 * @retval	0, if all SPI transmitions were successful
 *
 */
uint8_t CC2500::init()
{
	uint8_t txData[2] = {0};
	uint8_t rxData[2] = {0};
	uint8_t errorcode = 0;

	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_RESET);

	//wake up device
	txData[0] = CC2500_Strobe_SNOP;
	txData[1] = CC2500_Strobe_SNOP;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if(errorcode != 0) return errorcode;

	//reset device
	txData[0] = CC2500_Strobe_SRES;
	txData[1] = CC2500_Strobe_SNOP;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if(errorcode != 0) return errorcode;

	while(HAL_GPIO_ReadPin(SPI_MISO_RF_GPIO_Port, SPI_MISO_RF_Pin)){} //after SRES strobe, wait for SO to go low (see P.24. in CC2500 datasheet)


	txData[0] = CC2500_REG_IOCFG2;
	txData[1] = CC2500_VAL_IOCFG2;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if(errorcode != 0) return errorcode;


	txData[0] = CC2500_REG_IOCFG1;
	txData[1] = CC2500_VAL_IOCFG1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if(errorcode != 0) return errorcode;


	txData[0] = CC2500_REG_IOCFG0;
	txData[1] = CC2500_VAL_IOCFG0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if(errorcode != 0) return errorcode;


	txData[0] = CC2500_REG_FIFOTHR;
	txData[1] = CC2500_VAL_FIFOTHR;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if(errorcode != 0) return errorcode;


	txData[0] = CC2500_REG_SYNC1;
	txData[1] = CC2500_VAL_SYNC1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if(errorcode != 0) return errorcode;


	txData[0] = CC2500_REG_SYNC0;
	txData[1] = CC2500_VAL_SYNC0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if(errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_PKTLEN;
	txData[1] = CC2500_VAL_PKTLEN;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_PKTCTRL1;
	txData[1] = CC2500_VAL_PKTCTRL1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_PKTCTRL0;
	txData[1] = CC2500_VAL_PKTCTRL0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_ADDR;
	txData[1] = CC2500_VAL_ADDR;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_CHANNR;
	txData[1] = CC2500_VAL_CHANNR;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FSCTRL1;
	txData[1] = CC2500_VAL_FSCTRL1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FSCTRL0;
	txData[1] = CC2500_VAL_FSCTRL0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FREQ2;
	txData[1] = CC2500_VAL_FREQ2;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FREQ1;
	txData[1] = CC2500_VAL_FREQ1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FREQ0;
	txData[1] = CC2500_VAL_FREQ0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_MDMCFG4;
	txData[1] = CC2500_VAL_MDMCFG4;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_MDMCFG3;
	txData[1] = CC2500_VAL_MDMCFG3;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_MDMCFG2;
	txData[1] = CC2500_VAL_MDMCFG2;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_MDMCFG1;
	txData[1] = CC2500_VAL_MDMCFG1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_MDMCFG0;
	txData[1] = CC2500_VAL_MDMCFG0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_DEVIATN;
	txData[1] = CC2500_VAL_DEVIATN;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_MCSM2;
	txData[1] = CC2500_VAL_MCSM2;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_MCSM1;
	txData[1] = CC2500_VAL_MCSM1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_MCSM0;
	txData[1] = CC2500_VAL_MCSM0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FOCCFG;
	txData[1] = CC2500_VAL_FOCCFG;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_BSCFG;
	txData[1] = CC2500_VAL_BSCFG;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_AGCCTRL2;
	txData[1] = CC2500_VAL_AGCCTRL2;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_AGCCTRL1;
	txData[1] = CC2500_VAL_AGCCTRL1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_AGCCTRL0;
	txData[1] = CC2500_VAL_AGCCTRL0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_WOREVT1;
	txData[1] = CC2500_VAL_WOREVT1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_WOREVT0;
	txData[1] = CC2500_VAL_WOREVT0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_WORCTRL;
	txData[1] = CC2500_VAL_WORCTRL;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FREND1;
	txData[1] = CC2500_VAL_FREND1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FREND0;
	txData[1] = CC2500_VAL_FREND0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FSCAL3;
	txData[1] = CC2500_VAL_FSCAL3;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FSCAL2;
	txData[1] = CC2500_VAL_FSCAL2;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FSCAL1;
	txData[1] = CC2500_VAL_FSCAL1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FSCAL0;
	txData[1] = CC2500_VAL_FSCAL0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_RCCTRL1;
	txData[1] = CC2500_VAL_RCCTRL1;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_RCCTRL0;
	txData[1] = CC2500_VAL_RCCTRL0;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_FSTEST;
	txData[1] = CC2500_VAL_FSTEST;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_PTEST;
	txData[1] = CC2500_VAL_PTEST;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	txData[0] = CC2500_REG_PATABLE;
	txData[1] = CC2500_VAL_PATABLE;
	errorcode = HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData, rxData, 2, HAL_MAX_DELAY);
	if (errorcode != 0) return errorcode;

	//FIXME: CS only goes high if all transmissions are successful...
	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_SET);

	return errorcode;


}


/*
 * @brief 		Read one message from the RX FIFO
 * @param[out]	pRxData: pointer to receive data buffer
 * @retval		Bytes read from the RX FIFO including address and status bytes
 * 
 * NOTE: The function caller is responsible, that enough storage is allocated, and the FIFO is not empty.
 * 		 If fixed packet length is used, the allocated memory must be al least PKTLEN + 2 * APPEND_STATUS.
 * 		 If variable length is used, the allocated memory should be at least MAX_RX_FIFO_LEN + 2 * APPEND_STATUS.
 */
uint8_t CC2500::read_rx_fifo(uint8_t *pRxData)
{
#if !CC2500_VARIABLE_PKTLEN_EN
{
	//Fixed Packet length
	std::array<uint8_t, CC2500_VAL_PKTLEN + 2 * CC2500_APPEND_STATUS + 1> txData;
	txData.fill(CC2500_Strobe_SNOP);
	txData.at(0) = CC2500_BURST_RX;
	
	std::array<uint8_t, CC2500_VAL_PKTLEN + 2 * CC2500_APPEND_STATUS + 1> rxData;


	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData.data(), rxData.data(), CC2500_VAL_PKTLEN + 2 * CC2500_APPEND_STATUS + 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_SET);

	std::memcpy(pRxData, rxData.data() + 1, CC2500_VAL_PKTLEN + 2 * CC2500_APPEND_STATUS); //remove first byte
	return CC2500_VAL_PKTLEN + 2 * CC2500_APPEND_STATUS;
}
#else
{
	std::array<uint8_t, 258> txData;
	txData.fill(CC2500_Strobe_SNOP);
	txData.at(0) = CC2500_BURST_RX;
	
	std::array<uint8_t, 258> rxData;

	std::array<uint8_t, 2> rxBytes;

	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData.data(), rxBytes.data(), 2, HAL_MAX_DELAY); //get packet length
	HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData.data(), rxData.data(), rxBytes.at(1) + 2 * CC2500_APPEND_STATUS + 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_SET);

	std::memcpy(pRxData, rxData.data() + 1, rxBytes.at(1) + 2 * CC2500_APPEND_STATUS); //remove first byte
	return rxBytes.at(1) + 2 * CC2500_APPEND_STATUS;



}
#endif
}


/*
 * @brief  Write one message to the TX FIFO
 * @param  pTxData: pointer to transmit data buffer
 * @retval Number of Bytes transmitted
 *
 * NOTE: The caller of the function is responsible that enough memory is allocated, and no TX
 *       FIFO overflow occurs. When variable packet length is enabled, the first byte in the
 *       transmit data buffer must contain the packet length.
 * */
uint8_t CC2500::write_tx_fifo(uint8_t *pTxData)
{
#if !CC2500_VARIABLE_PKTLEN_EN
	//Fixed Packet length
	std::array<uint8_t, CC2500_VAL_PKTLEN + 1> txData;
	txData.at(0) = CC2500_BURST_TX;
	std::memcpy(txData.data() + 1, pTxData, CC2500_VAL_PKTLEN);
	
	std::array<uint8_t, CC2500_VAL_PKTLEN + 1> rxData;
	
	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData.data(), rxData.data(), CC2500_VAL_PKTLEN + 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_SET);

	return CC2500_VAL_PKTLEN;
#else
	uint8_t len = pTxData[0];
	std::array<uint8_t, 256> txData;
	txData.at(0) = CC2500_BURST_TX;
	std::memcpy(txData.data() + 1, pTxData, len);

	
	std::array<uint8_t, 256> rxData;

	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC2500_SPI_HANDLE, txData.data(), rxData.data(), len + 1, HAL_MAX_DELAY); 
	HAL_GPIO_WritePin(SPI_CS_RF_GPIO_Port, SPI_CS_RF_Pin, GPIO_PIN_SET);

	return len;

#endif
}
