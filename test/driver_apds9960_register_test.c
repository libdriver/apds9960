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
 * @file      driver_apds9960_register_test.c
 * @brief     driver apds9960 register test source file
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

#include "driver_apds9960_register_test.h"
#include <stdlib.h>

static apds9960_handle_t gs_handle;        /**< apds9960 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t apds9960_register_test(void)
{
    uint8_t res;
    uint8_t integration_time, integration_time_check;
    uint8_t wait_time, wait_time_check;
    uint16_t threshold, threshold_check;
    uint8_t reg, reg_check;
    uint16_t count, count_check;
    int8_t offset, offset_check;
    uint8_t mask, mask_check;
    uint8_t status;
    uint8_t level;
    float ms, ms_check;
    int32_t sensitivity, sensitivity_check;
    apds9960_info_t info;
    apds9960_bool_t enable;
    apds9960_proximity_interrupt_cycle_t cycle;
    apds9960_als_interrupt_cycle_t als_cycle;
    apds9960_proximity_pulse_length_t len;
    apds9960_led_current_t current;
    apds9960_proximity_gain_t proximity_gain;
    apds9960_als_color_gain_t als_gain;
    apds9960_led_boost_t boost;
    apds9960_gesture_fifo_threshold_t fifo_threshold;
    apds9960_gesture_exit_persistence_t persistence;
    apds9960_gesture_gain_control_t gesture_gain;
    apds9960_gesture_led_current_t gesture_current;
    apds9960_gesture_wait_time_t gesture_wait_time;
    apds9960_gesture_pulse_length_t gesture_len;
    apds9960_gesture_dimension_select_t s;
    
    /* link interface function */
    DRIVER_APDS9960_LINK_INIT(&gs_handle, apds9960_handle_t);
    DRIVER_APDS9960_LINK_IIC_INIT(&gs_handle, apds9960_interface_iic_init);
    DRIVER_APDS9960_LINK_IIC_DEINIT(&gs_handle, apds9960_interface_iic_deinit);
    DRIVER_APDS9960_LINK_IIC_READ(&gs_handle, apds9960_interface_iic_read);
    DRIVER_APDS9960_LINK_IIC_WRITE(&gs_handle, apds9960_interface_iic_write);
    DRIVER_APDS9960_LINK_DELAY_MS(&gs_handle, apds9960_interface_delay_ms);
    DRIVER_APDS9960_LINK_DEBUG_PRINT(&gs_handle, apds9960_interface_debug_print);
    DRIVER_APDS9960_LINK_RECEIVE_CALLBACK(&gs_handle, apds9960_interface_receive_callback);
    
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
    
    /* start register test */
    apds9960_interface_debug_print("apds9960: start register test.\n");
    
    /* init the apds9960 */
    res = apds9960_init(&gs_handle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: init failed.\n");
       
        return 1;
    }
    
    /* apds9960_set_conf/apds9960_get_conf test */
    apds9960_interface_debug_print("apds9960: apds9960_set_conf/apds9960_get_conf test.\n");
    
    /* disable power on */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_POWER_ON, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable power on.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_POWER_ON, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable power on */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_POWER_ON, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable power on.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_POWER_ON, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* enable gesture */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_GESTURE_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable gesture.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_GESTURE_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable gesture */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_GESTURE_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable gesture.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_GESTURE_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable proximity interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_INTERRUPT_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable proximity interrupt.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_PROXIMITY_INTERRUPT_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable proximity interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_INTERRUPT_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable proximity interrupt.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_PROXIMITY_INTERRUPT_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable als interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_INTERRUPT_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable als interrupt.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_ALS_INTERRUPT_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable als interrupt */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_INTERRUPT_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable als interrupt.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_ALS_INTERRUPT_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable wait */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_WAIT_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable wait.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_WAIT_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable wait */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_WAIT_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable wait.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_WAIT_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable proximity detect */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_DETECT_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable proximity detect.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_PROXIMITY_DETECT_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable proximity detect */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_PROXIMITY_DETECT_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable proximity detect.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_PROXIMITY_DETECT_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable als */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_ENABLE, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable als.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_ALS_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable als */
    res = apds9960_set_conf(&gs_handle, APDS9960_CONF_ALS_ENABLE, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable als.\n");
    res = apds9960_get_conf(&gs_handle, APDS9960_CONF_ALS_ENABLE, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get conf failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check config %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* apds9960_set_adc_integration_time/apds9960_get_adc_integration_time test */
    apds9960_interface_debug_print("apds9960: apds9960_set_adc_integration_time/apds9960_get_adc_integration_time test.\n");
    
    integration_time = rand() % 256;
    res = apds9960_set_adc_integration_time(&gs_handle, integration_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set adc integration time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set adc integration time 0x%02X.\n", integration_time);
    res = apds9960_get_adc_integration_time(&gs_handle, (uint8_t *)&integration_time_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get adc integration time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check adc integration time %s.\n", integration_time == integration_time_check ? "ok" : "error");
    
    /* apds9960_set_wait_time/apds9960_get_wait_time test */
    apds9960_interface_debug_print("apds9960: apds9960_set_wait_time/apds9960_get_wait_time test.\n");
    
    wait_time = rand() % 256;
    res = apds9960_set_wait_time(&gs_handle, wait_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set wait time 0x%02X.\n", wait_time);
    res = apds9960_get_wait_time(&gs_handle, (uint8_t *)&wait_time_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check wait time %s.\n", wait_time == wait_time_check ? "ok" : "error");
    
    /* apds9960_set_als_interrupt_low_threshold/apds9960_get_als_interrupt_low_threshold test */
    apds9960_interface_debug_print("apds9960: apds9960_set_als_interrupt_low_threshold/apds9960_get_als_interrupt_low_threshold test.\n");
    
    threshold = rand() % 65536;
    res = apds9960_set_als_interrupt_low_threshold(&gs_handle, threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt low threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt low threshold 0x%04X.\n", threshold);
    res = apds9960_get_als_interrupt_low_threshold(&gs_handle, (uint16_t *)&threshold_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt low threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt low threshold %s.\n", threshold == threshold_check ? "ok" : "error");
    
    /* apds9960_set_als_interrupt_high_threshold/apds9960_get_als_interrupt_high_threshold test */
    apds9960_interface_debug_print("apds9960: apds9960_set_als_interrupt_high_threshold/apds9960_get_als_interrupt_high_threshold test.\n");
    
    threshold = rand() % 65536;
    res = apds9960_set_als_interrupt_high_threshold(&gs_handle, threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt high threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt high threshold 0x%04X.\n", threshold);
    res = apds9960_get_als_interrupt_high_threshold(&gs_handle, (uint16_t *)&threshold_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt high threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt high threshold %s.\n", threshold == threshold_check ? "ok" : "error");
    
    /* apds9960_set_proximity_interrupt_low_threshold/apds9960_get_proximity_interrupt_low_threshold test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_interrupt_low_threshold/apds9960_get_proximity_interrupt_low_threshold test.\n");
    
    reg = rand() % 256;
    res = apds9960_set_proximity_interrupt_low_threshold(&gs_handle, reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt low threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt low threshold 0x%02X.\n", reg);
    res = apds9960_get_proximity_interrupt_low_threshold(&gs_handle, (uint8_t *)&reg_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt low threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt low threshold %s.\n", reg_check == reg ? "ok" : "error");
    
    /* apds9960_set_proximity_interrupt_high_threshold/apds9960_get_proximity_interrupt_high_threshold test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_interrupt_high_threshold/apds9960_get_proximity_interrupt_high_threshold test.\n");
    
    reg = rand() % 256;
    res = apds9960_set_proximity_interrupt_high_threshold(&gs_handle, reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt high threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt high threshold 0x%02X.\n", reg);
    res = apds9960_get_proximity_interrupt_high_threshold(&gs_handle, (uint8_t *)&reg_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt high threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt high threshold %s.\n", reg_check == reg ? "ok" : "error");
    
    /* apds9960_set_proximity_interrupt_cycle/apds9960_get_proximity_interrupt_cycle test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_interrupt_cycle/apds9960_get_proximity_interrupt_cycle test.\n");
    
    /* set proximity interrupt every cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_EVERY);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt every cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_EVERY ? "ok" : "error");
    
    /* set proximity interrupt any cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_ANY);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt any cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_ANY ? "ok" : "error");
    
    /* set proximity interrupt 2 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_2);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 2 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_2 ? "ok" : "error");
    
    /* set proximity interrupt 3 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_3);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 3 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_3 ? "ok" : "error");
    
    /* set proximity interrupt 4 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_4);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 4 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_4 ? "ok" : "error");
    
    /* set proximity interrupt 5 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_5);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 5 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_5 ? "ok" : "error");
    
    /* set proximity interrupt 6 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_6);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 6 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_6 ? "ok" : "error");
    
    /* set proximity interrupt 7 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_7);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 7 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_7 ? "ok" : "error");
    
    /* set proximity interrupt 8 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_8);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 8 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_8 ? "ok" : "error");
    
    /* set proximity interrupt 9 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_9);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 9 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_9 ? "ok" : "error");
    
    /* set proximity interrupt 10 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_10);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 10 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_10 ? "ok" : "error");
    
    /* set proximity interrupt 11 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_11);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 11 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_11 ? "ok" : "error");
    
    /* set proximity interrupt 12 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_12);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 12 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_12 ? "ok" : "error");
    
    /* set proximity interrupt 13 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_13);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 13 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_13 ? "ok" : "error");
    
    /* set proximity interrupt 14 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_14);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 14 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_14 ? "ok" : "error");
    
    /* set proximity interrupt 15 cycle */
    res = apds9960_set_proximity_interrupt_cycle(&gs_handle, APDS9960_PROXIMITY_INTERRUPT_CYCLE_15);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity interrupt 15 cycle.\n");
    res = apds9960_get_proximity_interrupt_cycle(&gs_handle, &cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt cycle %s.\n", cycle == APDS9960_PROXIMITY_INTERRUPT_CYCLE_15 ? "ok" : "error");
    
    /* apds9960_set_als_interrupt_cycle/apds9960_get_als_interrupt_cycle test */
    apds9960_interface_debug_print("apds9960: apds9960_set_als_interrupt_cycle/apds9960_get_als_interrupt_cycle test.\n");
    
    /* every als cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_EVERY);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt every cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_EVERY ? "ok" : "error");
    
    /* als any cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_ANY);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt any cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_ANY ? "ok" : "error");
    
    /* als 2 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_2);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 2 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_2 ? "ok" : "error");
    
    /* als 3 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_3);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 3 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_3 ? "ok" : "error");
    
    /* als 5 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_5);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 5 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_5 ? "ok" : "error");
    
    /* als 10 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_10);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 10 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_10 ? "ok" : "error");
    
    /* als 15 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_15);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 15 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_15 ? "ok" : "error");
    
    /* als 20 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_20);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 20 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_20 ? "ok" : "error");
    
    /* als 25 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_25);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 25 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_25 ? "ok" : "error");
    
    /* als 30 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_30);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 30 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_30 ? "ok" : "error");
    
    /* als 35 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_35);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 35 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_35 ? "ok" : "error");
    
    /* als 40 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_40);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 40 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_40 ? "ok" : "error");
    
    /* als 45 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_45);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 45 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_45 ? "ok" : "error");
    
    /* als 50 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_50);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 50 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_50 ? "ok" : "error");
    
    /* als 55 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_55);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 55 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_55 ? "ok" : "error");
    
    /* als 60 cycle */
    res = apds9960_set_als_interrupt_cycle(&gs_handle, APDS9960_ALS_INTERRUPT_CYCLE_60);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als interrupt 60 cycle.\n");
    res = apds9960_get_als_interrupt_cycle(&gs_handle, &als_cycle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als interrupt cycle failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt cycle %s.\n", als_cycle == APDS9960_ALS_INTERRUPT_CYCLE_60 ? "ok" : "error");
    
    /* apds9960_set_wait_long/apds9960_get_wait_long test */
    apds9960_interface_debug_print("apds9960: apds9960_set_wait_long/apds9960_get_wait_long test.\n");
    
    /* enable wait long */
    res = apds9960_set_wait_long(&gs_handle, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set wait long failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable wait long.\n");
    res = apds9960_get_wait_long(&gs_handle, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get wait long failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check wait long %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable wait long */
    res = apds9960_set_wait_long(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set wait long failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable wait long.\n");
    res = apds9960_get_wait_long(&gs_handle, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get wait long failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check wait long %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* apds9960_set_proximity_pulse_length/apds9960_get_proximity_pulse_length test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_pulse_length/apds9960_get_proximity_pulse_length test.\n");
    
    /* proximity pulse length 4 us */
    res = apds9960_set_proximity_pulse_length(&gs_handle, APDS9960_PROXIMITY_PULSE_LENGTH_4_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: proximity pulse length 4 us.\n");
    res = apds9960_get_proximity_pulse_length(&gs_handle, &len);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity pulse length %s.\n", len == APDS9960_PROXIMITY_PULSE_LENGTH_4_US ? "ok" : "error");
    
    /* proximity pulse length 8 us */
    res = apds9960_set_proximity_pulse_length(&gs_handle, APDS9960_PROXIMITY_PULSE_LENGTH_8_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: proximity pulse length 8 us.\n");
    res = apds9960_get_proximity_pulse_length(&gs_handle, &len);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity pulse length %s.\n", len == APDS9960_PROXIMITY_PULSE_LENGTH_8_US ? "ok" : "error");
    
    /* proximity pulse length 16 us */
    res = apds9960_set_proximity_pulse_length(&gs_handle, APDS9960_PROXIMITY_PULSE_LENGTH_16_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: proximity pulse length 16 us.\n");
    res = apds9960_get_proximity_pulse_length(&gs_handle, &len);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity pulse length %s.\n", len == APDS9960_PROXIMITY_PULSE_LENGTH_16_US ? "ok" : "error");
    
    /* proximity pulse length 32 us */
    res = apds9960_set_proximity_pulse_length(&gs_handle, APDS9960_PROXIMITY_PULSE_LENGTH_32_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: proximity pulse length 32 us.\n");
    res = apds9960_get_proximity_pulse_length(&gs_handle, &len);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity pulse length %s.\n", len == APDS9960_PROXIMITY_PULSE_LENGTH_32_US ? "ok" : "error");
    
    /* apds9960_set_proximity_pulse_count/apds9960_get_proximity_pulse_count test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_pulse_count/apds9960_get_proximity_pulse_count test.\n");
    
    count = rand() % 0x3F;
    res = apds9960_set_proximity_pulse_count(&gs_handle, count);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity pulse count failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity pulse count %d.\n", count);
    res = apds9960_get_proximity_pulse_count(&gs_handle, (uint16_t *)&count_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity pulse count failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity pulse count %s.\n", count_check == count ? "ok" : "error");
    
    /* apds9960_set_led_current/apds9960_get_led_current test */
    apds9960_interface_debug_print("apds9960: apds9960_set_led_current/apds9960_get_led_current test.\n");
    
    /* 100 mA */
    res = apds9960_set_led_current(&gs_handle, APDS9960_LED_CURRENT_100_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set led current 100 mA.\n");
    res = apds9960_get_led_current(&gs_handle, &current);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check led current %s.\n", current == APDS9960_LED_CURRENT_100_MA ? "ok" : "error");
    
    /* 50 mA */
    res = apds9960_set_led_current(&gs_handle, APDS9960_LED_CURRENT_50_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set led current 50 mA.\n");
    res = apds9960_get_led_current(&gs_handle, &current);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check led current %s.\n", current == APDS9960_LED_CURRENT_50_MA ? "ok" : "error");
    
    /* 25 mA */
    res = apds9960_set_led_current(&gs_handle, APDS9960_LED_CURRENT_25_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set led current 25 mA.\n");
    res = apds9960_get_led_current(&gs_handle, &current);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check led current %s.\n", current == APDS9960_LED_CURRENT_25_MA ? "ok" : "error");
    
    /* 12.5 mA */
    res = apds9960_set_led_current(&gs_handle, APDS9960_LED_CURRENT_12P5_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set led current 12.5 mA.\n");
    res = apds9960_get_led_current(&gs_handle, &current);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check led current %s.\n", current == APDS9960_LED_CURRENT_12P5_MA ? "ok" : "error");
    
    /* apds9960_set_proximity_gain/apds9960_get_proximity_gain test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_gain/apds9960_get_proximity_gain test.\n");
    
    /* gain 1x */
    res = apds9960_set_proximity_gain(&gs_handle, APDS9960_PROXIMITY_GAIN_1X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity gain 1x.\n");
    res = apds9960_get_proximity_gain(&gs_handle, &proximity_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity gain %s.\n", proximity_gain == APDS9960_PROXIMITY_GAIN_1X ? "ok" : "error");
    
    /* gain 2x */
    res = apds9960_set_proximity_gain(&gs_handle, APDS9960_PROXIMITY_GAIN_2X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity gain 2x.\n");
    res = apds9960_get_proximity_gain(&gs_handle, &proximity_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity gain %s.\n", proximity_gain == APDS9960_PROXIMITY_GAIN_2X ? "ok" : "error");
    
    /* gain 4x */
    res = apds9960_set_proximity_gain(&gs_handle, APDS9960_PROXIMITY_GAIN_4X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity gain 4x.\n");
    res = apds9960_get_proximity_gain(&gs_handle, &proximity_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity gain %s.\n", proximity_gain == APDS9960_PROXIMITY_GAIN_4X ? "ok" : "error");
    
    /* gain 8x */
    res = apds9960_set_proximity_gain(&gs_handle, APDS9960_PROXIMITY_GAIN_8X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity gain 8x.\n");
    res = apds9960_get_proximity_gain(&gs_handle, &proximity_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity gain %s.\n", proximity_gain == APDS9960_PROXIMITY_GAIN_8X ? "ok" : "error");
    
    /* apds9960_set_als_color_gain/apds9960_get_als_color_gain test */
    apds9960_interface_debug_print("apds9960: apds9960_set_als_color_gain/apds9960_get_als_color_gain test.\n");
    
    /* gain 1x */
    res = apds9960_set_als_color_gain(&gs_handle, APDS9960_ALS_COLOR_GAIN_1X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als color gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als color gain 1x.\n");
    res = apds9960_get_als_color_gain(&gs_handle, &als_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als color gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als color gain %s.\n", als_gain == APDS9960_ALS_COLOR_GAIN_1X ? "ok" : "error");
    
    /* gain 4x */
    res = apds9960_set_als_color_gain(&gs_handle, APDS9960_ALS_COLOR_GAIN_4X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als color gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als color gain 4x.\n");
    res = apds9960_get_als_color_gain(&gs_handle, &als_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als color gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als color gain %s.\n", als_gain == APDS9960_ALS_COLOR_GAIN_4X ? "ok" : "error");
    
    /* gain 16x */
    res = apds9960_set_als_color_gain(&gs_handle, APDS9960_ALS_COLOR_GAIN_16X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als color gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als color gain 16x.\n");
    res = apds9960_get_als_color_gain(&gs_handle, &als_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als color gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als color gain %s.\n", als_gain == APDS9960_ALS_COLOR_GAIN_16X ? "ok" : "error");
    
    /* gain 64x */
    res = apds9960_set_als_color_gain(&gs_handle, APDS9960_ALS_COLOR_GAIN_64X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set als color gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set als color gain 64x.\n");
    res = apds9960_get_als_color_gain(&gs_handle, &als_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get als color gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als color gain %s.\n", als_gain == APDS9960_ALS_COLOR_GAIN_64X ? "ok" : "error");
    
    /* apds9960_set_saturation_interrupt/apds9960_get_saturation_interrupt test */
    apds9960_interface_debug_print("apds9960: apds9960_set_saturation_interrupt/apds9960_get_saturation_interrupt test.\n");
    
    /* disable proximity saturation interrupt */
    res = apds9960_set_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable proximity saturation interrupt.\n");
    res = apds9960_get_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check saturation interrupt %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable proximity saturation interrupt */
    res = apds9960_set_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable proximity saturation interrupt.\n");
    res = apds9960_get_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check saturation interrupt %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable clear photo diode saturation interrupt */
    res = apds9960_set_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable clear photo diode saturation interrupt.\n");
    res = apds9960_get_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check clear photo diode saturation interrupt %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable clear photo diode saturation interrupt */
    res = apds9960_set_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable clear photo diode saturation interrupt.\n");
    res = apds9960_get_saturation_interrupt(&gs_handle, APDS9960_SATURATION_INTERRUPT_PROXIMITY, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get saturation interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check clear photo diode saturation interrupt %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* apds9960_set_led_boost/apds9960_get_led_boost test */
    apds9960_interface_debug_print("apds9960: apds9960_set_led_boost/apds9960_get_led_boost test.\n");
    
    /* 100% */
    res = apds9960_set_led_boost(&gs_handle, APDS9960_LED_BOOST_100_PERCENTAGE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led boost failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set led boost 100%%.\n");
    res = apds9960_get_led_boost(&gs_handle, &boost);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get led boost failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check led boost %s.\n", boost == APDS9960_LED_BOOST_100_PERCENTAGE ? "ok" : "error");
    
    /* 150% */
    res = apds9960_set_led_boost(&gs_handle, APDS9960_LED_BOOST_150_PERCENTAGE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led boost failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set led boost 150%%.\n");
    res = apds9960_get_led_boost(&gs_handle, &boost);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get led boost failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check led boost %s.\n", boost == APDS9960_LED_BOOST_150_PERCENTAGE ? "ok" : "error");
    
    /* 200% */
    res = apds9960_set_led_boost(&gs_handle, APDS9960_LED_BOOST_200_PERCENTAGE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led boost failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set led boost 200%%.\n");
    res = apds9960_get_led_boost(&gs_handle, &boost);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get led boost failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check led boost %s.\n", boost == APDS9960_LED_BOOST_200_PERCENTAGE ? "ok" : "error");
    
    /* 300% */
    res = apds9960_set_led_boost(&gs_handle, APDS9960_LED_BOOST_300_PERCENTAGE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set led boost failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set led boost 300%%.\n");
    res = apds9960_get_led_boost(&gs_handle, &boost);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get led boost failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check led boost %s.\n", boost == APDS9960_LED_BOOST_300_PERCENTAGE ? "ok" : "error");
    
    /* apds9960_set_proximity_up_right_offset/apds9960_get_proximity_up_right_offset test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_up_right_offset/apds9960_get_proximity_up_right_offset test.\n");
    
    offset = rand() % 128;
    res = apds9960_set_proximity_up_right_offset(&gs_handle, offset);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity up right offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity up right offset %d.\n", offset);
    res = apds9960_get_proximity_up_right_offset(&gs_handle, (int8_t *)&offset_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity up right offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity up right offset %s.\n", offset_check == offset ? "ok" : "error");
    
    /* apds9960_set_proximity_down_left_offset/apds9960_get_proximity_down_left_offset test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_down_left_offset/apds9960_get_proximity_down_left_offset test.\n");
    
    offset = -(rand() % 128);
    res = apds9960_set_proximity_down_left_offset(&gs_handle, offset);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity down left offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set proximity down left offset %d.\n", offset);
    res = apds9960_get_proximity_down_left_offset(&gs_handle, (int8_t *)&offset_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity down left offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity down left offset %s.\n", offset_check == offset ? "ok" : "error");
    
    /* apds9960_set_proximity_gain_compensation/apds9960_get_proximity_gain_compensation test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_gain_compensation/apds9960_get_proximity_gain_compensation test.\n");
    
    /* enable */
    res = apds9960_set_proximity_gain_compensation(&gs_handle, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain compensation failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable proximity gain compensation.\n");
    res = apds9960_get_proximity_gain_compensation(&gs_handle, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity gain compensation failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity gain compensation %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable */
    res = apds9960_set_proximity_gain_compensation(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity gain compensation failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable proximity gain compensation.\n");
    res = apds9960_get_proximity_gain_compensation(&gs_handle, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity gain compensation failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity gain compensation %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* apds9960_set_sleep_after_interrupt/apds9960_get_sleep_after_interrupt test */
    apds9960_interface_debug_print("apds9960: apds9960_set_sleep_after_interrupt/apds9960_get_sleep_after_interrupt test.\n");
    
    /* enable */
    res = apds9960_set_sleep_after_interrupt(&gs_handle, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set sleep after interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable sleep after interrupt.\n");
    res = apds9960_get_sleep_after_interrupt(&gs_handle, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get sleep after interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check sleep after interrupt %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable */
    res = apds9960_set_sleep_after_interrupt(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set sleep after interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable sleep after interrupt.\n");
    res = apds9960_get_sleep_after_interrupt(&gs_handle, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get sleep after interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check sleep after interrupt %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* apds9960_set_proximity_mask/apds9960_get_proximity_mask test */
    apds9960_interface_debug_print("apds9960: apds9960_set_proximity_mask/apds9960_get_proximity_mask test.\n");
    
    /* enable proximity mask up */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_UP, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable proximity mask up.\n");
    res = apds9960_get_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_UP, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity mask %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable proximity mask up */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_UP, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable proximity mask up.\n");
    res = apds9960_get_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_UP, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity mask %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable proximity mask down */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_DOWN, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable proximity mask down.\n");
    res = apds9960_get_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_DOWN, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity mask %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable proximity mask down */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_DOWN, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable proximity mask down.\n");
    res = apds9960_get_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_DOWN, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity mask %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable proximity mask left */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_LEFT, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable proximity mask left.\n");
    res = apds9960_get_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_LEFT, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity mask %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable proximity mask left */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_LEFT, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable proximity mask left.\n");
    res = apds9960_get_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_LEFT, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity mask %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* enable proximity mask right */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_RIGHT, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable proximity mask right.\n");
    res = apds9960_get_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_RIGHT, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity mask %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable proximity mask right */
    res = apds9960_set_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_RIGHT, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable proximity mask right.\n");
    res = apds9960_get_proximity_mask(&gs_handle, APDS9960_PROXIMITY_MASK_RIGHT, (apds9960_bool_t *)&enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get proximity mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity mask %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* apds9960_set_gesture_proximity_enter_threshold/apds9960_get_gesture_proximity_enter_threshold test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_proximity_enter_threshold/apds9960_get_gesture_proximity_enter_threshold test.\n");
    
    reg  = rand() % 256;
    res = apds9960_set_gesture_proximity_enter_threshold(&gs_handle, reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture proximity enter threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture proximity enter threshold 0x%02X.\n", reg);
    res = apds9960_get_gesture_proximity_enter_threshold(&gs_handle, (uint8_t *)&reg_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture proximity enter threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture proximity enter threshold %s.\n", reg == reg_check ? "ok" : "error");
    
    /* apds9960_set_gesture_proximity_exit_threshold/apds9960_get_gesture_proximity_exit_threshold test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_proximity_exit_threshold/apds9960_get_gesture_proximity_exit_threshold test.\n");
    
    reg  = rand() % 256;
    res = apds9960_set_gesture_proximity_exit_threshold(&gs_handle, reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture proximity exit threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture proximity exit threshold 0x%02X.\n", reg);
    res = apds9960_get_gesture_proximity_exit_threshold(&gs_handle, (uint8_t *)&reg_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture proximity exit threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture proximity exit threshold %s.\n", reg == reg_check ? "ok" : "error");
    
    /* apds9960_set_gesture_fifo_threshold/apds9960_get_gesture_fifo_threshold test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_fifo_threshold/apds9960_get_gesture_fifo_threshold test.\n");
    
    /* set gesture fifo threshold 1 dataset */
    res = apds9960_set_gesture_fifo_threshold(&gs_handle, APDS9960_GESTURE_FIFO_THRESHOLD_1_DATASET);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture fifo threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture fifo threshold 1 dataset.\n");
    res = apds9960_get_gesture_fifo_threshold(&gs_handle, &fifo_threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture fifo threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture fifo threshold %s.\n", fifo_threshold == APDS9960_GESTURE_FIFO_THRESHOLD_1_DATASET ? "ok" : "error");
    
    /* set gesture fifo threshold 4 dataset */
    res = apds9960_set_gesture_fifo_threshold(&gs_handle, APDS9960_GESTURE_FIFO_THRESHOLD_4_DATASET);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture fifo threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture fifo threshold 4 dataset.\n");
    res = apds9960_get_gesture_fifo_threshold(&gs_handle, &fifo_threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture fifo threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture fifo threshold %s.\n", fifo_threshold == APDS9960_GESTURE_FIFO_THRESHOLD_4_DATASET ? "ok" : "error");
    
    /* set gesture fifo threshold 8 dataset */
    res = apds9960_set_gesture_fifo_threshold(&gs_handle, APDS9960_GESTURE_FIFO_THRESHOLD_8_DATASET);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture fifo threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture fifo threshold 8 dataset.\n");
    res = apds9960_get_gesture_fifo_threshold(&gs_handle, &fifo_threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture fifo threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture fifo threshold %s.\n", fifo_threshold == APDS9960_GESTURE_FIFO_THRESHOLD_8_DATASET ? "ok" : "error");
    
    /* set gesture fifo threshold 16 dataset */
    res = apds9960_set_gesture_fifo_threshold(&gs_handle, APDS9960_GESTURE_FIFO_THRESHOLD_16_DATASET);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture fifo threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture fifo threshold 16 dataset.\n");
    res = apds9960_get_gesture_fifo_threshold(&gs_handle, &fifo_threshold);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture fifo threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture fifo threshold %s.\n", fifo_threshold == APDS9960_GESTURE_FIFO_THRESHOLD_16_DATASET ? "ok" : "error");
    
    /* apds9960_set_gesture_exit_persistence/apds9960_get_gesture_exit_persistence test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_exit_persistence/apds9960_get_gesture_exit_persistence test.\n");
    
    /* set gesture exit persistence 1st */
    res = apds9960_set_gesture_exit_persistence(&gs_handle, APDS9960_GESTURE_EXIT_PERSISTENCE_1ST);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture exit persistence failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture exit persistence 1st.\n");
    res = apds9960_get_gesture_exit_persistence(&gs_handle, &persistence);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture exit persistence failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture exit persistence %s.\n", persistence == APDS9960_GESTURE_EXIT_PERSISTENCE_1ST ? "ok" : "error");
    
    /* set gesture exit persistence 2nd */
    res = apds9960_set_gesture_exit_persistence(&gs_handle, APDS9960_GESTURE_EXIT_PERSISTENCE_2ND);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture exit persistence failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture exit persistence 2nd.\n");
    res = apds9960_get_gesture_exit_persistence(&gs_handle, &persistence);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture exit persistence failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture exit persistence %s.\n", persistence == APDS9960_GESTURE_EXIT_PERSISTENCE_2ND ? "ok" : "error");
    
    /* set gesture exit persistence 4th */
    res = apds9960_set_gesture_exit_persistence(&gs_handle, APDS9960_GESTURE_EXIT_PERSISTENCE_4TH);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture exit persistence failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture exit persistence 4th.\n");
    res = apds9960_get_gesture_exit_persistence(&gs_handle, &persistence);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture exit persistence failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture exit persistence %s.\n", persistence == APDS9960_GESTURE_EXIT_PERSISTENCE_4TH ? "ok" : "error");
    
    /* set gesture exit persistence 7th */
    res = apds9960_set_gesture_exit_persistence(&gs_handle, APDS9960_GESTURE_EXIT_PERSISTENCE_7TH);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture exit persistence failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture exit persistence 7th.\n");
    res = apds9960_get_gesture_exit_persistence(&gs_handle, &persistence);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture exit persistence failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture exit persistence %s.\n", persistence == APDS9960_GESTURE_EXIT_PERSISTENCE_7TH ? "ok" : "error");
    
    /* apds9960_set_gesture_exit_mask/apds9960_get_gesture_exit_mask test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_exit_mask/apds9960_get_gesture_exit_mask test.\n");
    
    mask = rand() % 0xF;
    res = apds9960_set_gesture_exit_mask(&gs_handle, mask);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture exit mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture exit mask 0x%01X.\n", mask);
    res = apds9960_get_gesture_exit_mask(&gs_handle, (uint8_t *)&mask_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture exit mask failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture exit mask %s.\n", mask_check == mask ? "ok" : "error");
    
    /* apds9960_set_gesture_gain/apds9960_get_gesture_gain test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_gain/apds9960_get_gesture_gain test.\n");
    
    /* set gesture gain 1x */
    res = apds9960_set_gesture_gain(&gs_handle, APDS9960_GESTURE_GAIN_1X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture gain 1x.\n");
    res = apds9960_get_gesture_gain(&gs_handle, &gesture_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture gain %s.\n", gesture_gain == APDS9960_GESTURE_GAIN_1X ? "ok" : "error");
    
    /* set gesture gain 2x */
    res = apds9960_set_gesture_gain(&gs_handle, APDS9960_GESTURE_GAIN_2X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture gain 2x.\n");
    res = apds9960_get_gesture_gain(&gs_handle, &gesture_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture gain %s.\n", gesture_gain == APDS9960_GESTURE_GAIN_2X ? "ok" : "error");
    
    /* set gesture gain 4x */
    res = apds9960_set_gesture_gain(&gs_handle, APDS9960_GESTURE_GAIN_4X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture gain 4x.\n");
    res = apds9960_get_gesture_gain(&gs_handle, &gesture_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture gain %s.\n", gesture_gain == APDS9960_GESTURE_GAIN_4X ? "ok" : "error");
    
    /* set gesture gain 8x */
    res = apds9960_set_gesture_gain(&gs_handle, APDS9960_GESTURE_GAIN_8X);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture gain 8x.\n");
    res = apds9960_get_gesture_gain(&gs_handle, &gesture_gain);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture gain failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture gain %s.\n", gesture_gain == APDS9960_GESTURE_GAIN_8X ? "ok" : "error");
    
    /* apds9960_set_gesture_led_current/apds9960_get_gesture_led_current test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_led_current/apds9960_get_gesture_led_current test.\n");
    
    /* set gesture led current 100 mA */
    res = apds9960_set_gesture_led_current(&gs_handle, APDS9960_GESTURE_LED_CURRENT_100_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture led current 100 mA.\n");
    res = apds9960_get_gesture_led_current(&gs_handle, &gesture_current);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture led current %s.\n", gesture_current == APDS9960_GESTURE_LED_CURRENT_100_MA ? "ok" : "error");
    
    /* set gesture led current 50 mA */
    res = apds9960_set_gesture_led_current(&gs_handle, APDS9960_GESTURE_LED_CURRENT_50_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture led current 50 mA.\n");
    res = apds9960_get_gesture_led_current(&gs_handle, &gesture_current);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture led current %s.\n", gesture_current == APDS9960_GESTURE_LED_CURRENT_50_MA ? "ok" : "error");
    
    /* set gesture led current 25 mA */
    res = apds9960_set_gesture_led_current(&gs_handle, APDS9960_GESTURE_LED_CURRENT_25_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture led current 25 mA.\n");
    res = apds9960_get_gesture_led_current(&gs_handle, &gesture_current);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture led current %s.\n", gesture_current == APDS9960_GESTURE_LED_CURRENT_25_MA ? "ok" : "error");
    
    /* set gesture led current 12.5 mA */
    res = apds9960_set_gesture_led_current(&gs_handle, APDS9960_GESTURE_LED_CURRENT_12P5_MA);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture led current 12.5 mA.\n");
    res = apds9960_get_gesture_led_current(&gs_handle, &gesture_current);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture led current failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture led current %s.\n", gesture_current == APDS9960_GESTURE_LED_CURRENT_12P5_MA ? "ok" : "error");
    
    /* apds9960_set_gesture_wait_time/apds9960_get_gesture_wait_time test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_wait_time/apds9960_get_gesture_wait_time test.\n");
    
    /* set gesture wait time 0 ms */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_GESTURE_WAIT_TIME_0_MS);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture wait time 0 ms.\n");
    res = apds9960_get_gesture_wait_time(&gs_handle, &gesture_wait_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture wait time %s.\n", gesture_wait_time == APDS9960_GESTURE_WAIT_TIME_0_MS ? "ok" : "error");
    
    /* set gesture wait time 2.8 ms */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_GESTURE_WAIT_TIME_2P8_MS);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture wait time 2.8 ms.\n");
    res = apds9960_get_gesture_wait_time(&gs_handle, &gesture_wait_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture wait time %s.\n", gesture_wait_time == APDS9960_GESTURE_WAIT_TIME_2P8_MS ? "ok" : "error");
    
    /* set gesture wait time 5.6 ms */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_GESTURE_WAIT_TIME_5P6_MS);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture wait time 5.6 ms.\n");
    res = apds9960_get_gesture_wait_time(&gs_handle, &gesture_wait_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture wait time %s.\n", gesture_wait_time == APDS9960_GESTURE_WAIT_TIME_5P6_MS ? "ok" : "error");
    
    /* set gesture wait time 8.4 ms */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_GESTURE_WAIT_TIME_8P4_MS);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture wait time 8.4 ms.\n");
    res = apds9960_get_gesture_wait_time(&gs_handle, &gesture_wait_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture wait time %s.\n", gesture_wait_time == APDS9960_GESTURE_WAIT_TIME_8P4_MS ? "ok" : "error");
    
    /* set gesture wait time 14 ms */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_GESTURE_WAIT_TIME_14_MS);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture wait time 14 ms.\n");
    res = apds9960_get_gesture_wait_time(&gs_handle, &gesture_wait_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture wait time %s.\n", gesture_wait_time == APDS9960_GESTURE_WAIT_TIME_14_MS ? "ok" : "error");
    
    /* set gesture wait time 22.4 ms */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_GESTURE_WAIT_TIME_22P4_MS);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture wait time 22.4 ms.\n");
    res = apds9960_get_gesture_wait_time(&gs_handle, &gesture_wait_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture wait time %s.\n", gesture_wait_time == APDS9960_GESTURE_WAIT_TIME_22P4_MS ? "ok" : "error");
    
    /* set gesture wait time 30.8 ms */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_GESTURE_WAIT_TIME_30P8_MS);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture wait time 30.8 ms.\n");
    res = apds9960_get_gesture_wait_time(&gs_handle, &gesture_wait_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture wait time %s.\n", gesture_wait_time == APDS9960_GESTURE_WAIT_TIME_30P8_MS ? "ok" : "error");
    
    /* set gesture wait time 39.2 ms */
    res = apds9960_set_gesture_wait_time(&gs_handle, APDS9960_GESTURE_WAIT_TIME_39P2_MS);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture wait time 39.2 ms.\n");
    res = apds9960_get_gesture_wait_time(&gs_handle, &gesture_wait_time);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture wait time failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture wait time %s.\n", gesture_wait_time == APDS9960_GESTURE_WAIT_TIME_39P2_MS ? "ok" : "error");
    
    /* apds9960_set_gesture_up_offset/apds9960_get_gesture_up_offset test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_up_offset/apds9960_get_gesture_up_offset test.\n");
    
    offset = rand() % 128;
    res = apds9960_set_gesture_up_offset(&gs_handle, offset);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture up offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture up offset %d.\n", offset);
    res = apds9960_get_gesture_up_offset(&gs_handle, (int8_t *)&offset_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture up offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture up offset %s.\n", offset_check == offset ? "ok" : "error");
    
    /* apds9960_set_gesture_down_offset/apds9960_get_gesture_down_offset test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_down_offset/apds9960_get_gesture_down_offset test.\n");
    
    offset = -(rand() % 128);
    res = apds9960_set_gesture_down_offset(&gs_handle, offset);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture down offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture down offset %d.\n", offset);
    res = apds9960_get_gesture_down_offset(&gs_handle, (int8_t *)&offset_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture down offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture down offset %s.\n", offset_check == offset ? "ok" : "error");
    
    /* apds9960_set_gesture_left_offset/apds9960_get_gesture_left_offset test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_left_offset/apds9960_get_gesture_left_offset test.\n");
    
    offset = rand() % 128;
    res = apds9960_set_gesture_left_offset(&gs_handle, offset);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture left offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture left offset %d.\n", offset);
    res = apds9960_get_gesture_left_offset(&gs_handle, (int8_t *)&offset_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture left offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture left offset %s.\n", offset_check == offset ? "ok" : "error");
    
    /* apds9960_set_gesture_right_offset/apds9960_get_gesture_right_offset test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_right_offset/apds9960_get_gesture_right_offset test.\n");
    
    offset = -(rand() % 128);
    res = apds9960_set_gesture_right_offset(&gs_handle, offset);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture right offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture right offset %d.\n", offset);
    res = apds9960_get_gesture_right_offset(&gs_handle, (int8_t *)&offset_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture right offset failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture right offset %s.\n", offset_check == offset ? "ok" : "error");
    
    /* apds9960_set_gesture_pulse_length/apds9960_get_gesture_pulse_length test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_pulse_length/apds9960_get_gesture_pulse_length test.\n");
    
    /* set gesture pulse length 4 us */
    res = apds9960_set_gesture_pulse_length(&gs_handle, APDS9960_GESTURE_PULSE_LENGTH_4_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture pulse length 4 us.\n");
    res = apds9960_get_gesture_pulse_length(&gs_handle, &gesture_len);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture pulse length %s.\n", gesture_len == APDS9960_GESTURE_PULSE_LENGTH_4_US ? "ok" : "error");
    
    /* set gesture pulse length 8 us */
    res = apds9960_set_gesture_pulse_length(&gs_handle, APDS9960_GESTURE_PULSE_LENGTH_8_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture pulse length 8 us.\n");
    res = apds9960_get_gesture_pulse_length(&gs_handle, &gesture_len);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture pulse length %s.\n", gesture_len == APDS9960_GESTURE_PULSE_LENGTH_8_US ? "ok" : "error");
    
    /* set gesture pulse length 16 us */
    res = apds9960_set_gesture_pulse_length(&gs_handle, APDS9960_GESTURE_PULSE_LENGTH_16_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture pulse length 16 us.\n");
    res = apds9960_get_gesture_pulse_length(&gs_handle, &gesture_len);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture pulse length %s.\n", gesture_len == APDS9960_GESTURE_PULSE_LENGTH_16_US ? "ok" : "error");
    
    /* set gesture pulse length 32 us */
    res = apds9960_set_gesture_pulse_length(&gs_handle, APDS9960_GESTURE_PULSE_LENGTH_32_US);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture pulse length 32 us.\n");
    res = apds9960_get_gesture_pulse_length(&gs_handle, &gesture_len);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture pulse length failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture pulse length %s.\n", gesture_len == APDS9960_GESTURE_PULSE_LENGTH_32_US ? "ok" : "error");
    
    /* apds9960_set_gesture_pulse_count/apds9960_get_gesture_pulse_count test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_pulse_count/apds9960_get_gesture_pulse_count test.\n");
    
    count = rand() % 0x3F;
    res = apds9960_set_gesture_pulse_count(&gs_handle, count);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture pulse count failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture pulse count %d.\n", count);
    res = apds9960_get_gesture_pulse_count(&gs_handle, (uint16_t *)&count_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture pulse count failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture pulse count %s.\n", count_check == count ? "ok" : "error");
    
    /* apds9960_set_gesture_dimension/apds9960_get_gesture_dimension_select test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_dimension/apds9960_get_gesture_dimension_select test.\n");
    
    /* set both pairs active */
    res = apds9960_set_gesture_dimension(&gs_handle, APDS9960_GESTURE_DIMENSION_SELECT_BOTH_PAIRS_ACTIVE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture dimension failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set both pairs active.\n");
    res = apds9960_get_gesture_dimension_select(&gs_handle, &s);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture dimension failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture dimension select %s.\n", s == APDS9960_GESTURE_DIMENSION_SELECT_BOTH_PAIRS_ACTIVE ? "ok" : "error");
    
    /* set only up down pair active */
    res = apds9960_set_gesture_dimension(&gs_handle, APDS9960_GESTURE_DIMENSION_SELECT_ONLY_UP_DOWN_PAIRS_ACTIVE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture dimension failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set only up down pair active.\n");
    res = apds9960_get_gesture_dimension_select(&gs_handle, &s);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture dimension failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture dimension select %s.\n", s == APDS9960_GESTURE_DIMENSION_SELECT_ONLY_UP_DOWN_PAIRS_ACTIVE ? "ok" : "error");
    
    /* set only left right pair active */
    res = apds9960_set_gesture_dimension(&gs_handle, APDS9960_GESTURE_DIMENSION_SELECT_ONLY_LEFT_RIGHT_PAIRS_ACTIVE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture dimension failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set only left right pair active.\n");
    res = apds9960_get_gesture_dimension_select(&gs_handle, &s);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture dimension failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture dimension select %s.\n", s == APDS9960_GESTURE_DIMENSION_SELECT_ONLY_LEFT_RIGHT_PAIRS_ACTIVE ? "ok" : "error");
    
    /* apds9960_set_gesture_interrupt/apds9960_get_gesture_interrupt test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_interrupt/apds9960_get_gesture_interrupt test.\n");
    
    /* enable gesture interrupt */
    res = apds9960_set_gesture_interrupt(&gs_handle, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable gesture interrupt.\n");
    res = apds9960_get_gesture_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture interrupt %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable gesture interrupt */
    res = apds9960_set_gesture_interrupt(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable gesture interrupt.\n");
    res = apds9960_get_gesture_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture interrupt %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* apds9960_set_gesture_mode/apds9960_get_gesture_mode test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_mode/apds9960_get_gesture_mode test.\n");
    
    /* enable gesture mode */
    res = apds9960_set_gesture_mode(&gs_handle, APDS9960_BOOL_TRUE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture mode failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: enable gesture mode.\n");
    res = apds9960_get_gesture_mode(&gs_handle, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture mode failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture mode %s.\n", enable == APDS9960_BOOL_TRUE ? "ok" : "error");
    
    /* disable gesture mode */
    res = apds9960_set_gesture_mode(&gs_handle, APDS9960_BOOL_FALSE);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture mode failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: disable gesture mode.\n");
    res = apds9960_get_gesture_mode(&gs_handle, &enable);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture mode failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture mode %s.\n", enable == APDS9960_BOOL_FALSE ? "ok" : "error");
    
    /* apds9960_set_gesture_decode_threshold/apds9960_get_gesture_decode_threshold test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_decode_threshold/apds9960_get_gesture_decode_threshold test.\n");
    
    reg = rand() % 256;
    res = apds9960_set_gesture_decode_threshold(&gs_handle, reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture decode threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture decode threshold 0x%02X.\n", reg);
    res = apds9960_get_gesture_decode_threshold(&gs_handle, (uint8_t *)&reg_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture decode threshold failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture decode threshold %s.\n", reg_check == reg ? "ok" : "error");
    
    /* apds9960_set_gesture_decode_sensitivity_1/apds9960_get_gesture_decode_sensitivity_1 test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_decode_sensitivity_1/apds9960_get_gesture_decode_sensitivity_1 test.\n");
    
    sensitivity = rand() % 65536;
    res = apds9960_set_gesture_decode_sensitivity_1(&gs_handle, sensitivity);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture decode sensitivity 1 failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture decode sensitivity 1 %d.\n", sensitivity);
    res = apds9960_get_gesture_decode_sensitivity_1(&gs_handle, (int32_t *)&sensitivity_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture decode sensitivity 1 failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture decode sensitivity %s.\n", sensitivity_check == sensitivity ? "ok" : "error");
    
    /* apds9960_set_gesture_decode_sensitivity_2/apds9960_get_gesture_decode_sensitivity_2 test */
    apds9960_interface_debug_print("apds9960: apds9960_set_gesture_decode_sensitivity_2/apds9960_get_gesture_decode_sensitivity_2 test.\n");
    
    sensitivity = rand() % 65536;
    res = apds9960_set_gesture_decode_sensitivity_2(&gs_handle, sensitivity);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: set gesture decode sensitivity 2 failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set gesture decode sensitivity 2 %d.\n", sensitivity);
    res = apds9960_get_gesture_decode_sensitivity_2(&gs_handle, (int32_t *)&sensitivity_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture decode sensitivity 2 failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture decode sensitivity %s.\n", sensitivity_check == sensitivity ? "ok" : "error");
    
    /* apds9960_adc_integration_time_convert_to_register/apds9960_adc_integration_time_convert_to_data test */
    apds9960_interface_debug_print("apds9960: apds9960_adc_integration_time_convert_to_register/apds9960_adc_integration_time_convert_to_data test.\n");
    
    ms = (float)(rand() % 1000 )/ 10.0f;
    res = apds9960_adc_integration_time_convert_to_register(&gs_handle, ms, (uint8_t *)&reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: adc integration time convert to register failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set adc integration time %0.2f.\n", ms);
    res = apds9960_adc_integration_time_convert_to_data(&gs_handle, reg, (float *)&ms_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: adc integration time convert to data failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check adc integration time %0.2f.\n", ms_check);
    
    /* apds9960_wait_time_convert_to_register/apds9960_wait_time_convert_to_data test */
    apds9960_interface_debug_print("apds9960: apds9960_wait_time_convert_to_register/apds9960_wait_time_convert_to_data test.\n");
    
    ms = (float)(rand() % 1000 )/ 10.0f;
    res = apds9960_wait_time_convert_to_register(&gs_handle, ms, (uint8_t *)&reg);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: wait time convert to register failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: set wait time %0.2f.\n", ms);
    res = apds9960_wait_time_convert_to_data(&gs_handle, reg, (float *)&ms_check);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: wait time convert to data failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check wait time %0.2f.\n", ms_check);
    
    /* apds9960_get_status test */
    apds9960_interface_debug_print("apds9960: apds9960_get_status test.\n");
    
    /* get status */
    res = apds9960_get_status(&gs_handle, (uint8_t *)&status);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get status failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: status is 0x%02X.\n", status);
    
    /* apds9960_get_gesture_fifo_level test */
    apds9960_interface_debug_print("apds9960: apds9960_get_gesture_fifo_level test.\n");
    
    /* get gesture fifo level */
    res = apds9960_get_gesture_fifo_level(&gs_handle, (uint8_t *)&level);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture fifo level failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: fifo level is 0x%02X.\n", level);
    
    /* apds9960_get_gesture_status test */
    apds9960_interface_debug_print("apds9960: apds9960_get_gesture_status test.\n");
    
    /* get gesture status */
    res = apds9960_get_gesture_status(&gs_handle, (uint8_t *)&status);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: get gesture status failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: gesture status is 0x%02X.\n", status);
    
    /* apds9960_gesture_fifo_clear test */
    apds9960_interface_debug_print("apds9960: apds9960_gesture_fifo_clear test.\n");
    
    /* gesture fifo clear */
    res = apds9960_gesture_fifo_clear(&gs_handle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: gesture fifo clear failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check gesture fifo clear %s.\n", res == 0 ? "ok" : "error");
    
    /* apds9960_force_interrupt test */
    apds9960_interface_debug_print("apds9960: apds9960_force_interrupt test.\n");
    
    /* force interrupt */
    res = apds9960_force_interrupt(&gs_handle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: force interrupt failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check force interrupt %s.\n", res == 0 ? "ok" : "error");
    
    /* apds9960_proximity_interrupt_clear test */
    apds9960_interface_debug_print("apds9960: apds9960_proximity_interrupt_clear test.\n");
    
    /* proximity interrupt clear */
    res = apds9960_proximity_interrupt_clear(&gs_handle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: proximity interrupt clear failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check proximity interrupt clear %s.\n", res == 0 ? "ok" : "error");
    
    /* apds9960_als_interrupt_clear test */
    apds9960_interface_debug_print("apds9960: apds9960_als_interrupt_clear test.\n");
    
    /* als interrupt clear */
    res = apds9960_als_interrupt_clear(&gs_handle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: als interrupt clear failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check als interrupt clear %s.\n", res == 0 ? "ok" : "error");
    
    /* apds9960_all_non_gesture_interrupt_clear test */
    apds9960_interface_debug_print("apds9960: apds9960_all_non_gesture_interrupt_clear test.\n");
    
    /* all non gesture interrupt clear */
    res = apds9960_all_non_gesture_interrupt_clear(&gs_handle);
    if (res != 0)
    {
        apds9960_interface_debug_print("apds9960: all non gesture interrupt clear failed.\n");
        (void)apds9960_deinit(&gs_handle);
        
        return 1;
    }
    apds9960_interface_debug_print("apds9960: check all non gesture interrupt clear %s.\n", res == 0 ? "ok" : "error");
    
    /* finish register test */
    apds9960_interface_debug_print("apds9960: finish register test.\n");
    (void)apds9960_deinit(&gs_handle);
    
    return 0;
}
