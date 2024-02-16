[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver APDS9960

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/apds9960/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

Broadcom APDS-9960は、単一の8ピンパッケージに収められたデジタルRGB、環境光、近接およびジェスチャーセンサーデバイスです。このデバイスは、I2C互換のインターフェイスを備えており、赤、緑、青、クリア（RGBC）、近接、およびIRLEDによるジェスチャセンシングを提供します。 RGBおよび周囲光検知機能は、さまざまな照明条件の下で、暗いガラスを含むさまざまな減衰材料を介して光強度を検出します。さらに、統合されたUV-IRブロッキングフィルターにより、正確な周囲光と相関色温度の検出が可能になります。近接およびジェスチャ機能は、お客様のキャリブレーションを必要とせずに、工場でトリミングされ、100mmの近接検出距離にキャリブレーションされます。ジェスチャ検出は、可視ブロッキングフィルタと統合された4つの指向性フォトダイオードを利用して、単純な上下左右のジェスチャまたはより複雑なジェスチャを正確に検出します。モジュール内にマイクロ光学レンズを追加すると、赤外線エネルギーの高効率の送受信が可能になります。内部ステートマシンにより、デバイスをRGBC、近接測定、ジェスチャ測定の間で低電力状態にすることができ、非常に低い消費電力を提供します。ディスプレイのバックライト制御、相関色温度検知、携帯電話のタッチスクリーンの無効化、デジタルで使用できます。カメラのタッチスクリーンの無効化、機械的なスイッチの交換、ジェスチャ検出など。

LibDriver APDS9960は、LibDriverによって起動されたAPDS9960の全機能ドライバーです。LibDriverAPDS9960は、rgbc読み取り機能、近接読み取り機能、ジェスチャデコード機能などの機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example gesture](#example-gesture)
    - [example interrupt](#example-interrupt)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver APDS9960のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver APDS9960用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver APDS9960ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver APDS9960プログラミング例が含まれています。

/ docディレクトリには、LibDriver APDS9960オフラインドキュメントが含まれています。

/ datasheetディレクトリには、APDS9960データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

```c
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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/apds9960/index.html](https://www.libdriver.com/docs/apds9960/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。