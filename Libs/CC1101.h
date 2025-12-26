#pragma once

#include <stdint.h>
#include <array>
#include <cstring>
#include "stm32g4xx_hal.h"
#include "main.h"

#define CC1101_PKT_LEN 5

typedef union 
{
	struct
	{
		uint8_t GDO2_CFG	:6;
		uint8_t GDO2_INV	:1;
		uint8_t 			:1;
	};
	uint8_t raw;	
}cc1101_iocfg2_t;

typedef union 
{
	struct
	{
		uint8_t GDO1_CFG	:6;
		uint8_t GDO1_INV	:1;
		uint8_t GDO_DS  	:1;
	};
	uint8_t raw;
}cc1101_iocfg1_t;

typedef union 
{
	struct
	{
		uint8_t GDO0_CFG				:6;
		uint8_t GDO0_INV				:1;
		uint8_t TEMP_SENSOR_ENABLE  	:1;
	};
	uint8_t raw;
}cc1101_iocfg0_t;

typedef union 
{
	struct
	{
		uint8_t FIFO_THR			:4;
		uint8_t CLOSE_IN_RX			:2;
		uint8_t ADC_RETENTION		:1;
		uint8_t 					:1;
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
		uint8_t ADR_CHK			:2;
		uint8_t APPEND_STATUS	:1;
		uint8_t CRC_AUTOFLUSH	:1;
		uint8_t 				:1;
		uint8_t PQT 			:3;
	};
	uint8_t raw;
}cc1101_pktctrl1_t;

typedef union 
{
	struct
	{
		uint8_t LENGTH_CONFIG	:2;
		uint8_t CRC_EN			:1;
		uint8_t 				:1;
		uint8_t PKT_FORMAT		:2;
		uint8_t WHITE_DATA		:1;
		uint8_t 				:1;
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
		uint8_t FREQ_IF			:5;
		uint8_t 				:3;
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
		uint8_t FREQ			:6;
		uint8_t 				:2;
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
		uint8_t DRATE_E			:4;
		uint8_t CHANBW_M		:2;
		uint8_t CHANBW_E		:2;
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
		uint8_t SYNC_MODE		:3;
		uint8_t MANCHESTER_EN	:1;
		uint8_t MOD_FORMAT		:3;
		uint8_t DEM_DCFILT_OFF	:1;
	};
	uint8_t raw;
}cc1101_mdmcfg2_t;

typedef union 
{
	struct
	{
		uint8_t CHANSPC_E		:2;
		uint8_t 				:2;
		uint8_t NUM_PREAMBLE	:3;
		uint8_t FEC_EN 			:1;
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
		uint8_t DEVIATION_M		:3;
		uint8_t 				:1;
		uint8_t DEVIATION_E		:3;
		uint8_t 			 	:1;
	};
	uint8_t raw;
}cc1101_deviatn_t;

typedef union 
{
	struct
	{
		uint8_t RX_TIME			:3;
		uint8_t RX_TIME_QUAL	:1;
		uint8_t RX_TIME_RSSI	:1;
		uint8_t 				:3;
	};
	uint8_t raw;
}cc1101_mcsm2_t;

typedef union 
{
	struct
	{
		uint8_t TXOFF_MODE		:2;
		uint8_t RXOFF_MODE		:2;
		uint8_t CCA_MODE 		:2;
		uint8_t 				:2;
	};
	uint8_t raw;
}cc1101_mcsm1_t;

typedef union 
{
	struct
	{
		uint8_t XOSC_FORCE_ON	:1;
		uint8_t PIN_CTRL_EN		:1;
		uint8_t PO_TIMEOUT		:2;
		uint8_t FS_AUTOCAL		:2;
		uint8_t 				:2;
	};
	uint8_t raw;
}cc1101_mcsm0_t;

typedef union 
{
	struct
	{
		uint8_t FOC_LIMIT		:2;
		uint8_t FOC_POST_K		:1;
		uint8_t FOC_PRE_K		:2;
		uint8_t FOC_BS_CS_GATE	:1;
		uint8_t 				:2;
	};
	uint8_t raw;
}cc1101_foccfg_t;

