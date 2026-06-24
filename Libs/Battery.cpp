#include "Battery.h"




#define COLOR_RED 0xFF0000
#define COLOR_YELLOW 0xFFFF00
#define COLOR_GREEN 0x00FF00
#define COLOR_ORANGE 0xFFA500
#define COLOR_BLUE 0x0000FF

uint16_t adc_value = 0;
uint16_t vrefint_adc = 0;


static void setLEDColor(uint32_t color, uint8_t brightness = 50)
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, (color >> 16) & 0xFF * brightness / 255); //Red
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, (color >> 8) & 0xFF * brightness / 255);  //Green
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, color & 0xFF * brightness / 255);         //Blue
}



static void updateLED(float voltage)
{
    uint32_t color;
    uint8_t brightness;

    if (voltage > 4.5f)
    {
        color = COLOR_BLUE;
    }
    else if (voltage > 4.0f)
    {
        // Blend BLUE to GREEN
        float blend = (voltage - 4.0f) / 0.2f;
        uint32_t r = (uint32_t)((0x00 * (1 - blend) + 0x00 * blend));
        uint32_t g = (uint32_t)((0xFF * (1 - blend) + 0xFF * blend));
        uint32_t b = (uint32_t)((0xFF * (1 - blend) + 0x00 * blend));
        color = (r << 16) | (g << 8) | b;
    }
    else if (voltage > 3.8f)
    {
        color = COLOR_GREEN;
    }
    else if (voltage > 3.6f)
    {
        // Blend GREEN to YELLOW
        float blend = (voltage - 3.6f) / 0.2f;
        uint32_t r = (uint32_t)((0x00 * (1 - blend) + 0xFF * blend));
        uint32_t g = (uint32_t)((0xFF * (1 - blend) + 0xFF * blend));
        uint32_t b = (uint32_t)((0x00 * (1 - blend) + 0x00 * blend));
        color = (r << 16) | (g << 8) | b;
    }
    else if (voltage > 3.4f)
    {
        // Blend YELLOW to RED
        float blend = (voltage - 3.4f) / 0.2f;
        uint32_t r = (uint32_t)((0xFF * (1 - blend) + 0xFF * blend));
        uint32_t g = (uint32_t)((0xFF * (1 - blend) + 0x00 * blend));
        uint32_t b = (uint32_t)((0x00 * (1 - blend) + 0x00 * blend));
        color = (r << 16) | (g << 8) | b;
    }
    else
    {
        color = COLOR_RED;
    }

    setLEDColor(color);
}


void Battery_Init()
{
    //Nothing to initialize, ADC is already initialized in main.cpp
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t*)&adc_value, 1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&vrefint_adc, 1);

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

float Battery_ReadVoltage()
{
    float vref = VREFINT * ADC_RES_12BIT / vrefint_adc; //calculate Vref in V, see P.14 in STM32G4 reference manual
    float voltage = (adc_value * vref / ADC_RES_16BIT) * R_BOTTOM / R_TOP; //calculate voltage in V

    updateLED(voltage);

    return voltage;
}