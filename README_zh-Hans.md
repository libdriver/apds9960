[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver APDS9960

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/apds9960/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

Broadcom APDS-9960 是一款采用单个 8 引脚封装的数字 RGB、环境光、接近和手势传感器装置。该装置具有与 I2C 兼容的接口，为红色、绿色、蓝色、透明 (RGBC)，接近和手势感测配有红外 LED。RGB 和环境光感测功能可在多种光条件下以及通过多种减振材料包括深色玻璃的情况下，检测出光强度。此外，集成 UV-IR 遮光滤光片可实现精准的环境光和相关色温感测。接近和手势功能经工厂调整和校准至 100 毫米的接近检测距离，无需客户校准。利用四个定向二极管，与可见光遮光滤光片集成，手势检测能准确地感应“上下左右”以及更复杂的动作。模块内增加的微光学透镜能提供高效的传输和红外能量的接收。内部状态机能够将该装置在RGBC、接近和手势测量完成后进入低功耗状态，提供极低的使用功耗。它可用于显示屏背光控制、色温感应、手机触摸屏禁用、数字摄像头触屏禁用、机械开关更换、手势检测等。

LibDriver APDS9960是LibDriver推出的APDS9960全功能驱动。LibDriver APDS9960提供rgbc读取、接近读取、手势解码等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example gesture](#example-gesture)
    - [example interrupt](#example-interrupt)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver APDS9960的源文件。

/interface目录包含了LibDriver APDS9960与平台无关的IIC总线模板。

/test目录包含了LibDriver APDS9960驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver APDS9960编程范例。

/doc目录包含了LibDriver APDS9960离线文档。

/datasheet目录包含了APDS9960数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/apds9960/index.html](https://www.libdriver.com/docs/apds9960/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。