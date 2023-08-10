/*
 * led.c
 *
 *  Created on: Aug 8, 2023
 *      Author: gen
 */

/* Includes
 * --------------------------------------------*/
#include "ncu15xh103f6src-thermistor.h"
#include <math.h>

/* Private variables
 * --------------------------------------------*/

#define STM32_ANALOG_RESOLUTION 65535.0f

/* adc vars */
uint32_t AD_RES;

/* ntc vars */
float Ntc_Tmp;
float Ntc_Tmp_Raw;
uint16_t Ntc_R;

/* R1 resistance */
#define NTC_UP_R 10000.0f

/* constants of Steinhart-Hart equation, based on datasheet */ 
#define A 0.0009020459061f
#define B 0.0002488731513f
#define C 0.0000002044806163f

/* Public function implementations
 * --------------------------------------------*/

void ADC_Thermistor_Init(ADC_HandleTypeDef *adc)
{
  // Start ADC Conversion
     HAL_ADC_Start(adc);

  // ADC calibration
  HAL_ADCEx_Calibration_Start(adc, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
}

float ADC_Thermistor_Read(ADC_HandleTypeDef *adc)
{
  // Start ADC Conversion
  HAL_ADC_Start_IT(adc);

  // calc. ntc resistance
  Ntc_R = ((NTC_UP_R)/((STM32_ANALOG_RESOLUTION/AD_RES) - 1));  //16 bit resolution
  // temp
  float Ntc_Ln = log(Ntc_R);
  // calc. temperature
  Ntc_Tmp = (1.0/(A + B*Ntc_Ln + C*Ntc_Ln*Ntc_Ln*Ntc_Ln)) - 273.15;

  return (Ntc_Tmp);
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    // Read & Update The ADC Result
    AD_RES = HAL_ADC_GetValue(&hadc1);
}
