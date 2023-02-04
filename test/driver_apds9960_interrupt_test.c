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
 * @file      driver_apds9960_interrupt_test.c
 * @brief     driver apds9960 interrupt test source file
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

#include "driver_apds9960_interrupt_test.h"

static apds9960_handle_t gs_handle;        /**< apds9960 handle */
static volatile uint8_t gs_flag;           /**< flag */

/**
 * @brief  interrupt test irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t apds9960_interrupt_test_irq_handler(void)
{
    if (apds9960_irq_handler(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     interface receive callback
 * @param[in] type is the interrupt type
 * @note      none
 */
static void a_callback(uint8_t type)
{
    switch (type)
    {
        case APDS9960_INTERRUPT_STATUS_GESTURE_LEFT :
        {
            apds9960_interface_debug_print("apds9960: irq gesture left.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_RIGHT :
        {
            apds9960_interface_debug_print("apds9960: irq gesture right.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_UP :
        {
            apds9960_interface_debug_print("apds9960: irq gesture up.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_DOWN :
        {
            apds9960_interface_debug_print("apds9960: irq gesture down.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_NEAR :
        {
            apds9960_interface_debug_print("apds9960: irq gesture near.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_FAR :
        {
            apds9960_interface_debug_print("apds9960: irq gesture far.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GFOV :
        {
            apds9960_interface_debug_print("apds9960: irq gesture fifo overflow.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GVALID :
        {
            apds9960_interface_debug_print("apds9960: irq gesture fifo data.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_CPSAT :
        {
            apds9960_interface_debug_print("apds9960: irq clear photo diode saturation.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_PGSAT :
        {
            apds9960_interface_debug_print("apds9960: irq analog saturation.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_PINT :
        {
            uint8_t res;
            uint8_t proximity;
            
            /* read proximity */
            proximity = 0;
            res = apds9960_read_proximity(&gs_handle, (uint8_t *)&proximity);
            if (res != 0)
            {
                apds9960_interface_debug_print("apds9960: read proximity failed.\n");
            }
            apds9960_interface_debug_print("apds9960: proximity is 0x%02X.\n", proximity);
            gs_flag = 1;
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_AINT :
        {
            uint8_t res;
            uint16_t red, green, blue, clear;
            
            /* read rgbc */
            red = 0;
            green = 0;
            blue = 0;
            clear = 0;
            res = apds9960_read_rgbc(&gs_handle, (uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
            if (res != 0)
            {
                apds9960_interface_debug_print("apds9960: read rgbc failed.\n");
            }
            /* output */
            apds9960_interface_debug_print("apds9960: red is 0x%04X.\n", red);
            apds9960_interface_debug_print("apds9960: green is 0x%04X.\n", green);
            apds9960_interface_debug_print("apds9960: blue is 0x%04X.\n", blue);
            apds9960_interface_debug_print("apds9960: clear is 0x%04X.\n", clear);
            gs_flag = 1;
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GINT :
        {
            apds9960_interface_debug_print("apds9960: irq gesture interrupt.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_PVALID :
        {
            break;
        }
        case APDS9960_INTERRUPT_STATUS_AVALID :
        {
            break;
        }
        default :
        {
            apds9960_interface_debug_print("apds9960: irq unknown.\n");
            
            break;
        }
    }
}

/**
 * @brief     interrupt test
 * @param[in] times is the test times
 * @param[in] als_low_threshold is the als low threshold
 * @param[in] als_high_threshold is the als high threshold
 * @param[in] proximity_low_threshold is the proximity low threshold
 * @param[in] proximity_high_threshold is the proximity high threshold
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t apds9960_interrupt_test(uint32_t times, uint16_t als_low_threshold, uint16_t als_high_threshold,
                                uint8_t proximity_low_threshold, uint8_t proximity_high_threshold)
{
    uint8_t res;
    uint8_t reg;
    uint32_t i;
    apds9960_info_t info;
    
    /* link interface function */
    DRIVER_APDS9960_LINK_INIT(&gs_handle, apds9960_handle_t);
    DRIVER_APDS9960_LINK_IIC_INIT(&gs_handle, apds9960_interface_iic_init);
    DRIVER_APDS9960_LINK_IIC_DEINIT(&gs_handle, apds9960_interface_iic_deinit);
    DRIVER_APDS9960_LINK_IIC_READ(&gs_handle, apds9960_interface_iic_read);
    DRIVER_APDS9960_LINK_IIC_WRITE(&gs_handle, apds9960_interface_iic_write);
    DRIVER_APDS9960_LINK_DELAY_MS(&gs_handle, apds9960_interface_delay_ms);
    DRIVER_APDS9960_LINK_DEBUG_PRINT(&gs_handle, apds9960_interface_debug_print);
    DRIVER_APDS9960_LINK_RECEIVE_CALLBACK(&gs_handle, a_callback);
    
    /* get information */
    res = apds9960_info(&info);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip info */
        apds9960_interface_debug_print("apds9960: chip is %s.\n", info.chip_name);
        apds9960_interface_debug_print("apds9960: manufacturer is %s.\n", info.manufacturer_name);
        apds9960_interface_debug_print("apds9960: interface is %s.\n", info.interface);
        apds9960_interface_debug_print("apds9960: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        apds9960_interface_debug_print("apds9960: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        apds9960_interface_debug_print("apds9960: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        apds9960_interface_debug_print("apds9960: max current is %0.2fmA.\n", info.max_current_ma);
        apds9960_interface_debug_print("apds9960: max temperature is %0.1fC.\n", info.temperature_max);
        apds9960_interface_debug_print("apds9960: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start interrupt test */
    apds9960_interface_debug_print("apds9960: start interrupt test.\n");
    
    /* init the apds9960 */
    res = apds9960_init(&gs_handle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: init failed.\n");
       
        return 1;
    }
    
    /* power on */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_POWER_ON, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable wait time */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_WAIT_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable proximity detect */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_DETECT_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable als */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable als interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_INTERRUPT_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable proximity interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_INTERRUPT_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable gesture */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_GESTURE_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert adc integration time */
    res = apds9960_adc_integration_time_convert_to_register(&gs_handle, 103.0f, (uint8_t *)&reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: adc integration time convert to register failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set adc integration time */
    res = apds9960_set_adc_integration_time(&gs_handle, reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set adc integration time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable wait long */
    res = apds9960_set_wait_long(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set wait long failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wait time convert to register */
    res = apds9960_wait_time_convert_to_register(&gs_handle, 10.0f, (uint8_t *)&reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: wait time convert to register failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set wait time */
    res = apds9960_set_wait_time(&gs_handle, reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set als interrupt low threshold */
    res = apds9960_set_als_interrupt_low_threshold(&gs_handle, als_low_threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt low threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set als interrupt high threshold */
    res = apds9960_set_als_interrupt_high_threshold(&gs_handle, als_high_threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt high threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity interrupt low threshold */
    res = apds9960_set_proximity_interrupt_low_threshold(&gs_handle, proximity_low_threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt low threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity interrupt high threshold */
    res = apds9960_set_proximity_interrupt_high_threshold(&gs_handle, proximity_high_threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt high threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* proximity interrupt cycle 2 */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_2);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* als interrupt cycle 2 */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_2);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity pulse length */
    res = apds9960_set_proximity_pulse_length(&gs_handle, APDS9960_PROXIMITY_PULSE_LENGTH_8_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity pulse count */
    res = apds9960_set_proximity_pulse_count(&gs_handle, 7);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity pulse count failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set led current */
    res = apds9960_set_led_current(&gs_handle, APDS9960_LED_CURRENT_100_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity gain */
    res = apds9960_set_proximity_gain(&gs_handle, APDS9960_PROXIMITY_GAIN_4X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set als color gain */
    res = apds9960_set_als_color_gain(&gs_handle, APDS9960_ALS_COLOR_GAIN_4X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als color gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable proximity saturation interrupt */
    res = apds9960_set_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable clear photo diode saturation interrupt */
    res = apds9960_set_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_CLEAR_PHOTODIODE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* 100% */
    res = apds9960_set_led_boost(&gs_handle, APDS9960_LED_BOOST_100_PERCENTAGE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led boost failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity up right offset */
    res = apds9960_set_proximity_up_right_offset(&gs_handle, 0);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity up right offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity down left offset */
    res = apds9960_set_proximity_down_left_offset(&gs_handle, 0);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity down left offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set proximity gain compensation */
    res = apds9960_set_proximity_gain_compensation(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain compensation failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable */
    res = apds9960_set_sleep_after_interrupt(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set sleep after interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable proximity mask up */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_UP, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable proximity mask down */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_DOWN, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable proximity mask left */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_LEFT, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable proximity mask right */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_RIGHT, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture proximity enter threshold */
    res = apds9960_set_gesture_proximity_enter_threshold(&gs_handle, 0x00);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture proximity enter threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture proximity exit threshold */
    res = apds9960_set_gesture_proximity_exit_threshold(&gs_handle, 0xFF);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture proximity exit threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture fifo threshold */
    res = apds9960_set_gesture_fifo_threshold(&gs_handle, APDS9960_GESTURE_FIFO_THRESHOLD_8_DATASET);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture fifo threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture exit persistence */
    res = apds9960_set_gesture_exit_persistence(&gs_handle, APDS9960_GESTURE_EXIT_PERSISTENCE_1ST);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture exit persistence failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture exit mask */
    res = apds9960_set_gesture_exit_mask(&gs_handle, 0x00);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture exit mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture gain */
    res = apds9960_set_gesture_gain(&gs_handle, APDS9960_GESTURE_GAIN_2X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture led current */
    res = apds9960_set_gesture_led_current(&gs_handle, APDS9960_GESTURE_LED_CURRENT_100_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture wait time */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_GESTURE_WAIT_TIME_2P8_MS);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture up offset */
    res = apds9960_set_gesture_up_offset(&gs_handle, 0);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture up offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture down offset */
    res = apds9960_set_gesture_down_offset(&gs_handle, 0);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture down offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture left offset */
    res = apds9960_set_gesture_left_offset(&gs_handle, 0);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture left offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture right offset */
    res = apds9960_set_gesture_right_offset(&gs_handle, 0);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture right offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture pulse length */
    res = apds9960_set_gesture_pulse_length(&gs_handle, APDS9960_GESTURE_PULSE_LENGTH_32_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture pulse count */
    res = apds9960_set_gesture_pulse_count(&gs_handle, 9);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture pulse count failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture dimension */
    res = apds9960_set_gesture_dimension(&gs_handle, APDS9960_GESTURE_DIMENSION_SELECT_BOTH_PAIRS_ACTIVE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture dimension failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* gesture fifo clear */
    res = apds9960_gesture_fifo_clear(&gs_handle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: gesture fifo clear failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture interrupt */
    res = apds9960_set_gesture_interrupt(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gesture mode */
    res = apds9960_set_gesture_mode(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture mode failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* all non gesture interrupt clear */
    res = apds9960_all_non_gesture_interrupt_clear(&gs_handle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: all non gesture interrupt clear failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable wait time */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_WAIT_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable proximity detect */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_DETECT_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable als */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable als interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_INTERRUPT_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable proximity interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_INTERRUPT_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    
    gs_flag = 0;
    for (i = 0; i < times; i++)
    {
        while (1)
        {
            if (gs_flag != 0)
            {
                gs_flag = 0;
                
                /* 1000 ms */
                apds9960_interface_delay_ms(100);
                
                break;
            }
            else
            {
                /* 1000 ms */
                apds9960_interface_delay_ms(100); 
                
                continue;
            }
        }
    }
    
    /* finish interrupt test */
    apds9960_interface_debug_print("apds9960: finish interrupt test.\n");
    (void)apds9960_deinit(&gs_handle);
    
    return 0;
}
