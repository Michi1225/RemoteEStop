#pragma once

#include <stdint.h>
#include <array>
#include <cstring>
#include "stm32h7xx_hal.h"
#include "main.h"

typedef union 
{
	struct
	{
		uint8_t 			:1;
		uint8_t GDO2_INV	:1;
		uint8_t GDO2_CFG	:6;
	};
	uint8_t raw;	
}cc1101_iocfg2_t;

typedef union 
{
	struct
	{
		uint8_t GDO_DS  	:1;
		uint8_t GDO1_INV	:1;
		uint8_t GDO1_CFG	:6;
	};
	uint8_t raw;
}cc1101_iocfg1_t;

typedef union 
{
	struct
	{
		uint8_t TEMP_SENSOR_ENABLE  	:1;
		uint8_t GDO0_INV				:1;
		uint8_t GDO0_CFG				:6;
	};
	uint8_t raw;
}cc1101_iocfg0_t;

typedef union 
{
	struct
	{
		uint8_t 					:1;
		uint8_t ADC_RETENTION		:1;
		uint8_t CLOSE_IN_RX			:2;
		uint8_t FIFO_THR			:4;
	};
	uint8_t raw;
}cc1101_fifothr_t;

typedef union 
{
	struct
	{
		uint8_t SYNC			:8;
	};
	uint8_t raw;
}cc1101_sync1_t;

typedef union 
{
	struct
	{
		uint8_t SYNC			:8;
	};
	uint8_t raw;
}cc1101_sync0_t;

typedef union 
{
	struct
	{
		uint8_t PACKET_LENGTH	:8;
	};
	uint8_t raw;
}cc1101_pktlen_t;

typedef union 
{
	struct
	{
		uint8_t PQT 			:3;
		uint8_t 				:1;
		uint8_t CRC_AUTOFLUSH	:1;
		uint8_t APPEND_STATUS	:1;
		uint8_t ADR_CHK			:2;
	};
	uint8_t raw;
}cc1101_pktctrl1_t;

typedef union 
{
	struct
	{
		uint8_t 				:1;
		uint8_t WHITE_DATA		:1;
		uint8_t PKT_FORMAT		:2;
		uint8_t 				:1;
		uint8_t CRC_EN			:1;
		uint8_t LENGTH_CONFIG	:2;
	};
	uint8_t raw;
}cc1101_pktctrl0_t;

typedef union 
{
	struct
	{
		uint8_t ADDR			:8;
	};
	uint8_t raw;
}cc1101_addr_t;

typedef union 
{
	struct
	{
		uint8_t CHANR			:8;
	};
	uint8_t raw;
}cc1101_channr_t;

typedef union 
{
	struct
	{
		uint8_t 				:3;
		uint8_t FREQ_IF			:5;
	};
	uint8_t raw;
}cc1101_fsctrl1_t;

typedef union 
{
	struct
	{
		uint8_t FREQOFF			:8;
	};
	uint8_t raw;
}cc1101_fsctrl0_t;

typedef union 
{
	struct
	{
		uint8_t 				:2;
		uint8_t FREQ			:6;
	};
	uint8_t raw;
}cc1101_freq2_t;

typedef union 
{
	struct
	{
		uint8_t FREQ			:8;
	};
	uint8_t raw;
}cc1101_freq1_t;

typedef union 
{
	struct
	{
		uint8_t FREQ			:8;
	};
	uint8_t raw;
}cc1101_freq0_t;

typedef union 
{
	struct
	{
		uint8_t CHANBW_E		:2;
		uint8_t CHANBW_M		:2;
		uint8_t DRATE_E			:4;
	};
	uint8_t raw;
}cc1101_mdmcfg4_t;

typedef union 
{
	struct
	{
		uint8_t DRATE_M			:8;
	};
	uint8_t raw;
}cc1101_mdmcfg3_t;