typedef union 
{
	struct
	{
		uint8_t BS_LIMIT		:2;
		uint8_t BS_POST_KP		:1;
		uint8_t BC_POST_KI		:1;
		uint8_t BS_PRE_KP		:2;
		uint8_t BS_PRE_KI		:2;
	};
	uint8_t raw;
}cc1101_bscfg_t;

typedef union 
{
	struct
	{
		uint8_t MAGN_TARGET		:3;
		uint8_t MAX_LNA_GAIN	:3;
		uint8_t MAX_DVGA_GAIN	:2;
	};
	uint8_t raw;
}cc1101_agcctrl2_t;

typedef union 
{
	struct
	{
		uint8_t CARRIER_SENSE_ABS_THR 	:4;
		uint8_t CARRIER_SENSE_REL_THR 	:2;
		uint8_t AGC_LNA_PRIORITY 		:1;
		uint8_t 						:1;
	};
	uint8_t raw;
}cc1101_agcctrl1_t;

typedef union 
{
	struct
	{
		uint8_t FILTER_LENGTH	:2;
		uint8_t AGC_FREEZE		:2;
		uint8_t WAIT_TIME		:2;
		uint8_t HYST_LEVEL		:2;
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
		uint8_t WOR_RES			:2;
		uint8_t 				:1;
		uint8_t RC_CAL			:1;
		uint8_t EVENT1 			:3;
		uint8_t RC_PD			:1;
	};
	uint8_t raw;
}cc1101_worctrl_t;

typedef union 
{
	struct
	{
		uint8_t MIX_CURRENT 			:2;
		uint8_t LODIV_BUF_CURRENT_RX	:2;
		uint8_t LNA2MIX_CURRENT			:2;
		uint8_t LNA_CURRENT				:2;
	};
	uint8_t raw;
}cc1101_frend1_t;

typedef union 
{
	struct
	{
		uint8_t PA_POWER				:3;
		uint8_t 						:1;
		uint8_t LODIV_BUF_CURRENT_TX	:2;
		uint8_t 						:2;
	};
	uint8_t raw;
}cc1101_frend0_t;

typedef union 
{
	struct
	{
		uint8_t FSCAL3_3_0			:4;
		uint8_t CHP_CURR_CAL_EN		:2;
		uint8_t FSCAL3_7_6			:2;
	};
	uint8_t raw;
}cc1101_fscal3_t;

typedef union 
{
	struct
	{
		uint8_t FSCAL2			:5;
		uint8_t VCO_CORE_H_EN	:1;
		uint8_t 				:2;
	};
	uint8_t raw;
}cc1101_fscal2_t;

typedef union 
{
	struct
	{
		uint8_t FSCAL1			:6;
		uint8_t 				:2;
	};
	uint8_t raw;
}cc1101_fscal1_t;

typedef union 
{
	struct
	{
		uint8_t FSCAL0			:6;
		uint8_t 				:2;
	};
	uint8_t raw;
}cc1101_fscal0_t;

typedef union 
{
	struct
	{
		uint8_t RCCTRL1			:7;
		uint8_t 				:1;
	};
	uint8_t raw;
}cc1101_rcctrl1_t;

typedef union 
{
	struct
	{
		uint8_t RCCTRL0			:7;
		uint8_t 				:1;
	};
	uint8_t raw;
}cc1101_rcctrl0_t;

