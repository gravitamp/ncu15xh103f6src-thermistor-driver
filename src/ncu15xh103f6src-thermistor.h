/*
 * ws2812-led.h
 *
 *  Created on: Mar 28, 2023
 *      Author: GEN
 */

#ifndef DRIVERS_NCU15XH103f6SRC_THERMISTOR_H_
#define DRIVERS_NCU15XH103f6SRC_THERMISTOR_H_

/* Includes
 * --------------------------------------------*/
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#include <adc.h>

/* Private defines
 * --------------------------------------------*/

/* Exported defines
 * --------------------------------------------*/
/** @defgroup ADCEx_Calibration_Mode   ADC Extended Calibration mode offset mode or linear mode
  * @{
  */
#define ADC_CALIB_OFFSET                   (LL_ADC_CALIB_OFFSET)
#define ADC_CALIB_OFFSET_LINEARITY         (LL_ADC_CALIB_OFFSET_LINEARITY)
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_CHANNEL_SINGLE_DIFF_ENDING  Channel - Single or differential ending
  * @{
  */
#define ADC_SINGLE_ENDED                (LL_ADC_SINGLE_ENDED)         /*!< ADC channel ending set to single ended (literal also used to set calibration mode) */
#define ADC_DIFFERENTIAL_ENDED          (LL_ADC_DIFFERENTIAL_ENDED)   /*!< ADC channel ending set to differential (literal also used to set calibration mode) */
/**
  * @}
  */

/* Public function prototypes
 * --------------------------------------------*/

void ADC_Thermistor_Init(ADC_HandleTypeDef *adc);
float ADC_Thermistor_Read(ADC_HandleTypeDef *adc);

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_NCU15XH103f6SRC_THERMISTOR_H_ */

