/*
 * CC1101.cpp
 *
 *  Created on: Jan 10, 2025
 *      Author: Michi
 */
#include "CC1101.h"




CC1101::CC1101()
{
	this->state = CC1101_State_IDLE;

	this->iocfg2 = 
	{
		.GDO2_CFG = 0x29,
		.GDO2_INV = 0
	};//Don't care, pin not used

	this->iocfg1 = 
	{
		.GDO1_CFG = 0x2E,	//Tri-state
		.GDO1_INV = 0,		//Active high
		.GDO_DS = 0			//Low drive strength
	};//GDO1 pin used as MISO --> Don't care

	this->iocfg0 = 
	{
		.GDO0_CFG = 0x01,			//Asserts when RX FIFO above threshold, de-asserts when empty
		.GDO0_INV = 0,				//Active high
		.TEMP_SENSOR_ENABLE = 0		//Disable temperature sensor
	};

	this->fifothr = 
	{
		.FIFO_THR = 0x0F,		//1 in TX, 64 in RX
		.CLOSE_IN_RX = 0x00,	//No RX Attenuation
		.ADC_RETENTION = 0		//Only used in Test (I think)
	};

	this->sync1 = 
	{
		.SYNC = 0xD3 			//Sync word high byte
	};

	this->sync0 = 
	{
		.SYNC = 0x91 			//Sync word low byte
	};

	this->pktlen = 
	{
		.PACKET_LENGTH = CC1101_PKT_LEN 		//3 bytes fixed length packets
	};

	this->pktctrl1 = 
	{
		.ADR_CHK = 0x01,								//Address check, no broadcast
		.APPEND_STATUS = CC1101_APPEND_STATUS,			//Append 2 status bytes to the payload
		.CRC_AUTOFLUSH = 0,								//Disable auto flush on CRC error
		.PQT = 0x05									//Preamble quality threshold
	};

	this->pktctrl0 = 
	{
		.LENGTH_CONFIG = 0x00,	//Use PKTLEN register for packet length
		.CRC_EN = 1,			//Enable CRC
		.PKT_FORMAT = 0x00,		//Normal mode
		.WHITE_DATA = 1			//Data whitening disabled
	};

	this->addr = 
	{
		.ADDR = 0x02 			//Device address
	};

	this->channr = 
	{
		.CHANR = 0x00 			//Channel number
	};

	this->fsctrl1 = 
	{
		.FREQ_IF = 0x08 		//Frequency offset for IF, Default value
	};

	this->fsctrl0 = 
	{
		.FREQOFF = 0x00 		//Frequency offset, Default value
	};

	this->freq2 = 
	{
		.FREQ = 0x21 			//Frequency setting, Default value
	};

	this->freq1 = 
	{
		.FREQ = 0x65 			//Frequency setting, Default value
	};

	this->freq0 = 
	{
		.FREQ = 0x6A 			//Frequency setting, Default value
	};

	this->mdmcfg4 = 
	{
		.DRATE_E = 0x0B,		//Data rate exponent, Default value
		.CHANBW_M = 0x01,		//Channel bandwidth mantissa, Default value
		.CHANBW_E = 0x01		//Channel bandwidth exponent, Default value
	};

	this->mdmcfg3 = 
	{
		.DRATE_M = 0xF8			//Data rate mantissa, Default value, results in 115200 Baud/s
	};

	this->mdmcfg2 = 
	{
		.SYNC_MODE = 0x03,		//16/16 sync word bits detected
		.MANCHESTER_EN = 0,		//Manchester disabled
		.MOD_FORMAT = 0x01,		//2-FSK
		.DEM_DCFILT_OFF = 0		//DC filter enabled
	};

	this->mdmcfg1 = 
	{
		.CHANSPC_E = 0x02,		//Default channel spacing exponent
		.NUM_PREAMBLE = 0x07,	//4 bytes preamble
		.FEC_EN = 0				//FEC disabled
	};

	this->mdmcfg0 = 
	{
		.CHANSPC_M = 0xF8		//Default channel spacing mantissa, Yields 20kHz spacing
	};

	this->deviatn = 
	{
		.DEVIATION_M = 0x07,	//Frequency deviation mantissa, Default value
		.DEVIATION_E = 0x04		//Frequency deviation exponent, Default value
	};

	this->mcsm2 = 
	{
		.RX_TIME = 0x07,			//Default RX timeout
		.RX_TIME_QUAL = 0,			//Default RSSI timeout
		.RX_TIME_RSSI = 0			//Default RSSI timeout
	};

	this->mcsm1 = 
	{
		.TXOFF_MODE = 0x02,		//Stay in TX
		.RXOFF_MODE = 0x03,		//Stay in RX
		.CCA_MODE = 0x03		//Clear channel if RSSI below threshold, unless receiving a packet
	};

	this->mcsm0 = 
	{
		.XOSC_FORCE_ON = 0,		//Disable XOSC force on
		.PIN_CTRL_EN = 0,		//Disable pin control
		.PO_TIMEOUT = 0x02,		//2.3 - 2.4 us
		.FS_AUTOCAL = 0x01		//No automatic calibration
	};

	this->foccfg = 
	{
		.FOC_LIMIT = 0x01,		//Default value
		.FOC_POST_K = 0x01,		//Default value
		.FOC_PRE_K = 0x03,		//Default value
		.FOC_BS_CS_GATE = 0x00	//Default value
	};

	this->bscfg = 
	{
		.BS_LIMIT = 0x00,		//Default value
		.BS_POST_KP = 0x01,		//Default value
		.BC_POST_KI = 0x01,		//Default value
		.BS_PRE_KP = 0x01,		//Default value
		.BS_PRE_KI = 0x00		//Default value
	};

	this->agcctrl2 = 
	{
		.MAGN_TARGET = 0x07,	//Default value
		.MAX_LNA_GAIN = 0x00,	//Maximum LNA gain
		.MAX_DVGA_GAIN = 0x03	//All gain stages enabled
	};

	this->agcctrl1 = 
	{
		.CARRIER_SENSE_ABS_THR = 0x00, //Default value
		.CARRIER_SENSE_REL_THR = 0x00, //Default value
		.AGC_LNA_PRIORITY = 0			//Default value
	};

	this->agcctrl0 = 
	{
		.FILTER_LENGTH = 0x02,	//Default value
		.AGC_FREEZE = 0,		//AGC not frozen
		.WAIT_TIME = 0x03,		//Default value
		.HYST_LEVEL = 0x02		//Default value
	};

	this->worevt1 = 
	{
		.EVENT0 = 0x87 			//Default value
	};

	this->worevt0 = 
	{
		.EVENT0 = 0x6B 			//Default value
	};

	this->worctrl = 
	{
		.WOR_RES = 0x00,			//Default value
		.RC_CAL = 0x01,			//Calibrate when going from sleep to RX
		.EVENT1 = 0x07,			//Default value
		.RC_PD = 0x01			//RC oscillator on during sleep
	};

	this->frend1 = 
	{
		.MIX_CURRENT = 0x02,			//Default value
		.LODIV_BUF_CURRENT_RX = 0x01,	//Default value
		.LNA2MIX_CURRENT = 0x03,		//Default value
		.LNA_CURRENT = 0x02			//Default value
	};

	this->frend0 = 
	{
		.PA_POWER = 0x00,				//Max output power
		.LODIV_BUF_CURRENT_TX = 0x01	//Default value
	};

	this->fscal3 = 
	{
		.FSCAL3_3_0 = 0x0A,				//Default value
		.CHP_CURR_CAL_EN = 0x02,		//Default value
		.FSCAL3_7_6 = 0x03 			//Default value
	};

	this->fscal2 = 
	{
		.FSCAL2 = 0x0A, 				//Default value
		.VCO_CORE_H_EN = 1				//Disable high VCO current
	};

	this->fscal1 = 
	{
		.FSCAL1 = 0x00 					//Default value
	};

	this->fscal0 = 
	{
		.FSCAL0 = 0x1F 					//Default value
	};

	this->rcctrl1 = 
	{
		.RCCTRL1 = 0x41 				//Default value
	};

	this->rcctrl0 = 
	{
		.RCCTRL0 = 0x00 				//Default value
	};



}


