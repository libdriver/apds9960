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
 * @file      driver_apds9960.h
 * @brief     driver apds9960 header file
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

#ifndef DRIVER_APDS9960_H
#define DRIVER_APDS9960_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup apds9960_driver apds9960 driver function
 * @brief    apds9960 driver modules
 * @{
 */

/**
 * @addtogroup apds9960_basic_driver
 * @{
 */

/**
 * @brief apds9960 gesture algorithm params definition
 */
#ifndef APDS9960_GESTURE_THRESHOLD
    #define APDS9960_GESTURE_THRESHOLD     10        /**< 10 */
#endif

#ifndef APDS9960_GESTURE_SENSITIVITY_1
    #define APDS9960_GESTURE_SENSITIVITY_1 50        /**< 50 */
#endif

#ifndef APDS9960_GESTURE_SENSITIVITY_2
    #define APDS9960_GESTURE_SENSITIVITY_2 20        /**< 20 */
#endif

/**
 * @brief apds9960 bool enumeration definition
 */
typedef enum
{
    APDS9960_BOOL_FALSE = 0x00,        /**< false */
    APDS9960_BOOL_TRUE  = 0x01,        /**< true */
} apds9960_bool_t;

/**
 * @brief apds9960 conf enumeration definition
 */
typedef enum
{
    APDS9960_CONF_GESTURE_ENABLE             = 6,        /**< gesture enable */
    APDS9960_CONF_PROXIMITY_INTERRUPT_ENABLE = 5,        /**< proximity interrupt enable */
    APDS9960_CONF_ALS_INTERRUPT_ENABLE       = 4,        /**< als interrupt enable */
    APDS9960_CONF_WAIT_ENABLE                = 3,        /**< wait enable */
    APDS9960_CONF_PROXIMITY_DETECT_ENABLE    = 2,        /**< proximity detect enable */
    APDS9960_CONF_ALS_ENABLE                 = 1,        /**< als enable */
    APDS9960_CONF_POWER_ON                   = 0,        /**< power on */
} apds9960_conf_t;

/**
 * @brief apds9960 proximity interrupt cycle enumeration definition
 */
typedef enum
{
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_EVERY = 0,        /**< every proximity cycle */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_ANY   = 1,        /**< any proximity value outside of threshold range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_2     = 2,        /**< 2 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_3     = 3,        /**< 3 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_4     = 4,        /**< 4 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_5     = 5,        /**< 5 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_6     = 6,        /**< 6 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_7     = 7,        /**< 7 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_8     = 8,        /**< 8 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_9     = 9,        /**< 9 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_10    = 10,       /**< 10 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_11    = 11,       /**< 11 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_12    = 12,       /**< 12 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_13    = 13,       /**< 13 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_14    = 14,       /**< 14 consecutive proximity values out of range */
    APDS9960_PROXIMITY_INTERRUPT_CYCLE_15    = 15,       /**< 15 consecutive proximity values out of range */
} apds9960_proximity_interrupt_cycle_t;

/**
 * @brief apds9960 als interrupt cycle enumeration definition
 */
typedef enum
{
    APDS9960_ALS_INTERRUPT_CYCLE_EVERY = 0,        /**< every als cycle */
    APDS9960_ALS_INTERRUPT_CYCLE_ANY   = 1,        /**< any als value outside of threshold range */
    APDS9960_ALS_INTERRUPT_CYCLE_2     = 2,        /**< 2 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_3     = 3,        /**< 3 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_5     = 4,        /**< 5 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_10    = 5,        /**< 10 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_15    = 6,        /**< 15 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_20    = 7,        /**< 20 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_25    = 8,        /**< 25 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_30    = 9,        /**< 30 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_35    = 10,       /**< 35 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_40    = 11,       /**< 40 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_45    = 12,       /**< 45 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_50    = 13,       /**< 50 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_55    = 14,       /**< 55 consecutive als values out of range */
    APDS9960_ALS_INTERRUPT_CYCLE_60    = 15,       /**< 60 consecutive als values out of range */
} apds9960_als_interrupt_cycle_t;

/**
 * @brief apds9960 proximity pulse length enumeration definition
 */
typedef enum
{
    APDS9960_PROXIMITY_PULSE_LENGTH_4_US  = 0x00,        /**< 4 us */
    APDS9960_PROXIMITY_PULSE_LENGTH_8_US  = 0x01,        /**< 8 us */
    APDS9960_PROXIMITY_PULSE_LENGTH_16_US = 0x02,        /**< 16 us */
    APDS9960_PROXIMITY_PULSE_LENGTH_32_US = 0x03,        /**< 32 us */
} apds9960_proximity_pulse_length_t;

/**
 * @brief apds9960 led current enumeration definition
 */
typedef enum
{
    APDS9960_LED_CURRENT_100_MA  = 0x00,        /**< 100 mA */
    APDS9960_LED_CURRENT_50_MA   = 0x01,        /**< 50 mA */
    APDS9960_LED_CURRENT_25_MA   = 0x02,        /**< 25 mA */
    APDS9960_LED_CURRENT_12P5_MA = 0x03,        /**< 12.5 mA */
} apds9960_led_current_t;

/**
 * @brief apds9960 proximity gain enumeration definition
 */
typedef enum
{
    APDS9960_PROXIMITY_GAIN_1X = 0x00,        /**< 1x */
    APDS9960_PROXIMITY_GAIN_2X = 0x01,        /**< 2x */
    APDS9960_PROXIMITY_GAIN_4X = 0x02,        /**< 4x */
    APDS9960_PROXIMITY_GAIN_8X = 0x03,        /**< 8x */
} apds9960_proximity_gain_t;

/**
 * @brief apds9960 als and color gain enumeration definition
 */
typedef enum
{
    APDS9960_ALS_COLOR_GAIN_1X  = 0x00,        /**< 1x */
    APDS9960_ALS_COLOR_GAIN_4X  = 0x01,        /**< 4x */
    APDS9960_ALS_COLOR_GAIN_16X = 0x02,        /**< 16x */
    APDS9960_ALS_COLOR_GAIN_64X = 0x03,        /**< 64x */
} apds9960_als_color_gain_t;

/**
 * @brief apds9960 saturation interrupt enumeration definition
 */
typedef enum
{
    APDS9960_SATURATION_INTERRUPT_PROXIMITY        = 7,        /**< proximity saturation interrupt */
    APDS9960_SATURATION_INTERRUPT_CLEAR_PHOTODIODE = 6,        /**< clear photo diode saturation interrupt */
} apds9960_saturation_interrupt_t;

/**
 * @brief apds9960 led boost enumeration definition
 */
typedef enum
{
    APDS9960_LED_BOOST_100_PERCENTAGE = 0x00,        /**< 100% */
    APDS9960_LED_BOOST_150_PERCENTAGE = 0x01,        /**< 150% */
    APDS9960_LED_BOOST_200_PERCENTAGE = 0x02,        /**< 200% */
    APDS9960_LED_BOOST_300_PERCENTAGE = 0x03,        /**< 300% */
} apds9960_led_boost_t;

/**
 * @brief apds9960 status enumeration definition
 */
typedef enum
{
    APDS9960_STATUS_CPSAT  = 7,        /**< clear photo diode saturation */
    APDS9960_STATUS_PGSAT  = 6,        /**< indicates that an analog saturation event occurred during a previous proximity or gesture cycle */
    APDS9960_STATUS_PINT   = 5,        /**< proximity interrupt */
    APDS9960_STATUS_AINT   = 4,        /**< als interrupt */
    APDS9960_STATUS_GINT   = 2,        /**< gesture interrupt */
    APDS9960_STATUS_PVALID = 1,        /**< proximity valid */
    APDS9960_STATUS_AVALID = 0,        /**< als valid */
} apds9960_status_t;

/**
 * @brief apds9960 proximity mask enumeration definition
 */
typedef enum
{
    APDS9960_PROXIMITY_MASK_UP    = 3,        /**< proximity mask up */
    APDS9960_PROXIMITY_MASK_DOWN  = 2,        /**< proximity mask down */
    APDS9960_PROXIMITY_MASK_LEFT  = 1,        /**< proximity mask left */
    APDS9960_PROXIMITY_MASK_RIGHT = 0,        /**< proximity mask right */
} apds9960_proximity_mask_t;

/**
 * @brief apds9960 gesture fifo threshold enumeration definition
 */
typedef enum
{
    APDS9960_GESTURE_FIFO_THRESHOLD_1_DATASET  = 0,        /**< interrupt is generated after 1 dataset is added to fifo */
    APDS9960_GESTURE_FIFO_THRESHOLD_4_DATASET  = 1,        /**< interrupt is generated after 4 dataset is added to fifo */
    APDS9960_GESTURE_FIFO_THRESHOLD_8_DATASET  = 2,        /**< interrupt is generated after 8 dataset is added to fifo */
    APDS9960_GESTURE_FIFO_THRESHOLD_16_DATASET = 3,        /**< interrupt is generated after 16 dataset is added to fifo */
} apds9960_gesture_fifo_threshold_t;

/**
 * @brief apds9960 gesture exit persistence enumeration definition
 */
typedef enum
{
    APDS9960_GESTURE_EXIT_PERSISTENCE_1ST = 0,        /**< 1st 'gesture end' occurrence results in gesture state machine exit */
    APDS9960_GESTURE_EXIT_PERSISTENCE_2ND = 1,        /**< 2nd 'gesture end' occurrence results in gesture state machine exit */
    APDS9960_GESTURE_EXIT_PERSISTENCE_4TH = 2,        /**< 4th 'gesture end' occurrence results in gesture state machine exit */
    APDS9960_GESTURE_EXIT_PERSISTENCE_7TH = 3,        /**< 7th 'gesture end' occurrence results in gesture state machine exit */
} apds9960_gesture_exit_persistence_t;

/**
 * @brief apds9960 gesture gain control enumeration definition
 */
typedef enum
{
    APDS9960_GESTURE_GAIN_1X = 0,        /**< 1x */
    APDS9960_GESTURE_GAIN_2X = 1,        /**< 2x */
    APDS9960_GESTURE_GAIN_4X = 2,        /**< 4x */
    APDS9960_GESTURE_GAIN_8X = 3,        /**< 8x */
} apds9960_gesture_gain_control_t;

/**
 * @brief apds9960 gesture led current enumeration definition
 */
typedef enum
{
    APDS9960_GESTURE_LED_CURRENT_100_MA  = 0x00,        /**< 100 mA */
    APDS9960_GESTURE_LED_CURRENT_50_MA   = 0x01,        /**< 50 mA */
    APDS9960_GESTURE_LED_CURRENT_25_MA   = 0x02,        /**< 25 mA */
    APDS9960_GESTURE_LED_CURRENT_12P5_MA = 0x03,        /**< 12.5 mA */
} apds9960_gesture_led_current_t;

/**
 * @brief apds9960 gesture wait time enumeration definition
 */
typedef enum
{
    APDS9960_GESTURE_WAIT_TIME_0_MS    = 0x00,        /**< 0 ms */
    APDS9960_GESTURE_WAIT_TIME_2P8_MS  = 0x01,        /**< 2.8 ms */
    APDS9960_GESTURE_WAIT_TIME_5P6_MS  = 0x02,        /**< 5.6 ms */
    APDS9960_GESTURE_WAIT_TIME_8P4_MS  = 0x03,        /**< 8.4 ms */
    APDS9960_GESTURE_WAIT_TIME_14_MS   = 0x04,        /**< 14 ms */
    APDS9960_GESTURE_WAIT_TIME_22P4_MS = 0x05,        /**< 22.4 ms */
    APDS9960_GESTURE_WAIT_TIME_30P8_MS = 0x06,        /**< 30.8 ms */
    APDS9960_GESTURE_WAIT_TIME_39P2_MS = 0x07,        /**< 39.2 ms */
} apds9960_gesture_wait_time_t;

/**
 * @brief apds9960 gesture pulse length enumeration definition
 */
typedef enum
{
    APDS9960_GESTURE_PULSE_LENGTH_4_US  = 0x00,        /**< 4 us */
    APDS9960_GESTURE_PULSE_LENGTH_8_US  = 0x01,        /**< 8 us */
    APDS9960_GESTURE_PULSE_LENGTH_16_US = 0x02,        /**< 16 us */
    APDS9960_GESTURE_PULSE_LENGTH_32_US = 0x03,        /**< 32 us */
} apds9960_gesture_pulse_length_t;

/**
 * @brief apds9960 gesture dimension select enumeration definition
 */
typedef enum
{
    APDS9960_GESTURE_DIMENSION_SELECT_BOTH_PAIRS_ACTIVE            = 0x00,        /**< both pairs are active */
    APDS9960_GESTURE_DIMENSION_SELECT_ONLY_UP_DOWN_PAIRS_ACTIVE    = 0x01,        /**< only the up down pair is active */
    APDS9960_GESTURE_DIMENSION_SELECT_ONLY_LEFT_RIGHT_PAIRS_ACTIVE = 0x02,        /**< only the left right pair is active */
} apds9960_gesture_dimension_select_t;

/**
 * @brief apds9960 gesture status enumeration definition
 */
typedef enum
{
    APDS9960_GESTURE_STATUS_FIFO_OVERFLOW = 0x01,        /**< gesture fifo overflow */
    APDS9960_GESTURE_STATUS_FIFO_VALID    = 0x00,        /**< gesture fifo data */
} apds9960_gesture_status_t;

/**
 * @brief apds9960 interrupt status enumeration definition
 */
typedef enum
{
    APDS9960_INTERRUPT_STATUS_GESTURE_LEFT  = 15,       /**< gesture left */
    APDS9960_INTERRUPT_STATUS_GESTURE_RIGHT = 14,       /**< gesture right */
    APDS9960_INTERRUPT_STATUS_GESTURE_UP    = 13,       /**< gesture up */
    APDS9960_INTERRUPT_STATUS_GESTURE_DOWN  = 12,       /**< gesture down */
    APDS9960_INTERRUPT_STATUS_GESTURE_NEAR  = 11,       /**< gesture near */
    APDS9960_INTERRUPT_STATUS_GESTURE_FAR   = 10,       /**< gesture far */
    APDS9960_INTERRUPT_STATUS_GFOV          = 9,        /**< gesture fifo overflow */
    APDS9960_INTERRUPT_STATUS_GVALID        = 8,        /**< gesture fifo data */
    APDS9960_INTERRUPT_STATUS_CPSAT         = 7,        /**< clear photo diode saturation */
    APDS9960_INTERRUPT_STATUS_PGSAT         = 6,        /**< indicates that an analog saturation event occurred during a previous proximity or gesture cycle */
    APDS9960_INTERRUPT_STATUS_PINT          = 5,        /**< proximity interrupt */
    APDS9960_INTERRUPT_STATUS_AINT          = 4,        /**< als interrupt */
    APDS9960_INTERRUPT_STATUS_GINT          = 2,        /**< gesture interrupt */
    APDS9960_INTERRUPT_STATUS_PVALID        = 1,        /**< proximity valid */
    APDS9960_INTERRUPT_STATUS_AVALID        = 0,        /**< als valid */
} apds9960_interrupt_status_t;

/**
 * @brief apds9960 handle structure definition
 */
typedef struct apds9960_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    void (*receive_callback)(uint8_t type);                                             /**< point to a receive_callback function address */
    uint8_t inited;                                                                     /**< inited flag */
    uint8_t gesture_status;                                                             /**< gesture status */
    uint8_t gesture_threshold;                                                          /**< gesture threshold */
    int32_t gesture_sensitivity_1;                                                      /**< gesture sensitivity 1 */
    int32_t gesture_sensitivity_2;                                                      /**< gesture sensitivity 2 */
    int32_t gesture_ud_delta;                                                           /**< gesture ud delta */
    int32_t gesture_lr_delta;                                                           /**< gesture lr delta */
    int32_t gesture_ud_count;                                                           /**< gesture ud count */
    int32_t gesture_lr_count;                                                           /**< gesture lr count */
    int32_t gesture_near_count;                                                         /**< gesture near count */
    int32_t gesture_far_count;                                                          /**< gesture far count */
} apds9960_handle_t;

