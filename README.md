[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver APDS9960

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/apds9960/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The Broadcom APDS-9960 is a digital RGB, ambient light, proximity and gesture sensor device in a single 8-pin package. The device has an I2C compatible interface providing red, green, blue, clear (RGBC), proximity and gesture sensing with IR LED. The RGB and ambient light sensing feature detects light intensity under various lighting conditions and through various attentuation materials including darkened glass. In addition, the integrated UV-IR blocking filter enables accurate ambient light and correlated color temperature sensing.The proximity and gesture feature is factory-trimmed and calibrated to 100mm proximity detection distance without requiring customer calibrations. Gesture detection utilizes four directional photodiodes, integrated with visible blocking filter, to accurately sense simple UP-DOWN-RIGHT-LEFT gestures or more complex gestures. The addition of micro-optics lenses within the module provides high efficient transmission and reception of infrared energy. An internal state machine allows the device to be put into a low power state between RGBC, proximity and gesture measurements providing very low power consumption.It can be used in display backlight control,correlated color temperature sensing,cell phone touch-screen disable,digital camera touch-screen disable,mechanical switch replacement,gesture detection and so on.

LibDriver APDS9960 is the full function driver of APDS9960 launched by LibDriver.LibDriver APDS9960 provides rgbc reading function, proximity reading function, gesture decoding function and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example gesture](#example-gesture)
    - [example interrupt](#example-interrupt)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver APDS9960 source files.

/interface includes LibDriver APDS9960 IIC platform independent template.

/test includes LibDriver APDS9960 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver APDS9960 sample code.

/doc includes LibDriver APDS9960 offline document.

/datasheet includes APDS9960 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_apds9960_basic.h"

uint8_t res;
uint32_t i, times;

times = 3;
res = apds9960_basic_init();
if (res != 0)
{
    return 1;
}

/* 1000 ms */
apds9960_interface_delay_ms(1000);

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
```

#### example gesture

```C
#include "driver_apds9960_gesture.h"

uint8_t (*g_gpio_irq)(void) = NULL;
static uint8_t gs_flag;
uint8_t res;
uint32_t i, times;

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
            
            break;
        }
    }
}

times = 3;

/* gpio interrupt init */
g_gpio_irq = apds9960_gesture_irq_handler;
if (gpio_interrupt_init() != 0)
{
    g_gpio_irq = NULL;
}

res = apds9960_gesture_init(a_gesture_callback);
if (res != 0)
{
    (void)gpio_interrupt_deinit();
    g_gpio_irq = NULL;

    return 1;
}

gs_flag = 0;
for (i = 0; i < times; i++)
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

(void)apds9960_gesture_deinit();
(void)gpio_interrupt_deinit();
g_gpio_irq = NULL;

return 0;
```

#### example interrupt

```C
#include "driver_apds9960_interrupt.h"

uint8_t (*g_gpio_irq)(void) = NULL;
static uint8_t gs_flag;
uint8_t res;
uint32_t i, times;

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
            
            break;
        }
    }
}
               
times = 3;

/* gpio interrupt init */
g_gpio_irq = apds9960_interrupt_irq_handler;
if (gpio_interrupt_init() != 0)
{
    g_gpio_irq = NULL;
}

/* run interrupt function */
if (apds9960_interrupt_init(_interrupt_callback, 1,
                            2000, 1, 150) != 0)
{
    (void)gpio_interrupt_deinit();
    g_gpio_irq = NULL;

    return 1;
}

gs_flag = 0;
for (i = 0; i < times; i++)
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

(void)apds9960_interrupt_deinit();
(void)gpio_interrupt_deinit();
g_gpio_irq = NULL;

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/apds9960/index.html](https://www.libdriver.com/docs/apds9960/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.