enum cc1101_registers_t
{
	CC1101_REG_IOCFG2		= 0x00,
	CC1101_REG_IOCFG1		= 0x01,
	CC1101_REG_IOCFG0		= 0x02,
	CC1101_REG_FIFOTHR		= 0x03,
	CC1101_REG_SYNC1		= 0x04,
	CC1101_REG_SYNC0		= 0x05,
	CC1101_REG_PKTLEN		= 0x06,
	CC1101_REG_PKTCTRL1		= 0x07,
	CC1101_REG_PKTCTRL0		= 0x08,
	CC1101_REG_ADDR			= 0x09,
	CC1101_REG_CHANNR		= 0x0A,
	CC1101_REG_FSCTRL1		= 0x0B,
	CC1101_REG_FSCTRL0		= 0x0C,
	CC1101_REG_FREQ2		= 0x0D,
	CC1101_REG_FREQ1		= 0x0E,
	CC1101_REG_FREQ0		= 0x0F,
	CC1101_REG_MDMCFG4		= 0x10,
	CC1101_REG_MDMCFG3		= 0x11,
	CC1101_REG_MDMCFG2		= 0x12,
	CC1101_REG_MDMCFG1		= 0x13,
	CC1101_REG_MDMCFG0		= 0x14,
	CC1101_REG_DEVIATN		= 0x15,
	CC1101_REG_MCSM2		= 0x16,
	CC1101_REG_MCSM1		= 0x17,
	CC1101_REG_MCSM0		= 0x18,
	CC1101_REG_FOCCFG		= 0x19,
	CC1101_REG_BSCFG		= 0x1A,
	CC1101_REG_AGCCTRL2		= 0x1B,
	CC1101_REG_AGCCTRL1		= 0x1C,
	CC1101_REG_AGCCTRL0		= 0x1D,
	CC1101_REG_WOREVT1		= 0x1E,
	CC1101_REG_WOREVT0		= 0x1F,
	CC1101_REG_WORCTRL		= 0x20,
	CC1101_REG_FREND1		= 0x21,
	CC1101_REG_FREND0		= 0x22,
	CC1101_REG_FSCAL3		= 0x23,
	CC1101_REG_FSCAL2		= 0x24,
	CC1101_REG_FSCAL1		= 0x25,
	CC1101_REG_FSCAL0		= 0x26,
	CC1101_REG_RCCTRL1		= 0x27,
	CC1101_REG_RCCTRL0		= 0x28
};


#define CC1101_REG_FSTEST 0x29	   //FSTEST
#define CC1101_VAL_FSTEST 0x59	   //FSTEST
#define CC1101_REG_PTEST 0x2A	   //PTEST
#define CC1101_VAL_PTEST 0x7F	   //PTEST
#define CC1101_REG_AGCTST 0x2B	   //AGCTST
#define CC1101_VAL_AGCTST 0x00	   //AGCTST
#define CC1101_REG_TEST2 0x2C	   //TEST2
#define CC1101_VAL_TEST2 0x00	   //TEST2
#define CC1101_REG_TEST1 0x2D	   //TEST1
#define CC1101_VAL_TEST1 0x00	   //TEST1
#define CC1101_REG_TEST0 0x2E	   //TEST0
#define CC1101_VAL_TEST0 0x00	   //TEST0


enum class cc1101_statusreg_t : uint8_t
{
	CC1101_STATUS_REG_PARTNUM		= 0xF0,
	CC1101_STATUS_REG_VERSION		= 0xF1,
	CC1101_STATUS_REG_FREQEST		= 0xF2,
	CC1101_STATUS_REG_LQI			= 0xF3,
	CC1101_STATUS_REG_RSSI			= 0xF4,
	CC1101_STATUS_REG_MARCSTATE		= 0xF5,
	CC1101_STATUS_REG_WORTIM1		= 0xF6,
	CC1101_STATUS_REG_WORTIM0		= 0xF7,
	CC1101_STATUS_REG_PKTSTATUS		= 0xF8,
	CC1101_STATUS_REG_VCO_VC_DAC	= 0xF9,
	CC1101_STATUS_REG_TXBYTES		= 0xFA,
	CC1101_STATUS_REG_RXBYTES		= 0xFB
};

#define CC1101_REG_PATABLE 0x3E   //PATABLE
#define CC1101_VAL_PATABLE 0xFF   //PATABLE





#define CC1101_SINGLE_TX 0x3F
#define CC1101_BURST_TX 0x7F
#define CC1101_SINGLE_RX 0xBF
#define CC1101_BURST_RX 0xFF



#define CC1101_VARIABLE_PKTLEN_EN 	(CC1101_VAL_PKTCTRL0 & 0x03)
#define CC1101_ADR_CHK 				((CC1101_VAL_PKTCTRL1 & 0x03) > 0)
#define CC1101_APPEND_STATUS		1

