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
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                        /**< uart buffer */
volatile uint16_t g_len;                   /**< uart buffer length */
uint8_t (*g_gpio_irq)(void) = NULL;        /**< gpio irq */
static volatile uint8_t gs_flag;           /**< flag */

/**
 * @brief exti 0 irq
 * @note  none
 */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
 * @brief     gpio exti callback
 * @param[in] pin is the gpio pin
 * @note      none
 */
void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
    if (pin == GPIO_PIN_0)
    {
        if (g_gpio_irq != NULL)
        {
            g_gpio_irq();
        }
    }
}

/**
 * @brief     gesture callback
 * @param[in] type is the interrupt type
 * @note      none
 */
static void a_gesture_callback(uint8_t type)
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
            
            break;
        }
    }
}

/**
 * @brief     interrupt receive callback
 * @param[in] type is the interrupt type
 * @note      none
 */
static void a_interrupt_callback(uint8_t type)
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
            res = apds9960_interrupt_read_proximity((uint8_t *)&proximity);
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
            res = apds9960_interrupt_read_rgbc((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
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
 * @brief     apds9960 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t apds9960(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"als-high-threshold", required_argument, NULL, 1},
        {"als-low-threshold", required_argument, NULL, 2},
        {"proximity-high-threshold", required_argument, NULL, 3},
        {"proximity-low-threshold", required_argument, NULL, 4},
        {"times", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    uint16_t alow = 1;
    uint16_t ahigh = 1000;
    uint8_t plow = 1;
    uint8_t phigh = 128;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* als-high-threshold */
            case 1 :
            {
                /* set the als high threshold */
                ahigh = atol(optarg);
                
                break;
            }
            
            /* als-low-threshold */
            case 2 :
            {
                /* set the als low threshold */
                alow = atol(optarg);
                
                break;
            }
            
            /* proximity-high-threshold */
            case 3 :
            {
                /* set proximity high threshold */
                phigh = atol(optarg);
                
                break;
            }
             
            /* proximity-low-threshold */
            case 4 :
            {
                /* set proximity low threshold */
                plow = atol(optarg);
                
                break;
            }
            
            /* running times */
            case 5 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (apds9960_register_test() != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (apds9960_read_test(times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_int", type) == 0)
    {
        /* set gpio irq */
        g_gpio_irq = apds9960_interrupt_test_irq_handler;
        
        /* gpio init */
        if (gpio_interrupt_init() != 0)
        {
            g_gpio_irq = NULL;
        }
        
        /* run interrupt test */
        if (apds9960_interrupt_test(times, alow, ahigh, plow, phigh) != 0)
        {
            (void)gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* gpio deinit */
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("t_gesture", type) == 0)
    {
        /* set gpio irq */
        g_gpio_irq = apds9960_gesture_test_irq_handler;
        
        /* gpio init */
        if (gpio_interrupt_init() != 0)
        {
            g_gpio_irq = NULL;
        }
        
        /* run gesture test */
        if (apds9960_gesture_test(times) != 0)
        {
            (void)gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* gpio deinit */
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* basic init */
        res = apds9960_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* 1000 ms */
        apds9960_interface_delay_ms(1000);
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            uint8_t proximity;
            uint16_t red, green, blue, clear;
            
            /* read rgbc */
            res = apds9960_basic_read_rgbc((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
            if (res != 0)
            {
                apds9960_interface_debug_print("apds9960: read rgbc failed.\n");
                (void)apds9960_basic_deinit();
                
                return 1;
            }
            
            /* read proximity */
            res = apds9960_basic_read_proximity((uint8_t *)&proximity);
            if (res != 0)
            {
                apds9960_interface_debug_print("apds9960: read proximity failed.\n");
                (void)apds9960_basic_deinit();
                
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
        (void)apds9960_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_gesture", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* set gpio irq */
        g_gpio_irq = apds9960_gesture_irq_handler;
        
        /* gpio init */
        if (gpio_interrupt_init() != 0)
        {
            g_gpio_irq = NULL;
        }
        
        /* gesture init */
        res = apds9960_gesture_init(a_gesture_callback);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* loop */
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
        
        /* deinit */
        (void)apds9960_gesture_deinit();
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("e_int", type) == 0)
    {
        uint32_t i;
        
        /* set gpio irq */
        g_gpio_irq = apds9960_interrupt_irq_handler;
        
        /* gpio init */
        if (gpio_interrupt_init() != 0)
        {
            g_gpio_irq = NULL;
        }
        
        /* run interrupt function */
        if (apds9960_interrupt_init(a_interrupt_callback, alow, ahigh, plow, phigh) != 0)
        {
            (void)gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* loop */
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
        
        /* deinit */
        (void)apds9960_interrupt_deinit();
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        apds9960_interface_debug_print("Usage:\n");
        apds9960_interface_debug_print("  apds9960 (-i | --information)\n");
        apds9960_interface_debug_print("  apds9960 (-h | --help)\n");
        apds9960_interface_debug_print("  apds9960 (-p | --port)\n");
        apds9960_interface_debug_print("  apds9960 (-t reg | --test=reg)\n");
        apds9960_interface_debug_print("  apds9960 (-t read | --test=read) [--times=<num>]\n");
        apds9960_interface_debug_print("  apds9960 (-t int | --test=int) [--times=<num>] [--als-high-threshold=<ahigh>] [--als-low-threshold=<alow>]\n");
        apds9960_interface_debug_print("           [--proximity-high-threshold=<phigh>] [--proximity-low-threshold=<plow>]\n");
        apds9960_interface_debug_print("  apds9960 (-t gesture | --test=gesture) [--times=<num>]\n");
        apds9960_interface_debug_print("  apds9960 (-e read | --example=read) [--times=<num>]\n");
        apds9960_interface_debug_print("  apds9960 (-e int | --example=int) [--times=<num>] [--als-high-threshold=<ahigh>] [--als-low-threshold=<alow>]\n");
        apds9960_interface_debug_print("           [--proximity-high-threshold=<phigh>] [--proximity-low-threshold=<plow>]\n");
        apds9960_interface_debug_print("  apds9960 (-e gesture | --example=gesture)  [--times=<num>]\n");
        apds9960_interface_debug_print("\n");
        apds9960_interface_debug_print("Options:\n");
        apds9960_interface_debug_print("      --als-high-threshold=<ahigh>          Set the als interrupt high threshold.([default: 1000])\n");
        apds9960_interface_debug_print("      --als-low-threshold=<alow>            Set the als interrupt low threshold.([default: 1])\n");
        apds9960_interface_debug_print("  -e <read | int | gesture>, --example=<read | int | gesture>\n");
        apds9960_interface_debug_print("                                            Run the driver example.\n");
        apds9960_interface_debug_print("  -h, --help                                Show the help.\n");
        apds9960_interface_debug_print("  -i, --information                         Show the chip information.\n");
        apds9960_interface_debug_print("  -p, --port                                Display the pin connections of the current board.\n");
        apds9960_interface_debug_print("      --proximity-high-threshold=<phigh>    Set the proximity high threshold.([default: 128])\n");
        apds9960_interface_debug_print("      --proximity-low-threshold=<plow>      Set the proximity low threshold.([default: 1])\n");
        apds9960_interface_debug_print("  -t <reg | read | int | gesture>, --test=<reg | read | int | gesture>\n");
        apds9960_interface_debug_print("                                            Run the driver test.\n");
        apds9960_interface_debug_print("      --times=<num>                         Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        apds9960_interface_debug_print("apds9960: SCL connected to GPIOB PIN8.\n");
        apds9960_interface_debug_print("apds9960: SDA connected to GPIOB PIN9.\n");
        apds9960_interface_debug_print("apds9960: INT connected to GPIOB PIN0.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register apds9960 function */
    shell_init();
    shell_register("apds9960", apds9960);
    uart_print("apds9960: welcome to libdriver apds9960.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("apds9960: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("apds9960: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("apds9960: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("apds9960: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("apds9960: param is invalid.\n");
            }
            else
            {
                uart_print("apds9960: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
