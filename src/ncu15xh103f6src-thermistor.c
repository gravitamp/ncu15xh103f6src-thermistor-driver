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
#define NTC_UP_R 8624.2f //8624.2f

/* constants of Steinhart-Hart equation, based on datasheet */ 
#define A 0.9017477480e-3f
#define B 2.489190310e-4f
#define C 2.043213857e-7f

/* Public function implementations
 * --------------------------------------------*/

void ADC_Thermistor_Init(ADC_HandleTypeDef *adc)
{  // ADC calibration
  HAL_ADCEx_Calibration_Start(adc, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
}

float ADC_Thermistor_Read(ADC_HandleTypeDef *adc)
{
  // Start ADC Conversion
  HAL_ADC_Start(adc);
  // Poll ADC1 Perihperal & TimeOut = 1mSec
   HAL_ADC_PollForConversion(adc, 1);
  // Read The ADC Conversion Result & Map It To PWM DutyCycle
   AD_RES = HAL_ADC_GetValue(adc);
   HAL_ADC_Stop(adc);
  // calc. ntc resistance
  Ntc_R = ((NTC_UP_R)*((STM32_ANALOG_RESOLUTION/AD_RES) - 1));
  // temp
  float Ntc_Ln = log(Ntc_R);
  // calc. temperature
  Ntc_Tmp = (1.0/(A + B*Ntc_Ln + C*Ntc_Ln*Ntc_Ln*Ntc_Ln)) - 273.15;
//  HAL_ADC_Stop(adc);

  return (movingAvg(&lcdTemperature.sampler, lcdTemperature.buffer, LCDTEMP_SAMPLE_SZ, Ntc_Tmp));
}