typedef union 
{
	struct
	{
		uint8_t DEM_DCFILT_OFF	:1;
		uint8_t MOD_FORMAT		:3;
		uint8_t MANCHESTER_EN	:1;
		uint8_t SYNC_MODE		:3;
	};
	uint8_t raw;
}cc1101_mdmcfg2_t;

typedef union 
{
	struct
	{
		uint8_t FEC_EN 			:1;
		uint8_t NUM_PREAMBLE	:3;
		uint8_t 				:2;
		uint8_t CHANSPC_E		:2;
	};
	uint8_t raw;
}cc1101_mdmcfg1_t;

typedef union 
{
	struct
	{
		uint8_t CHANSPC_M		:8;
	};
	uint8_t raw;
}cc1101_mdmcfg0_t;

typedef union 
{
	struct
	{
		uint8_t 			 	:1;
		uint8_t DEVIATION_E		:3;
		uint8_t 			 	:1;
		uint8_t DEVIATION_M		:3;
	};
	uint8_t raw;
}cc1101_deviatn_t;

typedef union 
{
	struct
	{
		uint8_t 				:3;
		uint8_t RX_TIME_RSSI	:1;
		uint8_t RX_TIME_QUAL	:1;
		uint8_t RX_TIME			:3;
	};
	uint8_t raw;
}cc1101_mcsm2_t;

typedef union 
{
	struct
	{
		uint8_t 				:2;
		uint8_t CCA_MODE 		:2;
		uint8_t RXOFF_MODE		:2;
		uint8_t TXOFF_MODE		:2;
	};
	uint8_t raw;
}cc1101_mcsm1_t;

typedef union 
{
	struct
	{
		uint8_t 				:2;
		uint8_t FS_AUTOCAL		:2;
		uint8_t PO_TIMEOUT		:2;
		uint8_t PIN_CTRL_EN		:1;
		uint8_t XOSC_FORCE_ON	:1;
	};
	uint8_t raw;
}cc1101_mcsm0_t;

typedef union 
{
	struct
	{
		uint8_t 				:2;
		uint8_t FOC_BS_CS_GATE	:1;
		uint8_t FOC_PRE_K		:2;
		uint8_t FOC_POST_K		:1;
		uint8_t FOC_LIMIT		:2;
	};
	uint8_t raw;
}cc1101_foccfg_t;

typedef union 
{
	struct
	{
		uint8_t BS_PRE_KI		:2;
		uint8_t BS_PRE_KP		:2;
		uint8_t BC_POST_KI		:1;
		uint8_t BS_POST_KP		:1;
		uint8_t BS_LIMIT		:2;
	};
	uint8_t raw;
}cc1101_bscfg_t;

typedef union 
{
	struct
	{
		uint8_t MAX_DVGA_GAIN	:2;
		uint8_t MAX_LNA_GAIN	:3;
		uint8_t MAGN_TARGET		:3;
	};
	uint8_t raw;
}cc1101_agcctrl2_t;

typedef union 
{
	struct
	{
		uint8_t 						:1;
		uint8_t AGC_LNA_PRIORITY 		:1;
		uint8_t CARRIER_SENSE_REL_THR 	:2;
		uint8_t CARRIER_SENSE_ABS_THR 	:4;
	};
	uint8_t raw;
}cc1101_agcctrl1_t;

typedef union 
{
	struct
	{
		uint8_t HYST_LEVEL		:2;
		uint8_t WAIT_TIME		:2;
		uint8_t AGC_FREEZE		:1;
		uint8_t FILTER_LENGTH	:2;
	};
	uint8_t raw;
}cc1101_agcctrl0_t;

typedef union 
{
	struct
	{
		uint8_t EVENT0			:8;
	};
	uint8_t raw;
}cc1101_worevt1_t;

typedef union 
{
	struct
	{
		uint8_t EVENT0			:8;
	};
	uint8_t raw;
}cc1101_worevt0_t;

typedef union 
{
	struct
	{
		uint8_t RC_PD			:1;
		uint8_t EVENT1 			:3;
		uint8_t RX_CAL			:1;
		uint8_t 				:1;
		uint8_t WOR_RES			:2;
	};
	uint8_t raw;
}cc1101_worctrl_t;