#define CC1101_SPI_HANDLE &hspi1



enum CC1101_State
{
	CC1101_State_SLEEP,
	CC1101_State_IDLE,
	CC1101_State_XOFF,
	CC1101_State_VCOON_MC,
	CC1101_State_REGON_MC,
	CC1101_State_MANCAL,
	CC1101_State_VCOON,
	CC1101_State_REGON,
	CC1101_State_STARTCAL,
	CC1101_State_BWBOOST,
	CC1101_State_FS_LOCK,
	CC1101_State_IFADCON,
	CC1101_State_ENDCAL,
	CC1101_State_RX,
	CC1101_State_RX_END,
	CC1101_State_RX_RST,
	CC1101_State_TXRX_SWITCH,
	CC1101_State_RXFIFO_OVERFLOW,
	CC1101_State_FSTXON,
	CC1101_State_TX,
	CC1101_State_TX_END,
	CC1101_State_RXTX_SWITCH,
	CC1101_State_TXFIFO_UNDERFLOW
};

enum class cc1101_strobe_t : uint8_t
{
	CC1101_Strobe_SRES = 0x30,
	CC1101_Strobe_SFSTXON,
	CC1101_Strobe_SXOFF,
	CC1101_Strobe_SCAL,
	CC1101_Strobe_SRX,
	CC1101_Strobe_STX,
	CC1101_Strobe_SIDLE,
	CC1101_Strobe_SWOR = 0x38,
	CC1101_Strobe_SPWD,
	CC1101_Strobe_SFRX,
	CC1101_Strobe_SFTX,
	CC1101_Strobe_SWORRST,
	CC1101_Strobe_SNOP,
};

class CC1101
{
private:
    CC1101_State state;

	
	public:
	CC1101();
	CC1101_State read_fsm_state();
	
    CC1101_State state_transition(cc1101_strobe_t strobe);
	
	uint8_t init();
	
	uint8_t read_rx_fifo(uint8_t *pRxData);
	
	uint8_t write_tx_fifo(uint8_t *pTxData);
	
	uint8_t read_status_reg(cc1101_statusreg_t reg);
	
	
	
	cc1101_iocfg2_t iocfg2;
	cc1101_iocfg1_t iocfg1;
	cc1101_iocfg0_t iocfg0;
	cc1101_fifothr_t fifothr;
	cc1101_sync1_t sync1;
	cc1101_sync0_t sync0;
	cc1101_pktlen_t pktlen;
	cc1101_pktctrl1_t pktctrl1;
	cc1101_pktctrl0_t pktctrl0;
	cc1101_addr_t addr;
	cc1101_channr_t channr;
	cc1101_fsctrl1_t fsctrl1;
	cc1101_fsctrl0_t fsctrl0;
	cc1101_freq2_t freq2;
	cc1101_freq1_t freq1;
	cc1101_freq0_t freq0;
	cc1101_mdmcfg4_t mdmcfg4;
	cc1101_mdmcfg3_t mdmcfg3;
	cc1101_mdmcfg2_t mdmcfg2;
	cc1101_mdmcfg1_t mdmcfg1;
	cc1101_mdmcfg0_t mdmcfg0;
	cc1101_deviatn_t deviatn;
	cc1101_mcsm2_t mcsm2;
	cc1101_mcsm1_t mcsm1;
	cc1101_mcsm0_t mcsm0;
	cc1101_foccfg_t foccfg;
	cc1101_bscfg_t bscfg;
	cc1101_agcctrl2_t agcctrl2;
	cc1101_agcctrl1_t agcctrl1;
	cc1101_agcctrl0_t agcctrl0;
	cc1101_worevt1_t worevt1;
	cc1101_worevt0_t worevt0;
	cc1101_worctrl_t worctrl;
	cc1101_frend1_t frend1;
	cc1101_frend0_t frend0;
	cc1101_fscal3_t fscal3;
	cc1101_fscal2_t fscal2;
	cc1101_fscal1_t fscal1;
	cc1101_fscal0_t fscal0;
	cc1101_rcctrl1_t rcctrl1;
	cc1101_rcctrl0_t rcctrl0;


};