/*
 * @brief  Update the state from the MARCSTATE register
 * @retval Returns the current FSM state
 */
CC1101_State CC1101::read_fsm_state()
{
	std::array<uint8_t,2> txData = {static_cast<uint8_t>(cc1101_statusreg_t::CC1101_STATUS_REG_MARCSTATE), static_cast<uint8_t>(cc1101_strobe_t::CC1101_Strobe_SNOP)};
	std::array<uint8_t,2> rxData = {0, 0}; 

	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData.data(), rxData.data(), 2, 10);
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_SET);

	this->state = (CC1101_State)(rxData.at(1) & 0x1F);

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
CC1101_State CC1101::state_transition(cc1101_strobe_t strobe)
{
	std::array<uint8_t,2> txData = {static_cast<uint8_t>(strobe), static_cast<uint8_t>(cc1101_strobe_t::CC1101_Strobe_SNOP)};
	std::array<uint8_t,2> rxData = {0, 0};

	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData.data(), rxData.data(), 2, 10);
	txData.at(0) = static_cast<uint8_t>(cc1101_statusreg_t::CC1101_STATUS_REG_MARCSTATE);
	HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData.data(), rxData.data(), 2, 10);
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_SET);

	this->state = (CC1101_State)(rxData.at(1) & 0x1F); //only bits 0-4 are MARCSTATE

    return this->state; 
}