typedef union 
{
	struct
	{
		uint8_t LNA_CURRENT				:2;
		uint8_t LNA2MIX_CURRENT			:2;
		uint8_t LODIV_BUF_CURRENT_RX	:2;
		uint8_t MIX_CURRENT 			:2;
	};
	uint8_t raw;
}cc1101_frend1_t;

typedef union 
{
	struct
	{
		uint8_t 						:2;
		uint8_t LODIV_BUF_CURRENT_TX	:2;
		uint8_t 						:1;
		uint8_t PA_POWER				:3;
	};
	uint8_t raw;
}cc1101_frend0_t;

typedef union 
{
	struct
	{
		uint8_t FSCAL3_7_6			:2;
		uint8_t CHP_CURR_CAL_EN		:2;
		uint8_t FSCAL3_3_0			:4;
	};
	uint8_t raw;
}cc1101_fscal3_t;

typedef union 
{
	struct
	{
		uint8_t 				:2;
		uint8_t VCO_CORE_H_EN	:1;
		uint8_t FSCAL2			:5;
	};
	uint8_t raw;
}cc1101_fscal2_t;

typedef union 
{
	struct
	{
		uint8_t 				:2;
		uint8_t FSCAL1			:6;
	};
	uint8_t raw;
}cc1101_fscal1_t;

typedef union 
{
	struct
	{
		uint8_t 				:2;
		uint8_t FSCAL0			:6;
	};
	uint8_t raw;
}cc1101_fscal0_t;

typedef union 
{
	struct
	{
		uint8_t 				:1;
		uint8_t RCCTRL1			:7;
	};
	uint8_t raw;
}cc1101_rcctrl1_t;

typedef union 
{
	struct
	{
		uint8_t 				:1;
		uint8_t RCCTRL0			:7;
	};
	uint8_t raw;
}cc1101_rcctrl0_t;

enum cc1101_registers_t
{
	CC2500_REG_IOCFG2		= 0x00,
	CC2500_REG_IOCFG1		= 0x01,
	CC2500_REG_IOCFG0		= 0x02,
	CC2500_REG_FIFOTHR		= 0x03,
	CC2500_REG_SYNC1		= 0x04,
	CC2500_REG_SYNC0		= 0x05,
	CC2500_REG_PKTLEN		= 0x06,
	CC2500_REG_PKTCTRL1		= 0x07,
	CC2500_REG_PKTCTRL0		= 0x08,
	CC2500_REG_ADDR			= 0x09,
	CC2500_REG_CHANNR		= 0x0A,
	CC2500_REG_FSCTRL1		= 0x0B,
	CC2500_REG_FSCTRL0		= 0x0C,
	CC2500_REG_FREQ2		= 0x0D,
	CC2500_REG_FREQ1		= 0x0E,
	CC2500_REG_FREQ0		= 0x0F,
	CC2500_REG_MDMCFG4		= 0x10,
	CC2500_REG_MDMCFG3		= 0x11,
	CC2500_REG_MDMCFG2		= 0x12,
	CC2500_REG_MDMCFG1		= 0x13,
	CC2500_REG_MDMCFG0		= 0x14,
	CC2500_REG_DEVIATN		= 0x15,
	CC2500_REG_MCSM2		= 0x16,
	CC2500_REG_MCSM1		= 0x17,
	CC2500_REG_MCSM0		= 0x18,
	CC2500_REG_FOCCFG		= 0x19,
	CC2500_REG_BSCFG		= 0x1A,
	CC2500_REG_AGCCTRL2		= 0x1B,
	CC2500_REG_AGCCTRL1		= 0x1C,
	CC2500_REG_AGCCTRL0		= 0x1D,
	CC2500_REG_WOREVT1		= 0x1E,
	CC2500_REG_WOREVT0		= 0x1F,
	CC2500_REG_WORCTRL		= 0x20,
	CC2500_REG_FREND1		= 0x21,
	CC2500_REG_FREND0		= 0x22,
	CC2500_REG_FSCAL3		= 0x23,
	CC2500_REG_FSCAL2		= 0x24,
	CC2500_REG_FSCAL1		= 0x25,
	CC2500_REG_FSCAL0		= 0x26,
	CC2500_REG_RCCTRL1		= 0x27,
	CC2500_REG_RCCTRL0		= 0x28
};


