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
 * @file      main.c
 * @brief     main source file
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

#include "driver_apds9960_gesture.h"
#include "driver_apds9960_interrupt.h"
#include "driver_apds9960_basic.h"
#include "driver_apds9960_gesture_test.h"
#include "driver_apds9960_interrupt_test.h"
#include "driver_apds9960_read_test.h"
#include "driver_apds9960_register_test.h"
#include "gpio.h"
#include <stdlib.h>

uint8_t (*g_gpio_irq)(void) = NULL;        /**< gpio irq */
static uint8_t gs_flag;                    /**< flag */

/**
 * @brief     gesture callback
 * @param[in] type is the interrupt type
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 * @note      none
 */
static uint8_t _gesture_callback(uint8_t type)
{
    switch (type)
    {
        case APDS9960_INTERRUPT_STATUS_GESTURE_LEFT :
        {
            apds9960_interface_debug_print("apds9960: irq gesture left.\n");
            gs_flag = 1;
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_RIGHT :
        {
            apds9960_interface_debug_print("apds9960: irq gesture right.\n");
            gs_flag = 1;
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_UP :
        {
            apds9960_interface_debug_print("apds9960: irq gesture up.\n");
            gs_flag = 1;
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_DOWN :
        {
            apds9960_interface_debug_print("apds9960: irq gesture down.\n");
            gs_flag = 1;
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_NEAR :
        {
            apds9960_interface_debug_print("apds9960: irq gesture near.\n");
            gs_flag = 1;
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GESTURE_FAR :
        {
            apds9960_interface_debug_print("apds9960: irq gesture far.\n");
            gs_flag = 1;
            
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
            apds9960_interface_debug_print("apds9960: irq clear photodiode saturation.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_PGSAT :
        {
            apds9960_interface_debug_print("apds9960: irq analog saturation.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_PINT :
        {
            apds9960_interface_debug_print("apds9960: irq proximity interrupt.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_AINT :
        {
            apds9960_interface_debug_print("apds9960: irq als interrupt.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_GINT :
        {
            break;
        }
        case APDS9960_INTERRUPT_STATUS_PVALID :
        {
            break;
        }
        case APDS9960_INTERRUPT_STATUS_AVALID :
        {
            apds9960_interface_debug_print("apds9960: irq als valid.\n");
            
            break;
        }
        default :
        {
            apds9960_interface_debug_print("apds9960: irq unknown.\n");
        }
    }
    
    return 0;
}

/**
 * @brief     interrupt receive callback
 * @param[in] type is the interrupt type
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 * @note      none
 */
static uint8_t _interrupt_callback(uint8_t type)
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
            apds9960_interface_debug_print("apds9960: irq clear photodiode saturation.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_PGSAT :
        {
            apds9960_interface_debug_print("apds9960: irq analog saturation.\n");
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_PINT :
        {
            volatile uint8_t res;
            volatile uint8_t proximity;
            
            /* read proximity */
            res = apds9960_interrupt_read_proximity((uint8_t *)&proximity);
            if (res)
            {
                apds9960_interface_debug_print("apds9960: read proximity failed.\n");
                
                return 1;
            }
            apds9960_interface_debug_print("apds9960: proximity is 0x%02X.\n", proximity);
            gs_flag = 1;
            
            break;
        }
        case APDS9960_INTERRUPT_STATUS_AINT :
        {
            volatile uint8_t res;
            volatile uint16_t red, green, blue, clear;
            
            /* read rgbc */
            res = apds9960_interrupt_read_rgbc((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
            if (res)
            {
                apds9960_interface_debug_print("apds9960: read rgbc failed.\n");
                
                return 1;
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
        }
    }
    
    return 0;
}

/**
 * @brief     apds9960 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t apds9960(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            apds9960_info_t info;
            
            /* print apds9960 info */
            apds9960_info(&info);
            apds9960_interface_debug_print("apds9960: chip is %s.\n", info.chip_name);
            apds9960_interface_debug_print("apds9960: manufacturer is %s.\n", info.manufacturer_name);
            apds9960_interface_debug_print("apds9960: interface is %s.\n", info.interface);
            apds9960_interface_debug_print("apds9960: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
            apds9960_interface_debug_print("apds9960: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            apds9960_interface_debug_print("apds9960: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            apds9960_interface_debug_print("apds9960: max current is %0.2fmA.\n", info.max_current_ma);
            apds9960_interface_debug_print("apds9960: max temperature is %0.1fC.\n", info.temperature_max);
            apds9960_interface_debug_print("apds9960: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            apds9960_interface_debug_print("apds9960: SCL connected to GPIO3(BCM).\n");
            apds9960_interface_debug_print("apds9960: SDA connected to GPIO2(BCM).\n");
            apds9960_interface_debug_print("apds9960: INT connected to GPIO17(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show apds9960 help */
            
            help:
            
            apds9960_interface_debug_print("apds9960 -i\n\tshow apds9960 chip and driver information.\n");
            apds9960_interface_debug_print("apds9960 -h\n\tshow apds9960 help.\n");
            apds9960_interface_debug_print("apds9960 -p\n\tshow apds9960 pin connections of the current board.\n");
            apds9960_interface_debug_print("apds9960 -t reg\n\trun apds9960 register test.\n");
            apds9960_interface_debug_print("apds9960 -t read <times>\n\trun apds9960 read test.times means test times.\n");
            apds9960_interface_debug_print("apds9960 -t int <times> <alslowthreshold> <alshighthreshold> <proximitylowthreshold> <proximityhighthreshold>\n\t");
            apds9960_interface_debug_print("run apds9960 interrupt test.times means test times.alslowthreshold is the als low threshold."
                                           "alshighthreshold is the als high threshold.proximitylowthreshold is the proximity low threshold.proximityhighthreshold is the proximity high threshold.\n");
            apds9960_interface_debug_print("apds9960 -t gesture <times>\n\trun apds9960 gesture test.times means test times.\n");
            apds9960_interface_debug_print("apds9960 -c read <times>\n\trun apds9960 read function.times means test times.\n");
            apds9960_interface_debug_print("apds9960 -c gesture <times>\n\trun apds9960 gesture function.times means test times.\n");
            apds9960_interface_debug_print("apds9960 -c int <times> <alslowthreshold> <alshighthreshold> <proximitylowthreshold> <proximityhighthreshold>\n\t");
            apds9960_interface_debug_print("run apds9960 interrupt function.times means test times.alslowthreshold is the als low threshold.alshighthreshold is the als high threshold.");
            apds9960_interface_debug_print("proximitylowthreshold is the proximity low threshold.proximityhighthreshold is the proximity high threshold.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            if (strcmp("reg", argv[2]) == 0)
            {
                /* run reg test */
                if (apds9960_register_test())
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            if (strcmp("read", argv[2]) == 0)
            {
                /* run read test */
                if (apds9960_read_test(atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (strcmp("gesture", argv[2]) == 0)
            {
                /* gpio interrupt init */
                g_gpio_irq = apds9960_gesture_test_irq_handler;
                if (gpio_interrupt_init())
                {
                    g_gpio_irq = NULL;
                }
                
                /* run gesture test */
                if (apds9960_gesture_test(atoi(argv[3])))
                {
                    gpio_interrupt_deinit();
                    g_gpio_irq = NULL;
                    
                    return 1;
                }
                else
                {
                    gpio_interrupt_deinit();
                    g_gpio_irq = NULL;
                    
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i, times;
                
                times = atoi(argv[3]);
                res = apds9960_basic_init();
                if (res)
                {
                    return 1;
                }
                
                /* 1000 ms */
                apds9960_interface_delay_ms(1000);
                
                for (i = 0; i < times; i++)
                {
                    volatile uint8_t proximity;
                    volatile uint16_t red, green, blue, clear;
                    
                    /* read rgbc */
                    res = apds9960_basic_read_rgbc((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
                    if (res)
                    {
                        apds9960_interface_debug_print("apds9960: read rgbc failed.\n");
                        apds9960_basic_deinit();
                        
                        return 1;
                    }
                    
                    /* read proximity */
                    res = apds9960_basic_read_proximity((uint8_t *)&proximity);
                    if (res)
                    {
                        apds9960_interface_debug_print("apds9960: read proximity failed.\n");
                        apds9960_basic_deinit();
                        
                        return 1;
                    }
                    
                    /* output */
                    apds9960_interface_debug_print("%d/%d.\n", i + 1, times);
                    apds9960_interface_debug_print("apds9960: red is 0x%04X.\n", red);
                    apds9960_interface_debug_print("apds9960: green is 0x%04X.\n", green);
                    apds9960_interface_debug_print("apds9960: blue is 0x%04X.\n", blue);
                    apds9960_interface_debug_print("apds9960: clear is 0x%04X.\n", clear);
                    apds9960_interface_debug_print("apds9960: proximity is 0x%02X.\n", proximity);
                    
                    /* 1000 ms */
                    apds9960_interface_delay_ms(1000);
                }
                
                /* deinit */
                apds9960_basic_deinit();
                
                return 0;
            }
            else if (strcmp("gesture", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i, times;
                
                times = atoi(argv[3]);
                
                /* gpio interrupt init */
                g_gpio_irq = apds9960_gesture_irq_handler;
                if (gpio_interrupt_init())
                {
                    g_gpio_irq = NULL;
                }
                
                res = apds9960_gesture_init(_gesture_callback);
                if (res)
                {
                    gpio_interrupt_deinit();
                    g_gpio_irq = NULL;
                    
                    return 1;
                }
                
                gs_flag = 0;
                for (i = 0; i < times; i++)
                {
                    start_gesture:
                    
                    if (gs_flag)
                    {
                        gs_flag = 0;
                        
                        /* 1000 ms */
                        apds9960_interface_delay_ms(100);
                    }
                    else
                    {
                        /* 1000 ms */
                        apds9960_interface_delay_ms(100); 
                        
                        goto start_gesture;
                    }
                }
                
                apds9960_gesture_deinit();
                gpio_interrupt_deinit();
                g_gpio_irq = NULL;
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 8)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            if (strcmp("int", argv[2]) == 0)
            {
                /* gpio interrupt init */
                g_gpio_irq = apds9960_interrupt_test_irq_handler;
                if (gpio_interrupt_init())
                {
                    g_gpio_irq = NULL;
                }
                
                /* run interrupt test */
                if (apds9960_interrupt_test(atoi(argv[3]), atoi(argv[4]),
                                            atoi(argv[5]), atoi(argv[6]), atoi(argv[7])))
                {
                    gpio_interrupt_deinit();
                    g_gpio_irq = NULL;
                    
                    return 1;
                }
                else
                {
                    gpio_interrupt_deinit();
                    g_gpio_irq = NULL;
                    
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            if (strcmp("int", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i, times;
                
                times = atoi(argv[3]);
                
                /* gpio interrupt init */
                g_gpio_irq = apds9960_interrupt_irq_handler;
                if (gpio_interrupt_init())
                {
                    g_gpio_irq = NULL;
                }
                
                /* run interrupt function */
                if (apds9960_interrupt_init(_interrupt_callback, atoi(argv[4]),
                                            atoi(argv[5]), atoi(argv[6]), atoi(argv[7])))
                {
                    gpio_interrupt_deinit();
                    g_gpio_irq = NULL;
                    
                    return 1;
                }
                
                gs_flag = 0;
                for (i = 0; i < times; i++)
                {
                    start_int:
                    
                    if (gs_flag)
                    {
                        gs_flag = 0;
                        
                        /* 1000 ms */
                        apds9960_interface_delay_ms(100);
                    }
                    else
                    {
                        /* 1000 ms */
                        apds9960_interface_delay_ms(100); 
                        
                        goto start_int;
                    }
                }
                
                apds9960_interrupt_deinit();
                gpio_interrupt_deinit();
                g_gpio_irq = NULL;
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = apds9960(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        apds9960_interface_debug_print("apds9960: run failed.\n");
    }
    else if (res == 5)
    {
        apds9960_interface_debug_print("apds9960: param is invalid.\n");
    }
    else
    {
        apds9960_interface_debug_print("apds9960: unknow status code.\n");
    }

    return 0;
}
