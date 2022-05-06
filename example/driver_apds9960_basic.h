/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_apds9960_basic.h
 * @brief     driver apds9960 basic header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-01-23
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/01/23  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_APDS9960_BASIC_H
#define DRIVER_APDS9960_BASIC_H

#include "driver_apds9960_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup apds9960_example_driver apds9960 example driver function
 * @brief    apds9960 example driver modules
 * @ingroup  apds9960_driver
 * @{
 */

/**
 * @brief apds9960 basic example default definition
 */
#define APDS9960_BASIC_DEFAULT_ADC_INTEGRATION_TIME                  103.0f                                                     /**< 103 ms */
#define APDS9960_BASIC_DEFAULT_WAIT_TIME                             10.0f                                                      /**< 10 ms */
#define APDS9960_BASIC_DEFAULT_ALS_INTERRUPT_LOW_THRESHOLD           0x0000U                                                    /**< 0x0000 */
#define APDS9960_BASIC_DEFAULT_ALS_INTERRUPT_HIGH_THRESHOLD          0xFFFFU                                                    /**< 0xFFFF */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_INTERRUPT_LOW_THRESHOLD     0x00                                                       /**< 0x00 */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_INTERRUPT_HIGH_THRESHOLD    0xFF                                                       /**< 0xFF */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_INTERRUPT_CYCLE             APDS9960_PROXIMITY_INTERRUPT_CYCLE_2                       /**< proximity interrupt cycle 2 */
#define APDS9960_BASIC_DEFAULT_ALS_INTERRUPT_CYCLE                   APDS9960_ALS_INTERRUPT_CYCLE_2                             /**< als interrupt cycle 2 */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_PULSE_LENGTH                APDS9960_PROXIMITY_PULSE_LENGTH_8_US                       /**< proximity pulse length 8 us */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_PULSE_COUNT                 7                                                          /**< proximity pulse count 7 */
#define APDS9960_BASIC_DEFAULT_LED_CURRENT                           APDS9960_LED_CURRENT_100_MA                                /**< led current 100 mA */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_GAIN                        APDS9960_PROXIMITY_GAIN_4X                                 /**< proximity gain 4x */
#define APDS9960_BASIC_DEFAULT_ALS_COLOR_GAIN                        APDS9960_ALS_COLOR_GAIN_4X                                 /**< als color gain 4x */
#define APDS9960_BASIC_DEFAULT_SATURATION_INTERRUPT_PROXIMITY        APDS9960_BOOL_FALSE                                        /**< disable */
#define APDS9960_BASIC_DEFAULT_SATURATION_INTERRUPT_CLEAR_PHOTODIODE APDS9960_BOOL_FALSE                                        /**< disable */
#define APDS9960_BASIC_DEFAULT_LED_BOOST                             APDS9960_LED_BOOST_100_PERCENTAGE                          /**< 100% */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_UP_RIGHT_OFFSET             0                                                          /**< 0 offset */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_DOWN_LEFT_OFFSET            0                                                          /**< 0 offset */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_GAIN_COMPENSATION           APDS9960_BOOL_FALSE                                        /**< disable */
#define APDS9960_BASIC_DEFAULT_SLEEP_AFTER_INTERRUPT                 APDS9960_BOOL_FALSE                                        /**< disable */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_MASK_UP                     APDS9960_BOOL_FALSE                                        /**< disable */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_MASK_DOWN                   APDS9960_BOOL_FALSE                                        /**< disable */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_MASK_LEFT                   APDS9960_BOOL_FALSE                                        /**< disable */
#define APDS9960_BASIC_DEFAULT_PROXIMITY_MASK_RIGHT                  APDS9960_BOOL_FALSE                                        /**< disable */
#define APDS9960_BASIC_DEFAULT_GESTURE_PROXIMITY_ENTER_THRESHOLD     0x00                                                       /**< 0x00 */
#define APDS9960_BASIC_DEFAULT_GESTURE_PROXIMITY_EXIT_THRESHOLD      0xFF                                                       /**< 0xFF */
#define APDS9960_BASIC_DEFAULT_GESTURE_FIFO_THRESHOLD                APDS9960_GESTURE_FIFO_THRESHOLD_8_DATASET                  /**< fifo level 8 */
#define APDS9960_BASIC_DEFAULT_GESTURE_EXIT_PERSISTENCE              APDS9960_GESTURE_EXIT_PERSISTENCE_1ST                      /**< persistence 1st */
#define APDS9960_BASIC_DEFAULT_GESTURE_EXIT_MASK                     0x00                                                       /**< 0x00 */
#define APDS9960_BASIC_DEFAULT_GESTURE_GAIN                          APDS9960_GESTURE_GAIN_2X                                   /**< gesture 2x */
#define APDS9960_BASIC_DEFAULT_GESTURE_LED_CURRENT                   APDS9960_GESTURE_LED_CURRENT_100_MA                        /**< gesture 100 mA */
#define APDS9960_BASIC_DEFAULT_GESTURE_WAIT_TIME                     APDS9960_GESTURE_WAIT_TIME_2P8_MS                          /**< 2.8 ms */
#define APDS9960_BASIC_DEFAULT_GESTURE_UP_OFFSET                     0                                                          /**< 0 offset */
#define APDS9960_BASIC_DEFAULT_GESTURE_DOWN_OFFSET                   0                                                          /**< 0 offset */
#define APDS9960_BASIC_DEFAULT_GESTURE_LEFT_OFFSET                   0                                                          /**< 0 offset */
#define APDS9960_BASIC_DEFAULT_GESTURE_RIGHT_OFFSET                  0                                                          /**< 0 offset */
#define APDS9960_BASIC_DEFAULT_GESTURE_PULSE_LENGTH                  APDS9960_GESTURE_PULSE_LENGTH_32_US                        /**< 32 us */
#define APDS9960_BASIC_DEFAULT_GESTURE_PULSE_COUNT                   9                                                          /**< 9 */
#define APDS9960_BASIC_DEFAULT_GESTURE_DIMENSION                     APDS9960_GESTURE_DIMENSION_SELECT_BOTH_PAIRS_ACTIVE        /**< gesture dimension both */
#define APDS9960_BASIC_DEFAULT_GESTURE_INTERRUPT                     APDS9960_BOOL_FALSE                                        /**< disable */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t apds9960_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t apds9960_basic_deinit(void);

/**
 * @brief      basic example read rgbc
 * @param[out] *red points to a red buffer
 * @param[out] *green points to a green buffer
 * @param[out] *blue points to a blue buffer
 * @param[out] *clear points to a clear buffer
 * @return     status code
 *             - 0 success
 *             - 1 read rgbc failed
 * @note       none
 */
uint8_t apds9960_basic_read_rgbc(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear);

/**
 * @brief      basic example read proximity
 * @param[out] *proximity points to a proximity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read proximity failed
 * @note       none
 */
uint8_t apds9960_basic_read_proximity(uint8_t *proximity);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