#define CC2500_REG_IOCFG2 0x00	//IOCFG2
#define CC2500_VAL_IOCFG2 0x29	//IOCFG2
#define CC2500_REG_IOCFG1 0x01  //IOCFG1
#define CC2500_VAL_IOCFG1 0x2E  //IOCFG1
#define CC2500_REG_IOCFG0 0x02  //IOCFG0
#define CC2500_VAL_IOCFG0 0x01  //IOCFG0 --> RX FIF0 above threshold, de-asserts when empty
#define CC2500_REG_FIFOTHR 0x03   //FIFOTHR
#define CC2500_VAL_FIFOTHR 0x00   //FIFOTHR
#define CC2500_REG_SYNC1 0x04	   //SYNC1
#define CC2500_VAL_SYNC1 0xD3	   //SYNC1
#define CC2500_REG_SYNC0 0x05	   //SYNC0
#define CC2500_VAL_SYNC0 0x91	   //SYNC0
#define CC2500_REG_PKTLEN 0x06	   //PKTLEN
#define CC2500_VAL_PKTLEN 0x03	   //PKTLEN
#define CC2500_REG_PKTCTRL1 0x07  //PKTCTRL1
#define CC2500_VAL_PKTCTRL1 0x05  //PKTCTRL1
#define CC2500_REG_PKTCTRL0 0x08  //PKTCTRL0
#define CC2500_VAL_PKTCTRL0 0x44  //PKTCTRL0
#define CC2500_REG_ADDR 0x09	   //ADDR
#define CC2500_VAL_ADDR 0x01	   //ADDR
#define CC2500_REG_CHANNR 0x0A	   //CHANNR
#define CC2500_VAL_CHANNR 0x00	   //CHANNR
#define CC2500_REG_FSCTRL1 0x0B   //FSCTRL1
#define CC2500_VAL_FSCTRL1 0x10   //FSCTRL1
#define CC2500_REG_FSCTRL0 0x0C   //FSCTRL0
#define CC2500_VAL_FSCTRL0 0x00   //FSCTRL0
#define CC2500_REG_FREQ2 0x0D	   //FREQ2
#define CC2500_VAL_FREQ2 0x5C	   //FREQ2
#define CC2500_REG_FREQ1 0x0E	   //FREQ1
#define CC2500_VAL_FREQ1 0x4E	   //FREQ1
#define CC2500_REG_FREQ0 0x0F	   //FREQ0
#define CC2500_VAL_FREQ0 0xDE	   //FREQ0
#define CC2500_REG_MDMCFG4 0x10   //MDMCFG4
#define CC2500_VAL_MDMCFG4 0x0E   //MDMCFG4
#define CC2500_REG_MDMCFG3 0x11   //MDMCFG3
#define CC2500_VAL_MDMCFG3 0x3B   //MDMCFG3
#define CC2500_REG_MDMCFG2 0x12   //MDMCFG2
#define CC2500_VAL_MDMCFG2 0x73   //MDMCFG2
#define CC2500_REG_MDMCFG1 0x13   //MDMCFG1
#define CC2500_VAL_MDMCFG1 0xA2   //MDMCFG1
#define CC2500_REG_MDMCFG0 0x14   //MDMCFG0
#define CC2500_VAL_MDMCFG0 0xF8   //MDMCFG0
#define CC2500_REG_DEVIATN 0x15   //DEVIATN
#define CC2500_VAL_DEVIATN 0x00   //DEVIATN
#define CC2500_REG_MCSM2 0x16	   //MCSM2
#define CC2500_VAL_MCSM2 0x07	   //MCSM2
#define CC2500_REG_MCSM1 0x17	   //MCSM1
#define CC2500_VAL_MCSM1 0x3E	   //MCSM1
#define CC2500_REG_MCSM0 0x18	   //MCSM0
#define CC2500_VAL_MCSM0 0x18	   //MCSM0
#define CC2500_REG_FOCCFG 0x19	   //FOCCFG
#define CC2500_VAL_FOCCFG 0x1D	   //FOCCFG
#define CC2500_REG_BSCFG 0x1A	   //BSCFG
#define CC2500_VAL_BSCFG 0x1C	   //BSCFG
#define CC2500_REG_AGCCTRL2 0x1B  //AGCCTRL2
#define CC2500_VAL_AGCCTRL2 0xC7  //AGCCTRL2
#define CC2500_REG_AGCCTRL1 0x1C  //AGCCTRL1
#define CC2500_VAL_AGCCTRL1 0x40  //AGCCTRL1
#define CC2500_REG_AGCCTRL0 0x1D  //AGCCTRL0
#define CC2500_VAL_AGCCTRL0 0xB0  //AGCCTRL0
#define CC2500_REG_WOREVT1 0x1E   //WOREVT1
#define CC2500_VAL_WOREVT1 0x87   //WOREVT1
#define CC2500_REG_WOREVT0 0x1F   //WOREVT0
#define CC2500_VAL_WOREVT0 0x6B   //WOREVT0
#define CC2500_REG_WORCTRL 0x20   //WORCTRL
#define CC2500_VAL_WORCTRL 0xF8   //WORCTRL
#define CC2500_REG_FREND1 0x21	   //FREND1
#define CC2500_VAL_FREND1 0xB6	   //FREND1
#define CC2500_REG_FREND0 0x22	   //FREND0
#define CC2500_VAL_FREND0 0x10	   //FREND0
#define CC2500_REG_FSCAL3 0x23	   //FSCAL3
#define CC2500_VAL_FSCAL3 0xEA	   //FSCAL3
#define CC2500_REG_FSCAL2 0x24	   //FSCAL2
#define CC2500_VAL_FSCAL2 0x0A	   //FSCAL2
#define CC2500_REG_FSCAL1 0x25	   //FSCAL1
#define CC2500_VAL_FSCAL1 0x00	   //FSCAL1
#define CC2500_REG_FSCAL0 0x26	   //FSCAL0
#define CC2500_VAL_FSCAL0 0x19	   //FSCAL0
#define CC2500_REG_RCCTRL1 0x27   //RCCTRL1
#define CC2500_VAL_RCCTRL1 0x41   //RCCTRL1
#define CC2500_REG_RCCTRL0 0x28   //RCCTRL0
#define CC2500_VAL_RCCTRL0 0x00   //RCCTRL0
#define CC2500_REG_FSTEST 0x29	   //FSTEST
#define CC2500_VAL_FSTEST 0x59	   //FSTEST
#define CC2500_REG_PTEST 0x2A	   //PTEST
#define CC2500_VAL_PTEST 0x7F	   //PTEST
#define CC2500_REG_AGCTST 0x2B	   //AGCTST
#define CC2500_VAL_AGCTST 0x00	   //AGCTST
#define CC2500_REG_TEST2 0x2C	   //TEST2
#define CC2500_VAL_TEST2 0x00	   //TEST2
#define CC2500_REG_TEST1 0x2D	   //TEST1
#define CC2500_VAL_TEST1 0x00	   //TEST1
#define CC2500_REG_TEST0 0x2E	   //TEST0
#define CC2500_VAL_TEST0 0x00	   //TEST0
#define CC2500_REG_PARTNUM 0x30   //PARTNUM
#define CC2500_VAL_PARTNUM 0x00   //PARTNUM
#define CC2500_REG_VERSION 0x31   //VERSION
#define CC2500_VAL_VERSION 0x00   //VERSION
#define CC2500_REG_FREQEST 0x32   //FREQEST
#define CC2500_VAL_FREQEST 0x00   //FREQEST
#define CC2500_REG_LQI 0x33	   //LQI
#define CC2500_VAL_LQI 0x00	   //LQI
#define CC2500_REG_RSSI 0x34	   //RSSI
#define CC2500_VAL_RSSI 0x00	   //RSSI
#define CC2500_REG_MARCSTATE 0x35 //MARCSTAT
#define CC2500_VAL_MARCSTATE 0x00 //MARCSTAT
#define CC2500_REG_WORTIM1 0x36   //WORTIM1
#define CC2500_VAL_WORTIM1 0x00   //WORTIM1
#define CC2500_REG_WORTIM0 0x37   //WORTIM0
#define CC2500_VAL_WORTIM0 0x00   //WORTIM0
#define CC2500_REG_PKTSTATUS 0x38 //PKTSTATU
#define CC2500_VAL_PKTSTATUS 0x00 //PKTSTATU
#define CC2500_REG_VCO_VC_DAC 0x39//VCO_VC_D
#define CC2500_VAL_VCO_VC_DAC 0x00//VCO_VC_D
#define CC2500_REG_TXBYTES 0x3A   //TXBYTES
#define CC2500_VAL_TXBYTES 0x00   //TXBYTES
#define CC2500_REG_RXBYTES 0x3B   //RXBYTES
#define CC2500_VAL_RXBYTES 0x00   //RXBYTES
#define CC2500_REG_PATABLE 0x3E   //PATABLE
#define CC2500_VAL_PATABLE 0xFF   //PATABLE





