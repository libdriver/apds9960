[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver APDS9960

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/apds9960/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

Broadcom APDS-9960 是一款採用單個 8 引腳封裝的數字 RGB、環境光、近程和手勢傳感器裝置。該裝置具有與 I2C 兼容的接口，為紅色、綠色、藍色、透明 (RGBC)，近程和手勢感測配有紅外 LED。 RGB 和環境光感測功能可在多種光條件下以及通過多種減振材料包括深色玻璃的情況下，檢測出光強度。此外，集成 UV-IR 遮光濾光片可實現精準的環境光和相關色溫感測。近程和手勢功能經工廠調整和校準至 100 毫米的近程檢測距離，無需客戶校準。利用四個定向二極管，與可見光遮光濾光片集成，手勢檢測能準確地感應“上下左右”以及更複雜的動作。模塊內增加的微光學透鏡能提供高效的傳輸和紅外能量的接收。內部狀態機能夠將該裝置處於 RGBC、近程和手勢測量之間的低功耗狀態，提供極低的功耗。它可用於顯示屏背光控制、色溫感應、手機觸摸屏禁用、數字攝像頭觸屏禁用、機械開關更換、手勢檢測等。

LibDriver APDS9960是LibDriver推出的APDS9960全功能驅動。 LibDriver APDS9960提供rgbc讀取、接近讀取、手勢解碼等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example gesture](#example-gesture)
    - [example interrupt](#example-interrupt)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver APDS9960的源文件。

/interface目錄包含了LibDriver APDS9960與平台無關的IIC總線模板。

/test目錄包含了LibDriver APDS9960驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver APDS9960編程範例。

/doc目錄包含了LibDriver APDS9960離線文檔。

/datasheet目錄包含了APDS9960數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，/interface目錄和/example目錄加入工程。

### 使用

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

### 文檔

在線文檔: https://www.libdriver.com/docs/apds9960/index.html

離線文檔: /doc/html/index.html

### 貢獻

請聯繫lishifenging@outlook.com

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com