/*
 * @brief 	Initialize all CC1101 registers to the default values
 * @retval	0, if all SPI transmitions were successful
 *
 */
uint8_t CC1101::init()
{
	uint8_t txData[2] = {0};
	uint8_t rxData[2] = {0};
	uint8_t errorcode = 0;

	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_RESET);

	//wake up device
	txData[0] = static_cast<uint8_t>(cc1101_strobe_t::CC1101_Strobe_SNOP);
	txData[1] = static_cast<uint8_t>(cc1101_strobe_t::CC1101_Strobe_SNOP);
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if(errorcode != 0) return errorcode;

	//reset device
	txData[0] = static_cast<uint8_t>(cc1101_strobe_t::CC1101_Strobe_SRES);
	txData[1] = static_cast<uint8_t>(cc1101_strobe_t::CC1101_Strobe_SNOP);
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if(errorcode != 0) return errorcode;

	while(HAL_GPIO_ReadPin(SPI_MISO_RF_GPIO_Port, SPI_MISO_RF_Pin)){} //after SRES strobe, wait for SO to go low (see P.24. in CC1101 datasheet)

	// Write all registers using member variables
	txData[0] = CC1101_REG_IOCFG2;
	txData[1] = this->iocfg2.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if(errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_IOCFG1;
	txData[1] = this->iocfg1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if(errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_IOCFG0;
	txData[1] = this->iocfg0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if(errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FIFOTHR;
	txData[1] = this->fifothr.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if(errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_SYNC1;
	txData[1] = this->sync1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if(errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_SYNC0;
	txData[1] = this->sync0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if(errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_PKTLEN;
	txData[1] = this->pktlen.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_PKTCTRL1;
	txData[1] = this->pktctrl1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_PKTCTRL0;
	txData[1] = this->pktctrl0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_ADDR;
	txData[1] = this->addr.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_CHANNR;
	txData[1] = this->channr.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FSCTRL1;
	txData[1] = this->fsctrl1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FSCTRL0;
	txData[1] = this->fsctrl0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FREQ2;
	txData[1] = this->freq2.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FREQ1;
	txData[1] = this->freq1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FREQ0;
	txData[1] = this->freq0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_MDMCFG4;
	txData[1] = this->mdmcfg4.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_MDMCFG3;
	txData[1] = this->mdmcfg3.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_MDMCFG2;
	txData[1] = this->mdmcfg2.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_MDMCFG1;
	txData[1] = this->mdmcfg1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_MDMCFG0;
	txData[1] = this->mdmcfg0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_DEVIATN;
	txData[1] = this->deviatn.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_MCSM2;
	txData[1] = this->mcsm2.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_MCSM1;
	txData[1] = this->mcsm1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_MCSM0;
	txData[1] = this->mcsm0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FOCCFG;
	txData[1] = this->foccfg.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_BSCFG;
	txData[1] = this->bscfg.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_AGCCTRL2;
	txData[1] = this->agcctrl2.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_AGCCTRL1;
	txData[1] = this->agcctrl1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_AGCCTRL0;
	txData[1] = this->agcctrl0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_WOREVT1;
	txData[1] = this->worevt1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_WOREVT0;
	txData[1] = this->worevt0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_WORCTRL;
	txData[1] = this->worctrl.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FREND1;
	txData[1] = this->frend1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FREND0;
	txData[1] = this->frend0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FSCAL3;
	txData[1] = this->fscal3.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FSCAL2;
	txData[1] = this->fscal2.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FSCAL1;
	txData[1] = this->fscal1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_FSCAL0;
	txData[1] = this->fscal0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_RCCTRL1;
	txData[1] = this->rcctrl1.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	txData[0] = CC1101_REG_RCCTRL0;
	txData[1] = this->rcctrl0.raw;
	errorcode = HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	if (errorcode != 0) return errorcode;

	//FIXME: CS only goes high if all transmissions are successful...
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_SET);

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
uint8_t CC1101::read_rx_fifo(uint8_t *pRxData)
{
#if !CC1101_VARIABLE_PKTLEN_EN
{
	//Fixed Packet length
	std::array<uint8_t, CC1101_PKT_LEN + 2 * CC1101_APPEND_STATUS + 1> txData;
	txData.fill(static_cast<uint8_t>(cc1101_strobe_t::CC1101_Strobe_SNOP));
	txData.at(0) = CC1101_BURST_RX;
	
	std::array<uint8_t, CC1101_PKT_LEN + 2 * CC1101_APPEND_STATUS + 1> rxData;


	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData.data(), rxData.data(), CC1101_PKT_LEN + 2 * CC1101_APPEND_STATUS + 1, 10);
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_SET);

	std::memcpy(pRxData, rxData.data() + 1, CC1101_PKT_LEN + 2 * CC1101_APPEND_STATUS); //remove first byte
	return CC1101_PKT_LEN + 2 * CC1101_APPEND_STATUS;
}
#else
{
	std::array<uint8_t, 258> txData;
	txData.fill(CC1101_Strobe_SNOP);
	txData.at(0) = CC1101_BURST_RX;
	
	std::array<uint8_t, 258> rxData;

	std::array<uint8_t, 2> rxBytes;

	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData.data(), rxBytes.data(), 2, 10); //get packet length
	HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData.data(), rxData.data(), rxBytes.at(1) + 2 * CC1101_APPEND_STATUS + 1, 10);
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_SET);

	std::memcpy(pRxData, rxData.data() + 1, rxBytes.at(1) + 2 * CC1101_APPEND_STATUS); //remove first byte
	return rxBytes.at(1) + 2 * CC1101_APPEND_STATUS;



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
uint8_t CC1101::write_tx_fifo(uint8_t *pTxData)
{
#if !CC1101_VARIABLE_PKTLEN_EN
	//Fixed Packet length
	std::array<uint8_t, CC1101_PKT_LEN + 1> txData;
	txData.at(0) = CC1101_BURST_TX;
	std::memcpy(txData.data() + 1, pTxData, CC1101_PKT_LEN);
	
	std::array<uint8_t, CC1101_PKT_LEN + 1> rxData;
	
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData.data(), rxData.data(), CC1101_PKT_LEN + 1, 10);
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_SET);

	return CC1101_PKT_LEN;
#else
	uint8_t len = pTxData[0];
	std::array<uint8_t, 256> txData;
	txData.at(0) = CC1101_BURST_TX;
	std::memcpy(txData.data() + 1, pTxData, len);

	
	std::array<uint8_t, 256> rxData;

	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData.data(), rxData.data(), len + 1, 10); 
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_SET);

	return len;

#endif
}

uint8_t CC1101::read_status_reg(cc1101_statusreg_t reg)
{
	uint8_t txData[2] = {0};
	uint8_t rxData[2] = {0};
	txData[0] = static_cast<uint8_t>(reg);
	txData[1] = static_cast<uint8_t>(cc1101_strobe_t::CC1101_Strobe_SNOP);
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(CC1101_SPI_HANDLE, txData, rxData, 2, 10);
	HAL_GPIO_WritePin(NCS_GPIO_Port, NCS_Pin, GPIO_PIN_SET);

	return rxData[1];
}