/**
 * @brief apds9960 information structure definition
 */
typedef struct apds9960_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} apds9960_info_t;

/**
 * @}
 */

/**
 * @defgroup apds9960_link_driver apds9960 link driver function
 * @brief    apds9960 link driver modules
 * @ingroup  apds9960_driver
 * @{
 */

/**
 * @brief     initialize apds9960_handle_t structure
 * @param[in] HANDLE points to an apds9960 handle structure
 * @param[in] STRUCTURE is apds9960_handle_t
 * @note      none
 */
#define DRIVER_APDS9960_LINK_INIT(HANDLE, STRUCTURE)        memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an apds9960 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_APDS9960_LINK_IIC_INIT(HANDLE, FUC)          (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an apds9960 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_APDS9960_LINK_IIC_DEINIT(HANDLE, FUC)        (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an apds9960 handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_APDS9960_LINK_IIC_READ(HANDLE, FUC)          (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an apds9960 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_APDS9960_LINK_IIC_WRITE(HANDLE, FUC)         (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an apds9960 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_APDS9960_LINK_DELAY_MS(HANDLE, FUC)          (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an apds9960 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_APDS9960_LINK_DEBUG_PRINT(HANDLE, FUC)       (HANDLE)->debug_print = FUC

/**
 * @brief     link receive_callback function
 * @param[in] HANDLE points to an apds9960 handle structure
 * @param[in] FUC points to a receive_callback function address
 * @note      none
 */
