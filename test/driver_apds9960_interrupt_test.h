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
 * @file      driver_apds9960_interrupt_test.h
 * @brief     driver apds9960 interrupt test header file
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

#ifndef DRIVER_APDS9960_INTERRUPT_TEST_H
#define DRIVER_APDS9960_INTERRUPT_TEST_H

#include "driver_apds9960_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup apds9960_test_driver
 * @{
 */

/**
 * @brief  interrupt test irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t apds9960_interrupt_test_irq_handler(void);

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
                                uint8_t proximity_low_threshold, uint8_t proximity_high_threshold);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
