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
 * @file      driver_apds9960_basic.c
 * @brief     driver apds9960 basic source file
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

#include "driver_apds9960_basic.h"

static apds9960_handle_t gs_handle;        /**< apds9960 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t apds9960_basic_init(void)
{
    volatile uint8_t res;
    volatile uint8_t reg;
    
    /* link interface function */
    DRIVER_APDS9960_LINK_INIT(&gs_handle, apds9960_handle_t);
    DRIVER_APDS9960_LINK_IIC_INIT(&gs_handle, apds9960_interface_iic_init);
    DRIVER_APDS9960_LINK_IIC_DEINIT(&gs_handle, apds9960_interface_iic_deinit);
    DRIVER_APDS9960_LINK_IIC_READ(&gs_handle, apds9960_interface_iic_read);
    DRIVER_APDS9960_LINK_IIC_WRITE(&gs_handle, apds9960_interface_iic_write);
    DRIVER_APDS9960_LINK_DELAY_MS(&gs_handle, apds9960_interface_delay_ms);
    DRIVER_APDS9960_LINK_DEBUG_PRINT(&gs_handle, apds9960_interface_debug_print);
    DRIVER_APDS9960_LINK_RECEIVE_CALLBACK(&gs_handle, apds9960_interface_receive_callback);
    
    /* init the apds9960 */
    res = apds9960_init(&gs_handle);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: init failed.\n");
       
        return 1;
    }
    
    /* power on */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_POWER_ON, APDS9960_BOOL_TRUE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable wait time */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_WAIT_ENABLE, APDS9960_BOOL_FALSE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable proximity detect */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_DETECT_ENABLE, APDS9960_BOOL_FALSE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable als */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_ENABLE, APDS9960_BOOL_FALSE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable als interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_INTERRUPT_ENABLE, APDS9960_BOOL_FALSE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable proximity interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_INTERRUPT_ENABLE, APDS9960_BOOL_FALSE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable gesture */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_GESTURE_ENABLE, APDS9960_BOOL_FALSE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert adc integration time */
    res = apds9960_adc_integration_time_convert_to_register(&gs_handle, APDS9960_BASIC_DEFAULT_ADC_INTEGRATION_TIME, (uint8_t *)&reg);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: adc integration time convert to register failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set adc integration time */
    res = apds9960_set_adc_integration_time(&gs_handle, reg);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set adc integration time failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable wait long */
    res = apds9960_set_wait_long(&gs_handle, APDS9960_BOOL_FALSE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set wait long failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wait time convert to register */
    res = apds9960_wait_time_convert_to_register(&gs_handle, APDS9960_BASIC_DEFAULT_WAIT_TIME, (uint8_t *)&reg);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: wait time convert to register failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set wait time */
    res = apds9960_set_wait_time(&gs_handle, reg);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set wait time failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set als interrupt low threshold */
    res = apds9960_set_als_interrupt_low_threshold(&gs_handle, APDS9960_BASIC_DEFAULT_ALS_INTERRUPT_LOW_THRESHOLD);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt low threshold failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set als interrupt high threshold */
    res = apds9960_set_als_interrupt_high_threshold(&gs_handle, APDS9960_BASIC_DEFAULT_ALS_INTERRUPT_HIGH_THRESHOLD);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt high threshold failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity interrupt low threshold */
    res = apds9960_set_proximity_interrupt_low_threshold(&gs_handle, APDS9960_BASIC_DEFAULT_PROXIMITY_INTERRUPT_LOW_THRESHOLD);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt low threshold failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity interrupt high threshold */
    res = apds9960_set_proximity_interrupt_high_threshold(&gs_handle, APDS9960_BASIC_DEFAULT_PROXIMITY_INTERRUPT_HIGH_THRESHOLD);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt high threshold failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* proximity interrupt cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_BASIC_DEFAULT_PROXIMITY_INTERRUPT_CYCLE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* als interrupt cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_BASIC_DEFAULT_ALS_INTERRUPT_CYCLE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity pulse length */
    res = apds9960_set_proximity_pulse_length(&gs_handle, APDS9960_BASIC_DEFAULT_PROXIMITY_PULSE_LENGTH);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity pulse length failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity pulse count */
    res = apds9960_set_proximity_pulse_count(&gs_handle, APDS9960_BASIC_DEFAULT_PROXIMITY_PULSE_COUNT);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity pulse count failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set led current */
    res = apds9960_set_led_current(&gs_handle, APDS9960_BASIC_DEFAULT_LED_CURRENT);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set led current failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity gain */
    res = apds9960_set_proximity_gain(&gs_handle, APDS9960_BASIC_DEFAULT_PROXIMITY_GAIN);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set als color gain */
    res = apds9960_set_als_color_gain(&gs_handle, APDS9960_BASIC_DEFAULT_ALS_COLOR_GAIN);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set als color gain failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity saturation interrupt */
    res = apds9960_set_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, APDS9960_BASIC_DEFAULT_SATURATION_INTERRUPT_PROXIMITY);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set saturation interrupt failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set clear photodiode saturation interrupt */
    res = apds9960_set_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_CLEAR_PHOTODIODE, APDS9960_BASIC_DEFAULT_SATURATION_INTERRUPT_CLEAR_PHOTODIODE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set saturation interrupt failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set led boost */
    res = apds9960_set_led_boost(&gs_handle, APDS9960_BASIC_DEFAULT_LED_BOOST);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set led boost failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity up right offset */
    res = apds9960_set_proximity_up_right_offset(&gs_handle, APDS9960_BASIC_DEFAULT_PROXIMITY_UP_RIGHT_OFFSET);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity up right offset failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity down left offset */
    res = apds9960_set_proximity_down_left_offset(&gs_handle, APDS9960_BASIC_DEFAULT_PROXIMITY_DOWN_LEFT_OFFSET);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity down left offset failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity gain compensation */
    res = apds9960_set_proximity_gain_compensation(&gs_handle, APDS9960_BASIC_DEFAULT_PROXIMITY_GAIN_COMPENSATION);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain compensation failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set sleep after interrupt */
    res = apds9960_set_sleep_after_interrupt(&gs_handle, APDS9960_BASIC_DEFAULT_SLEEP_AFTER_INTERRUPT);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set sleep after interrupt failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity mask up */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_UP, APDS9960_BASIC_DEFAULT_PROXIMITY_MASK_UP);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity mask down */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_DOWN, APDS9960_BASIC_DEFAULT_PROXIMITY_MASK_DOWN);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity mask left */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_LEFT, APDS9960_BASIC_DEFAULT_PROXIMITY_MASK_LEFT);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity mask right */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_RIGHT, APDS9960_BASIC_DEFAULT_PROXIMITY_MASK_RIGHT);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture proximity enter threshold */
    res = apds9960_set_gesture_proximity_enter_threshold(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_PROXIMITY_ENTER_THRESHOLD);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture proximity enter threshold failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture proximity exit threshold */
    res = apds9960_set_gesture_proximity_exit_threshold(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_PROXIMITY_EXIT_THRESHOLD);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture proximity exit threshold failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture fifo threshold */
    res = apds9960_set_gesture_fifo_threshold(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_FIFO_THRESHOLD);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture fifo threshold failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture exit persistence */
    res = apds9960_set_gesture_exit_persistence(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_EXIT_PERSISTENCE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture exit persistence failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture exit mask */
    res = apds9960_set_gesture_exit_mask(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_EXIT_MASK);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture exit mask failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture gain */
    res = apds9960_set_gesture_gain(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_GAIN);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture gain failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture led current */
    res = apds9960_set_gesture_led_current(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_LED_CURRENT);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture led current failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture wait time */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_WAIT_TIME);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture up offset */
    res = apds9960_set_gesture_up_offset(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_UP_OFFSET);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture up offset failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture down offset */
    res = apds9960_set_gesture_down_offset(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_DOWN_OFFSET);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture down offset failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture left offset */
    res = apds9960_set_gesture_left_offset(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_LEFT_OFFSET);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture left offset failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture right offset */
    res = apds9960_set_gesture_right_offset(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_RIGHT_OFFSET);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture right offset failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture pulse length */
    res = apds9960_set_gesture_pulse_length(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_PULSE_LENGTH);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture pulse length failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture pulse count */
    res = apds9960_set_gesture_pulse_count(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_PULSE_COUNT);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture pulse count failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture dimension */
    res = apds9960_set_gesture_dimension(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_DIMENSION);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture dimension failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* gesture fifo clear */
    res = apds9960_gesture_fifo_clear(&gs_handle);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: gesture fifo clear failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture interrupt */
    res = apds9960_set_gesture_interrupt(&gs_handle, APDS9960_BASIC_DEFAULT_GESTURE_INTERRUPT);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture interrupt failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture mode */
    res = apds9960_set_gesture_mode(&gs_handle, APDS9960_BOOL_FALSE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set gesture mode failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* all non gesture interrupt clear */
    res = apds9960_all_non_gesture_interrupt_clear(&gs_handle);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: all non gesture interrupt clear failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable wait time */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_WAIT_ENABLE, APDS9960_BOOL_TRUE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable proximity detect */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_DETECT_ENABLE, APDS9960_BOOL_TRUE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable als */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_ENABLE, APDS9960_BOOL_TRUE);
    if (res)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t apds9960_basic_deinit(void)
{
    if (apds9960_deinit(&gs_handle))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

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
uint8_t apds9960_basic_read_rgbc(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear)
{
    if (apds9960_read_rgbc(&gs_handle, red, green, blue, clear))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief      basic example read proximity
 * @param[out] *proximity points to a proximity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read proximity failed
 * @note       none
 */
uint8_t apds9960_basic_read_proximity(uint8_t *proximity)
{
    if (apds9960_read_proximity(&gs_handle, proximity))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