#define DRIVER_APDS9960_LINK_RECEIVE_CALLBACK(HANDLE, FUC)  (HANDLE)->receive_callback = FUC

/**
 * @}
 */

/**
 * @defgroup apds9960_basic_driver apds9960 basic driver function
 * @brief    apds9960 basic driver modules
 * @ingroup  apds9960_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an apds9960 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t apds9960_info(apds9960_info_t *info);

/**
 * @brief     irq handler
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_irq_handler(apds9960_handle_t *handle);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 read id failed
 *            - 5 id is invalid
 * @note      none
 */
uint8_t apds9960_init(apds9960_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t apds9960_deinit(apds9960_handle_t *handle);

/**
 * @brief      read the rgbc data
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *red points to a red buffer
 * @param[out] *green points to a green buffer
 * @param[out] *blue points to a blue buffer
 * @param[out] *clear points to a clear buffer
 * @return     status code
 *             - 0 success
 *             - 1 read rgbc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_read_rgbc(apds9960_handle_t *handle, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear);

/**
 * @brief      read the proximity data
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *proximity points to a proximity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read proximity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_read_proximity(apds9960_handle_t *handle, uint8_t *proximity);

/**
 * @brief         read data from the gesture fifo
 * @param[in]     *handle points to an apds9960 handle structure
 * @param[out]    **data points to a data buffer
 * @param[in,out] *len points to a data length buffer
 * @return        status code
 *                - 0 success
 *                - 1 read gesture fifo failed
 *                - 2 handle is NULL
 *                - 3 handle is not initialized
 * @note          none
 */
uint8_t apds9960_read_gesture_fifo(apds9960_handle_t *handle, uint8_t (*data)[4], uint8_t *len);

/**
 * @brief     decode gestures from the fifo data
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] **data points to data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 decode gesture from fifo failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 decode failed
 * @note      none
 */
uint8_t apds9960_gesture_decode(apds9960_handle_t *handle, uint8_t (*data)[4], uint8_t len);

/**
 * @brief     set the gesture decode threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the gesture decode threshold
 * @return    status code
 *            - 0 success
 *            - 1 set gesture decode threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_decode_threshold(apds9960_handle_t *handle, uint8_t threshold);

/**
 * @brief      get the gesture decode threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a gesture decode threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture decode threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_decode_threshold(apds9960_handle_t *handle, uint8_t *threshold);

/**
 * @brief     set the gesture decode sensitivity 1
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] sensitivity is the gesture decode sensitivity
 * @return    status code
 *            - 0 success
 *            - 1 set gesture decode sensitivity 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_decode_sensitivity_1(apds9960_handle_t *handle, int32_t sensitivity);

/**
 * @brief      get the gesture decode sensitivity 1
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *sensitivity points to a gesture decode sensitivity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture decode sensitivity 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_decode_sensitivity_1(apds9960_handle_t *handle, int32_t *sensitivity);

/**
 * @brief     set the gesture decode sensitivity 2
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] sensitivity is the gesture decode sensitivity
 * @return    status code
 *            - 0 success
 *            - 1 set gesture decode sensitivity 2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_decode_sensitivity_2(apds9960_handle_t *handle, int32_t sensitivity);

/**
 * @brief      get the gesture decode sensitivity 2
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *sensitivity points to a gesture decode sensitivity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture decode sensitivity 2 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_decode_sensitivity_2(apds9960_handle_t *handle, int32_t *sensitivity);

/**
 * @brief     set the configuration
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] conf is the chip configuration
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set conf failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_conf(apds9960_handle_t *handle, apds9960_conf_t conf, apds9960_bool_t enable);

/**
 * @brief      get the configuration
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  conf is the chip configuration
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get conf failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_conf(apds9960_handle_t *handle, apds9960_conf_t conf, apds9960_bool_t *enable);

/**
 * @brief     set the adc integration time
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] integration_time is the adc integration time
 * @return    status code
 *            - 0 success
 *            - 1 set adc integration time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_adc_integration_time(apds9960_handle_t *handle, uint8_t integration_time);

/**
 * @brief      get the adc integration time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *integration_time points to an adc integration time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get adc integration time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_adc_integration_time(apds9960_handle_t *handle, uint8_t *integration_time);

/**
 * @brief      convert the adc integration time to the register raw data
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  ms is the integration time
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_adc_integration_time_convert_to_register(apds9960_handle_t *handle, float ms, uint8_t *reg);

/**
 * @brief      convert the register raw data to the integration time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *ms points to an adc integration time buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_adc_integration_time_convert_to_data(apds9960_handle_t *handle, uint8_t reg, float *ms);

/**
 * @brief     set the wait time
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] wait_time is the wait time
 * @return    status code
 *            - 0 success
 *            - 1 set wait time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_wait_time(apds9960_handle_t *handle, uint8_t wait_time);

/**
 * @brief      get the wait time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *wait_time points to a wait time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get wait time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_wait_time(apds9960_handle_t *handle, uint8_t *wait_time);

/**
 * @brief      convert the wait time to the register raw data
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  ms is the wait time
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 1 get configuration register 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_wait_time_convert_to_register(apds9960_handle_t *handle, float ms, uint8_t *reg);

/**
 * @brief      convert the register raw data to the wait time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *ms points to a wait time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get configuration register 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_wait_time_convert_to_data(apds9960_handle_t *handle, uint8_t reg, float *ms);

/**
 * @brief     set the als interrupt low threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the low threshold
 * @return    status code
 *            - 0 success
 *            - 1 set als interrupt low threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_als_interrupt_low_threshold(apds9960_handle_t *handle, uint16_t threshold);

/**
 * @brief      get the als interrupt low threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a low threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get als interrupt low threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_als_interrupt_low_threshold(apds9960_handle_t *handle, uint16_t *threshold);

/**
 * @brief     set the als interrupt high threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the high threshold
 * @return    status code
 *            - 0 success
 *            - 1 set als interrupt high threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_als_interrupt_high_threshold(apds9960_handle_t *handle, uint16_t threshold);

/**
 * @brief      get the als interrupt high threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a high threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get als interrupt high threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_als_interrupt_high_threshold(apds9960_handle_t *handle, uint16_t *threshold);

/**
 * @brief     set the proximity interrupt low threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the low threshold
 * @return    status code
 *            - 0 success
 *            - 1 set proximity interrupt low threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_interrupt_low_threshold(apds9960_handle_t *handle, uint8_t threshold);

/**
 * @brief      get the proximity interrupt low threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a low threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity interrupt low threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_interrupt_low_threshold(apds9960_handle_t *handle, uint8_t *threshold);

/**
 * @brief     set the proximity interrupt high threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the high threshold
 * @return    status code
 *            - 0 success
 *            - 1 set proximity interrupt high threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_interrupt_high_threshold(apds9960_handle_t *handle, uint8_t threshold);

/**
 * @brief      get the proximity interrupt high threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a high threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity interrupt high threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_interrupt_high_threshold(apds9960_handle_t *handle, uint8_t *threshold);

/**
 * @brief     set the proximity interrupt cycle
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] cycle is the proximity interrupt cycle
 * @return    status code
 *            - 0 success
 *            - 1 set proximity interrupt cycle failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_interrupt_cycle(apds9960_handle_t *handle, apds9960_proximity_interrupt_cycle_t cycle);

/**
 * @brief      get the proximity interrupt cycle
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *cycle points to a proximity interrupt cycle buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity interrupt cycle failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_interrupt_cycle(apds9960_handle_t *handle, apds9960_proximity_interrupt_cycle_t *cycle);

/**
 * @brief     set the als interrupt cycle
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] cycle is the als interrupt cycle
 * @return    status code
 *            - 0 success
 *            - 1 set als interrupt cycle failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_als_interrupt_cycle(apds9960_handle_t *handle, apds9960_als_interrupt_cycle_t cycle);

/**
 * @brief      get the als interrupt cycle
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *cycle points to an als interrupt cycle buffer
 * @return     status code
 *             - 0 success
 *             - 1 get als interrupt cycle failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_als_interrupt_cycle(apds9960_handle_t *handle, apds9960_als_interrupt_cycle_t *cycle);

/**
 * @brief     enable or disable the wait long
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set wait long failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_wait_long(apds9960_handle_t *handle, apds9960_bool_t enable);

/**
 * @brief      get the wait long status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get wait long failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_wait_long(apds9960_handle_t *handle, apds9960_bool_t *enable);

/**
 * @brief     set the proximity pulse length
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] len is the proximity pulse length
 * @return    status code
 *            - 0 success
 *            - 1 set proximity pulse length failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_pulse_length(apds9960_handle_t *handle, apds9960_proximity_pulse_length_t len);

/**
 * @brief      get the proximity pulse length
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *len points to a proximity pulse length buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity pulse length failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_pulse_length(apds9960_handle_t *handle, apds9960_proximity_pulse_length_t *len);

/**
 * @brief     set the proximity pulse count
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] count is the proximity pulse count
 * @return    status code
 *            - 0 success
 *            - 1 set proximity pulse count failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 count is over 63
 * @note      none
 */
uint8_t apds9960_set_proximity_pulse_count(apds9960_handle_t *handle, uint16_t count);

/**
 * @brief      get the proximity pulse count
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *count points to a proximity pulse count buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity pulse count failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_get_proximity_pulse_count(apds9960_handle_t *handle, uint16_t *count);

/**
 * @brief     set the led current
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] current is the led current
 * @return    status code
 *            - 0 success
 *            - 1 set led current failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_led_current(apds9960_handle_t *handle, apds9960_led_current_t current);

/**
 * @brief      get the led current
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *current points to a led current buffer
 * @return     status code
 *             - 0 success
 *             - 1 get led current failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_led_current(apds9960_handle_t *handle, apds9960_led_current_t *current);

/**
 * @brief     set the proximity gain
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] gain is the proximity gain
 * @return    status code
 *            - 0 success
 *            - 1 set proximity gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_gain(apds9960_handle_t *handle, apds9960_proximity_gain_t gain);

/**
 * @brief      get the proximity gain
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *gain points to a proximity gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_gain(apds9960_handle_t *handle, apds9960_proximity_gain_t *gain);

/**
 * @brief     set the als color gain
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] gain is the als color gain
 * @return    status code
 *            - 0 success
 *            - 1 set als color gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_als_color_gain(apds9960_handle_t *handle, apds9960_als_color_gain_t gain);

/**
 * @brief      get the als color gain
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *gain points to an als color gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get als color gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_als_color_gain(apds9960_handle_t *handle, apds9960_als_color_gain_t *gain);

/**
 * @brief     set the saturation interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] saturation is the saturation interrupt type
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set saturation interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_saturation_interrupt(apds9960_handle_t *handle, apds9960_saturation_interrupt_t saturation, apds9960_bool_t enable);

/**
 * @brief      get the saturation interrupt
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  saturation is the saturation interrupt type
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get saturation interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_saturation_interrupt(apds9960_handle_t *handle, apds9960_saturation_interrupt_t saturation, apds9960_bool_t *enable);

/**
 * @brief     set the led boost
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] boost is the led boost
 * @return    status code
 *            - 0 success
 *            - 1 set led boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_led_boost(apds9960_handle_t *handle, apds9960_led_boost_t boost);

/**
 * @brief      get the led boost
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *boost points to a led boost buffer
 * @return     status code
 *             - 0 success
 *             - 1 get led boost failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_led_boost(apds9960_handle_t *handle, apds9960_led_boost_t *boost);

/**
 * @brief      get the status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_status(apds9960_handle_t *handle, uint8_t *status);

/**
 * @brief     set the proximity up right offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the proximity offset
 * @return    status code
 *            - 0 success
 *            - 1 set proximity up right offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_up_right_offset(apds9960_handle_t *handle, int8_t offset);

/**
 * @brief      get the proximity up right offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a proximity offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity up right offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_up_right_offset(apds9960_handle_t *handle, int8_t *offset);

/**
 * @brief     set the proximity down left offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the proximity offset
 * @return    status code
 *            - 0 success
 *            - 1 set proximity down left offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_down_left_offset(apds9960_handle_t *handle, int8_t offset);

/**
 * @brief      get the proximity down left offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a proximity offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity down left offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_down_left_offset(apds9960_handle_t *handle, int8_t *offset);

/**
 * @brief     enable or disable the proximity gain compensation
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set proximity gain compensation failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_gain_compensation(apds9960_handle_t *handle, apds9960_bool_t enable);

/**
 * @brief      get the proximity gain compensation status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity gain compensation failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_gain_compensation(apds9960_handle_t *handle, apds9960_bool_t *enable);

/**
 * @brief     enable or disable sleeping after interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sleep after interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_sleep_after_interrupt(apds9960_handle_t *handle, apds9960_bool_t enable);

/**
 * @brief      get the sleeping after interrupt status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sleep after interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_sleep_after_interrupt(apds9960_handle_t *handle, apds9960_bool_t *enable);

/**
 * @brief     enable or disable the proximity mask
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] mask is the proximity mask
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set proximity mask failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_mask(apds9960_handle_t *handle, apds9960_proximity_mask_t mask, apds9960_bool_t enable);

/**
 * @brief      get the proximity mask status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  mask is the proximity mask
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity mask failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_mask(apds9960_handle_t *handle, apds9960_proximity_mask_t mask, apds9960_bool_t *enable);

/**
 * @brief     set the gesture proximity enter threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the gesture proximity enter threshold
 * @return    status code
 *            - 0 success
 *            - 1 set gesture proximity enter threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_proximity_enter_threshold(apds9960_handle_t *handle, uint8_t threshold);

/**
 * @brief      get the gesture proximity enter threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a gesture proximity enter threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture proximity enter threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_proximity_enter_threshold(apds9960_handle_t *handle, uint8_t *threshold);

/**
 * @brief     set the gesture proximity exit threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the gesture proximity exit threshold
 * @return    status code
 *            - 0 success
 *            - 1 set gesture proximity exit threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_proximity_exit_threshold(apds9960_handle_t *handle, uint8_t threshold);

/**
 * @brief      get the gesture proximity exit threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a gesture proximity exit threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture proximity exit threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_proximity_exit_threshold(apds9960_handle_t *handle, uint8_t *threshold);

/**
 * @brief     set the gesture fifo threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the gesture fifo threshold
 * @return    status code
 *            - 0 success
 *            - 1 set gesture fifo threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_fifo_threshold(apds9960_handle_t *handle, apds9960_gesture_fifo_threshold_t threshold);

/**
 * @brief      get the gesture fifo threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a gesture fifo threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture fifo threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_fifo_threshold(apds9960_handle_t *handle, apds9960_gesture_fifo_threshold_t *threshold);

/**
 * @brief     set the gesture exit persistence
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] persistence is the gesture exit persistence
 * @return    status code
 *            - 0 success
 *            - 1 set gesture exit persistence failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_exit_persistence(apds9960_handle_t *handle, apds9960_gesture_exit_persistence_t persistence);

/**
 * @brief      get the gesture exit persistence
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *persistence points to a gesture exit persistence buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture exit persistence failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_exit_persistence(apds9960_handle_t *handle, apds9960_gesture_exit_persistence_t *persistence);

/**
 * @brief     set the gesture exit mask
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] mask is the exit mask
 * @return    status code
 *            - 0 success
 *            - 1 set gesture exit mask failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 mask is over 0xF
 * @note      none
 */
uint8_t apds9960_set_gesture_exit_mask(apds9960_handle_t *handle, uint8_t mask);

/**
 * @brief      get the gesture exit mask
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *mask points to an exit mask buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture exit mask failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_exit_mask(apds9960_handle_t *handle, uint8_t *mask);

/**
 * @brief     set the gesture gain
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] gain is the gesture gain
 * @return    status code
 *            - 0 success
 *            - 1 set gesture gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_gain(apds9960_handle_t *handle, apds9960_gesture_gain_control_t gain);

/**
 * @brief      get the gesture gain
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *gain points to a gesture gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_gain(apds9960_handle_t *handle, apds9960_gesture_gain_control_t *gain);

/**
 * @brief     set the gesture led current
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] current is the gesture led current
 * @return    status code
 *            - 0 success
 *            - 1 set gesture led current failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_led_current(apds9960_handle_t *handle, apds9960_gesture_led_current_t current);

/**
 * @brief      get the gesture led current
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *current points to a gesture led current buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture led current failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_led_current(apds9960_handle_t *handle, apds9960_gesture_led_current_t *current);

/**
 * @brief     set the gesture wait time
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] t is the gesture wait time
 * @return    status code
 *            - 0 success
 *            - 1 set gesture wait time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_wait_time(apds9960_handle_t *handle, apds9960_gesture_wait_time_t t);

/**
 * @brief      get the gesture wait time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *t points to a gesture wait time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture wait time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_wait_time(apds9960_handle_t *handle, apds9960_gesture_wait_time_t *t);

/**
 * @brief     set the gesture up offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the gesture up offset
 * @return    status code
 *            - 0 success
 *            - 1 set gesture up offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_up_offset(apds9960_handle_t *handle, int8_t offset);

/**
 * @brief      get the gesture up offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a gesture up offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture up offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_up_offset(apds9960_handle_t *handle, int8_t *offset);

/**
 * @brief     set the gesture down offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the gesture down offset
 * @return    status code
 *            - 0 success
 *            - 1 set gesture down offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_down_offset(apds9960_handle_t *handle, int8_t offset);

/**
 * @brief      get the gesture down offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a gesture down offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture down offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_down_offset(apds9960_handle_t *handle, int8_t *offset);

/**
 * @brief     set the gesture left offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the gesture left offset
 * @return    status code
 *            - 0 success
 *            - 1 set gesture left offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_left_offset(apds9960_handle_t *handle, int8_t offset);

/**
 * @brief      get the gesture left offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a gesture left offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture left offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_left_offset(apds9960_handle_t *handle, int8_t *offset);

/**
 * @brief     set the gesture right offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the gesture right offset
 * @return    status code
 *            - 0 success
 *            - 1 set gesture right offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_right_offset(apds9960_handle_t *handle, int8_t offset);

/**
 * @brief      get the gesture right offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a gesture right offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture right offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_right_offset(apds9960_handle_t *handle, int8_t *offset);

/**
 * @brief     set the gesture pulse length
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] len is the gesture pulse length
 * @return    status code
 *            - 0 success
 *            - 1 set gesture pulse length failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_pulse_length(apds9960_handle_t *handle, apds9960_gesture_pulse_length_t len);

/**
 * @brief      get the gesture pulse length
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *len points to a gesture pulse length buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture pulse length failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_pulse_length(apds9960_handle_t *handle, apds9960_gesture_pulse_length_t *len);

/**
 * @brief     set the gesture pulse count
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] count is the gesture pulse count
 * @return    status code
 *            - 0 success
 *            - 1 set gesture pulse count failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 count is over 63
 * @note      none
 */
uint8_t apds9960_set_gesture_pulse_count(apds9960_handle_t *handle, uint16_t count);

/**
 * @brief      get the gesture pulse count
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *count points to a gesture pulse count buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture pulse count failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_pulse_count(apds9960_handle_t *handle, uint16_t *count);

/**
 * @brief     set the gesture dimension
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] s is the gesture dimension
 * @return    status code
 *            - 0 success
 *            - 1 set gesture dimension failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_dimension(apds9960_handle_t *handle, apds9960_gesture_dimension_select_t s);

/**
 * @brief      get the gesture dimension
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *s points to a gesture dimension buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture dimension failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_dimension_select(apds9960_handle_t *handle, apds9960_gesture_dimension_select_t *s);

/**
 * @brief     clear the gesture fifo status
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 gesture fifo clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_gesture_fifo_clear(apds9960_handle_t *handle);

/**
 * @brief     enable or disable the gesture interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set gesture interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_interrupt(apds9960_handle_t *handle, apds9960_bool_t enable);

/**
 * @brief      get the gesture interrupt status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_interrupt(apds9960_handle_t *handle, apds9960_bool_t *enable);

/**
 * @brief     enable or disable the gesture mode
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set gesture mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_mode(apds9960_handle_t *handle, apds9960_bool_t enable);

/**
 * @brief      get the gesture mode status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_mode(apds9960_handle_t *handle, apds9960_bool_t *enable);

/**
 * @brief      get the gesture fifo level
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *level points to a gesture fifo level buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture fifo level failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_fifo_level(apds9960_handle_t *handle, uint8_t *level);

/**
 * @brief      get the gesture status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_status(apds9960_handle_t *handle, uint8_t *status);

/**
 * @brief     force an interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 force interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_force_interrupt(apds9960_handle_t *handle);

/**
 * @brief     clear the proximity interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 proximity interrupt clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_proximity_interrupt_clear(apds9960_handle_t *handle);

/**
 * @brief     clear the als interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 als interrupt clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_als_interrupt_clear(apds9960_handle_t *handle);

/**
 * @brief     clear the all not gesture interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 all non gesture interrupt clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_all_non_gesture_interrupt_clear(apds9960_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup apds9960_extern_driver apds9960 extern driver function
 * @brief    apds9960 extern driver modules
 * @ingroup  apds9960_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_reg(apds9960_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_reg(apds9960_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
