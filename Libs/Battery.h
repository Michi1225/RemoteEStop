#pragma once

#include "main.h"


#define R_TOP 10000
#define R_BOTTOM 18000
#define ADC_RES_16BIT 65535
#define ADC_RES_12BIT 4096
#define VREFINT 1.21f

extern uint16_t adc_value;
extern uint16_t vrefint_adc;

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern TIM_HandleTypeDef htim2;


void  Battery_Init();
float Battery_ReadVoltage();