#define CC2500_SINGLE_TX 0x3F
#define CC2500_BURST_TX 0x7F
#define CC2500_SINGLE_RX 0xBF
#define CC2500_BURST_RX 0xFF



#define CC2500_VARIABLE_PKTLEN_EN 	(CC2500_VAL_PKTCTRL0 & 0x03)
#define CC2500_ADR_CHK 				((CC2500_VAL_PKTCTRL1 & 0x03) > 0)
#define CC2500_APPEND_STATUS		(CC2500_VAL_PKTCTRL1 & 0x04)

#define CC2500_SPI_HANDLE &hspi2



enum CC2500_State
{
	CC2500_State_SLEEP,
	CC2500_State_IDLE,
	CC2500_State_XOFF,
	CC2500_State_VCOON_MC,
	CC2500_State_REGON_MC,
	CC2500_State_MANCAL,
	CC2500_State_VCOON,
	CC2500_State_REGON,
	CC2500_State_STARTCAL,
	CC2500_State_BWBOOST,
	CC2500_State_FS_LOCK,
	CC2500_State_IFADCON,
	CC2500_State_ENDCAL,
	CC2500_State_RX,
	CC2500_State_RX_END,
	CC2500_State_RX_RST,
	CC2500_State_TXRX_SWITCH,
	CC2500_State_RXFIFO_OVERFLOW,
	CC2500_State_FSTXON,
	CC2500_State_TX,
	CC2500_State_TX_END,
	CC2500_State_RXTX_SWITCH,
	CC2500_State_TXFIFO_UNDERFLOW
};

enum CC2500_Strobe
{
	CC2500_Strobe_SRES = 0x30,
	CC2500_Strobe_SFSTXON,
	CC2500_Strobe_SXOFF,
	CC2500_Strobe_SCAL,
	CC2500_Strobe_SRX,
	CC2500_Strobe_STX,
	CC2500_Strobe_SIDLE,
	CC2500_Strobe_SWOR = 0x38,
	CC2500_Strobe_SPWD,
	CC2500_Strobe_SFRX,
	CC2500_Strobe_SFTX,
	CC2500_Strobe_SWORRST,
	CC2500_Strobe_SNOP,
};

class CC2500
{
private:
    CC2500_State state;

public:
	CC2500_State read_fsm_state();

    CC2500_State state_transition(CC2500_Strobe strobe);

	uint8_t init();

	uint8_t read_rx_fifo(uint8_t *pRxData);

	uint8_t write_tx_fifo(uint8_t *pTxData);





};
