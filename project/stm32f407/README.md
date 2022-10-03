### 1. Chip

#### 1.1 Chip Info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

int pin: INT PB0.

### 2. Shell

#### 2.1 Shell Parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. APDS9960

#### 3.1 Command Instruction

​          apds9960 is a basic command which can test all apds9960 driver function:

​          -i         show apds9960 chip and driver information.

​          -h        show apds9960 help.

​          -p        show apds9960 pin connections of the current board.

​          -t (reg | read <times> | int <times> <alslowthreshold> <alshighthreshold> <proximitylowthreshold> <proximityhighthreshold> | gesture <times>) 

​          -t reg         run apds9960 register test.

​          -t read <times>        run apds9960 read test. times means test times.         

​          -t int <times> <alslowthreshold> <alshighthreshold> <proximitylowthreshold> <proximityhighthreshold>            run apds9960 interrupt test. times means test times. alslowthreshold is the als low threshold. alshighthreshold is the als high threshold. proximitylowthreshold is the proximity low threshold. proximityhighthreshold is the proximity high threshold.

​          -t gesture <times>        run apds9960 gesture test. times means test times.   

​          -c (read <times> | int <times> <alslowthreshold> <alshighthreshold> <proximitylowthreshold> <proximityhighthreshold> | gesture <times>)  

​          -c read <times>        run apds9960 read function. times means test times.         

​          -c int <times> <alslowthreshold> <alshighthreshold> <proximitylowthreshold> <proximityhighthreshold>            run apds9960 interrupt function. times means test times. alslowthreshold is the als low threshold. alshighthreshold is the als high threshold. proximitylowthreshold is the proximity low threshold. proximityhighthreshold is the proximity high threshold.

​          -c gesture <times>        run apds9960 gesture function. times means test times. 

#### 3.2 Command Example

```shell
apds9960 -i

apds9960: chip is Broadcom APDS9960.
apds9960: manufacturer is Broadcom.
apds9960: interface is IIC.
apds9960: driver version is 1.0.
apds9960: min supply voltage is 2.4V.
apds9960: max supply voltage is 3.6V.
apds9960: max current is 100.00mA.
apds9960: max temperature is 85.0C.
apds9960: min temperature is -40.0C.
```

```shell
apds9960 -p

apds9960: SCL connected to GPIOB PIN8.
apds9960: SDA connected to GPIOB PIN9.
apds9960: INT connected to GPIOB PIN0.
```

```shell
apds9960 -t reg

apds9960: chip is Broadcom APDS9960.
apds9960: manufacturer is Broadcom.
apds9960: interface is IIC.
apds9960: driver version is 1.0.
apds9960: min supply voltage is 2.4V.
apds9960: max supply voltage is 3.6V.
apds9960: max current is 100.00mA.
apds9960: max temperature is 85.0C.
apds9960: min temperature is -40.0C.
apds9960: start register test.
apds9960: apds9960_set_conf/apds9960_get_conf test.
apds9960: disable power on.
apds9960: check config ok.
apds9960: enable power on.
apds9960: check config ok.
apds9960: enable gesture.
apds9960: check config ok.
apds9960: disable gesture.
apds9960: check config ok.
apds9960: enable proximity interrupt.
apds9960: check config ok.
apds9960: disable proximity interrupt.
apds9960: check config ok.
apds9960: enable als interrupt.
apds9960: check config ok.
apds9960: disable als interrupt.
apds9960: check config ok.
apds9960: enable wait.
apds9960: check config ok.
apds9960: disable wait.
apds9960: check config ok.
apds9960: enable proximity detect.
apds9960: check config ok.
apds9960: disable proximity detect.
apds9960: check config ok.
apds9960: enable als.
apds9960: check config ok.
apds9960: disable als.
apds9960: check config ok.
apds9960: apds9960_set_adc_integration_time/apds9960_get_adc_integration_time test.
apds9960: set adc integration time 0xB0.
apds9960: check adc integration time ok.
apds9960: apds9960_set_wait_time/apds9960_get_wait_time test.
apds9960: set wait time 0xCB.
apds9960: check wait time ok.
apds9960: apds9960_set_als_interrupt_low_threshold/apds9960_get_als_interrupt_low_threshold test.
apds9960: set als interrupt low threshold 0x7B49.
apds9960: check als interrupt low threshold ok.
apds9960: apds9960_set_als_interrupt_high_threshold/apds9960_get_als_interrupt_high_threshold test.
apds9960: set als interrupt high threshold 0xD868.
apds9960: check als interrupt high threshold ok.
apds9960: apds9960_set_proximity_interrupt_low_threshold/apds9960_get_proximity_interrupt_low_threshold test.
apds9960: set proximity interrupt low threshold 0x07.
apds9960: check proximity interrupt low threshold ok.
apds9960: apds9960_set_proximity_interrupt_high_threshold/apds9960_get_proximity_interrupt_high_threshold test.
apds9960: set proximity interrupt high threshold 0x45.
apds9960: check proximity interrupt high threshold ok.
apds9960: apds9960_set_proximity_interrupt_cycle/apds9960_get_proximity_interrupt_cycle test.
apds9960: set proximity interrupt every cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt any cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 2 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 3 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 4 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 5 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 6 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 7 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 8 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 9 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 10 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 11 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 12 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 13 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 14 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: set proximity interrupt 15 cycle.
apds9960: check proximity interrupt cycle ok.
apds9960: apds9960_set_als_interrupt_cycle/apds9960_get_als_interrupt_cycle test.
apds9960: set als interrupt every cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt any cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 2 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 3 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 5 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 10 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 15 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 20 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 25 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 30 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 35 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 40 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 45 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 50 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 55 cycle.
apds9960: check als interrupt cycle ok.
apds9960: set als interrupt 60 cycle.
apds9960: check als interrupt cycle ok.
apds9960: apds9960_set_wait_long/apds9960_get_wait_long test.
apds9960: enable wait long.
apds9960: check wait long ok.
apds9960: disable wait long.
apds9960: check wait long ok.
apds9960: apds9960_set_proximity_pulse_length/apds9960_get_proximity_pulse_length test.
apds9960: proximity pulse length 4 us.
apds9960: check proximity pulse length ok.
apds9960: proximity pulse length 8 us.
apds9960: check proximity pulse length ok.
apds9960: proximity pulse length 16 us.
apds9960: check proximity pulse length ok.
apds9960: proximity pulse length 32 us.
apds9960: check proximity pulse length ok.
apds9960: apds9960_set_proximity_pulse_count/apds9960_get_proximity_pulse_count test.
apds9960: set proximity pulse count 45.
apds9960: check proximity pulse count ok.
apds9960: apds9960_set_led_current/apds9960_get_led_current test.
apds9960: set led current 100 mA.
apds9960: check led current ok.
apds9960: set led current 50 mA.
apds9960: check led current ok.
apds9960: set led current 25 mA.
apds9960: check led current ok.
apds9960: set led current 12.5 mA.
apds9960: check led current ok.
apds9960: apds9960_set_proximity_gain/apds9960_get_proximity_gain test.
apds9960: set proximity gain 1x.
apds9960: check proximity gain ok.
apds9960: set proximity gain 2x.
apds9960: check proximity gain ok.
apds9960: set proximity gain 4x.
apds9960: check proximity gain ok.
apds9960: set proximity gain 8x.
apds9960: check proximity gain ok.
apds9960: apds9960_set_als_color_gain/apds9960_get_als_color_gain test.
apds9960: set als color gain 1x.
apds9960: check als color gain ok.
apds9960: set als color gain 4x.
apds9960: check als color gain ok.
apds9960: set als color gain 16x.
apds9960: check als color gain ok.
apds9960: set als color gain 64x.
apds9960: check als color gain ok.
apds9960: apds9960_set_saturation_interrupt/apds9960_get_saturation_interrupt test.
apds9960: disable proximity saturation interrupt.
apds9960: check saturation interrupt ok.
apds9960: enable proximity saturation interrupt.
apds9960: check saturation interrupt ok.
apds9960: disable clear photodiode saturation interrupt.
apds9960: check clear photodiode saturation interrupt ok.
apds9960: enable clear photodiode saturation interrupt.
apds9960: check clear photodiode saturation interrupt ok.
apds9960: apds9960_set_led_boost/apds9960_get_led_boost test.
apds9960: set led boost 100%.
apds9960: check led boost ok.
apds9960: set led boost 150%.
apds9960: check led boost ok.
apds9960: set led boost 200%.
apds9960: check led boost ok.
apds9960: set led boost 300%.
apds9960: check led boost ok.
apds9960: apds9960_set_proximity_up_right_offset/apds9960_get_proximity_up_right_offset test.
apds9960: set proximity up right offset 127.
apds9960: check proximity up right offset ok.
apds9960: apds9960_set_proximity_down_left_offset/apds9960_get_proximity_down_left_offset test.
apds9960: set proximity down left offset -19.
apds9960: check proximity down left offset ok.
apds9960: apds9960_set_proximity_gain_compensation/apds9960_get_proximity_gain_compensation test.
apds9960: enable proximity gain compensation.
apds9960: check proximity gain compensation ok.
apds9960: disable proximity gain compensation.
apds9960: check proximity gain compensation ok.
apds9960: apds9960_set_sleep_after_interrupt/apds9960_get_sleep_after_interrupt test.
apds9960: enable sleep after interrupt.
apds9960: check sleep after interrupt ok.
apds9960: disable sleep after interrupt.
apds9960: check sleep after interrupt ok.
apds9960: apds9960_set_proximity_mask/apds9960_get_proximity_mask test.
apds9960: enable proximity mask up.
apds9960: check proximity mask ok.
apds9960: disable proximity mask up.
apds9960: check proximity mask ok.
apds9960: enable proximity mask down.
apds9960: check proximity mask ok.
apds9960: disable proximity mask down.
apds9960: check proximity mask ok.
apds9960: enable proximity mask left.
apds9960: check proximity mask ok.
apds9960: disable proximity mask left.
apds9960: check proximity mask ok.
apds9960: enable proximity mask right.
apds9960: check proximity mask ok.
apds9960: disable proximity mask right.
apds9960: check proximity mask ok.
apds9960: apds9960_set_gesture_proximity_enter_threshold/apds9960_get_gesture_proximity_enter_threshold test.
apds9960: set gesture proximity enter threshold 0xC4.
apds9960: check gesture proximity enter threshold ok.
apds9960: apds9960_set_gesture_proximity_exit_threshold/apds9960_get_gesture_proximity_exit_threshold test.
apds9960: set gesture proximity exit threshold 0x6C.
apds9960: check gesture proximity exit threshold ok.
apds9960: apds9960_set_gesture_fifo_threshold/apds9960_get_gesture_fifo_threshold test.
apds9960: set gesture fifo threshold 1 dataset.
apds9960: check gesture fifo threshold ok.
apds9960: set gesture fifo threshold 4 dataset.
apds9960: check gesture fifo threshold ok.
apds9960: set gesture fifo threshold 8 dataset.
apds9960: check gesture fifo threshold ok.
apds9960: set gesture fifo threshold 16 dataset.
apds9960: check gesture fifo threshold ok.
apds9960: apds9960_set_gesture_exit_persistence/apds9960_get_gesture_exit_persistence test.
apds9960: set gesture exit persistence 1st.
apds9960: check gesture exit persistence ok.
apds9960: set gesture exit persistence 2nd.
apds9960: check gesture exit persistence ok.
apds9960: set gesture exit persistence 4th.
apds9960: check gesture exit persistence ok.
apds9960: set gesture exit persistence 7th.
apds9960: check gesture exit persistence ok.
apds9960: apds9960_set_gesture_exit_mask/apds9960_get_gesture_exit_mask test.
apds9960: set gesture exit mask 0x7.
apds9960: check gesture exit mask ok.
apds9960: apds9960_set_gesture_gain/apds9960_get_gesture_gain test.
apds9960: set gesture gain 1x.
apds9960: check gesture gain ok.
apds9960: set gesture gain 2x.
apds9960: check gesture gain ok.
apds9960: set gesture gain 4x.
apds9960: check gesture gain ok.
apds9960: set gesture gain 8x.
apds9960: check gesture gain ok.
apds9960: apds9960_set_gesture_led_current/apds9960_get_gesture_led_current test.
apds9960: set gesture led current 100 mA.
apds9960: check gesture led current ok.
apds9960: set gesture led current 50 mA.
apds9960: check gesture led current ok.
apds9960: set gesture led current 25 mA.
apds9960: check gesture led current ok.
apds9960: set gesture led current 12.5 mA.
apds9960: check gesture led current ok.
apds9960: apds9960_set_gesture_wait_time/apds9960_get_gesture_wait_time test.
apds9960: set gesture wait time 0 ms.
apds9960: check gesture wait time ok.
apds9960: set gesture wait time 2.8 ms.
apds9960: check gesture wait time ok.
apds9960: set gesture wait time 5.6 ms.
apds9960: check gesture wait time ok.
apds9960: set gesture wait time 8.4 ms.
apds9960: check gesture wait time ok.
apds9960: set gesture wait time 14 ms.
apds9960: check gesture wait time ok.
apds9960: set gesture wait time 22.4 ms.
apds9960: check gesture wait time ok.
apds9960: set gesture wait time 30.8 ms.
apds9960: check gesture wait time ok.
apds9960: set gesture wait time 39.2 ms.
apds9960: check gesture wait time ok.
apds9960: apds9960_set_gesture_up_offset/apds9960_get_gesture_up_offset test.
apds9960: set gesture up offset 58.
apds9960: check gesture up offset ok.
apds9960: apds9960_set_gesture_down_offset/apds9960_get_gesture_down_offset test.
apds9960: set gesture down offset -97.
apds9960: check gesture down offset ok.
apds9960: apds9960_set_gesture_left_offset/apds9960_get_gesture_left_offset test.
apds9960: set gesture left offset 101.
apds9960: check gesture left offset ok.
apds9960: apds9960_set_gesture_right_offset/apds9960_get_gesture_right_offset test.
apds9960: set gesture right offset -33.
apds9960: check gesture right offset ok.
apds9960: apds9960_set_gesture_pulse_length/apds9960_get_gesture_pulse_length test.
apds9960: set gesture pulse length 4 us.
apds9960: check gesture pulse length ok.
apds9960: set gesture pulse length 8 us.
apds9960: check gesture pulse length ok.
apds9960: set gesture pulse length 16 us.
apds9960: check gesture pulse length ok.
apds9960: set gesture pulse length 32 us.
apds9960: check gesture pulse length ok.
apds9960: apds9960_set_gesture_pulse_count/apds9960_get_gesture_pulse_count test.
apds9960: set gesture pulse count 50.
apds9960: check gesture pulse count ok.
apds9960: apds9960_set_gesture_dimension/apds9960_get_gesture_dimension_select test.
apds9960: set both pairs active.
apds9960: check gesture dimension select ok.
apds9960: set only up down pair active.
apds9960: check gesture dimension select ok.
apds9960: set only left right pair active.
apds9960: check gesture dimension select ok.
apds9960: apds9960_set_gesture_interrupt/apds9960_get_gesture_interrupt test.
apds9960: enable gesture interrupt.
apds9960: check gesture interrupt ok.
apds9960: disable gesture interrupt.
apds9960: check gesture interrupt ok.
apds9960: apds9960_set_gesture_mode/apds9960_get_gesture_mode test.
apds9960: enable gesture mode.
apds9960: check gesture mode ok.
apds9960: disable gesture mode.
apds9960: check gesture mode ok.
apds9960: apds9960_set_gesture_decode_threshold/apds9960_get_gesture_decode_threshold test.
apds9960: set gesture decode threshold 0x64.
apds9960: check gesture decode threshold ok.
apds9960: apds9960_set_gesture_decode_sensitivity_1/apds9960_get_gesture_decode_sensitivity_1 test.
apds9960: set gesture decode sensitivity 1 29497.
apds9960: check gesture decode sensitivity ok.
apds9960: apds9960_set_gesture_decode_sensitivity_2/apds9960_get_gesture_decode_sensitivity_2 test.
apds9960: set gesture decode sensitivity 2 58941.
apds9960: check gesture decode sensitivity ok.
apds9960: apds9960_adc_integration_time_convert_to_register/apds9960_adc_integration_time_convert_to_data test.
apds9960: set adc integration time 35.00.
apds9960: check adc integration time 36.14.
apds9960: apds9960_wait_time_convert_to_register/apds9960_wait_time_convert_to_data test.
apds9960: set wait time 36.20.
apds9960: check wait time 38.92.
apds9960: apds9960_get_status test.
apds9960: status is 0x00.
apds9960: apds9960_get_gesture_fifo_level test.
apds9960: fifo level is 0x00.
apds9960: apds9960_get_gesture_status test.
apds9960: gesture status is 0x00.
apds9960: apds9960_gesture_fifo_clear test.
apds9960: check gesture fifo clear ok.
apds9960: apds9960_force_interrupt test.
apds9960: check force interrupt ok.
apds9960: apds9960_proximity_interrupt_clear test.
apds9960: check proximity interrupt clear ok.
apds9960: apds9960_als_interrupt_clear test.
apds9960: check als interrupt clear ok.
apds9960: apds9960_all_non_gesture_interrupt_clear test.
apds9960: check all non gesture interrupt clear ok.
apds9960: finish register test.
```

```shell
apds9960 -t read 3

apds9960: chip is Broadcom APDS9960.
apds9960: manufacturer is Broadcom.
apds9960: interface is IIC.
apds9960: driver version is 1.0.
apds9960: min supply voltage is 2.4V.
apds9960: max supply voltage is 3.6V.
apds9960: max current is 100.00mA.
apds9960: max temperature is 85.0C.
apds9960: min temperature is -40.0C.
apds9960: start read test.
apds9960: red is 0x006F.
apds9960: green is 0x00D5.
apds9960: blue is 0x0091.
apds9960: clear is 0x006F.
apds9960: proximity is 0x05.
apds9960: red is 0x006F.
apds9960: green is 0x00D5.
apds9960: blue is 0x008F.
apds9960: clear is 0x0076.
apds9960: proximity is 0x04.
apds9960: red is 0x006F.
apds9960: green is 0x00D5.
apds9960: blue is 0x008F.
apds9960: clear is 0x006F.
apds9960: proximity is 0x06.
apds9960: finish read test.
```

```shell
apds9960 -t gesture 6

apds9960: chip is Broadcom APDS9960.
apds9960: manufacturer is Broadcom.
apds9960: interface is IIC.
apds9960: driver version is 1.0.
apds9960: min supply voltage is 2.4V.
apds9960: max supply voltage is 3.6V.
apds9960: max current is 100.00mA.
apds9960: max temperature is 85.0C.
apds9960: min temperature is -40.0C.
apds9960: start gesture test.
apds9960: irq gesture right.
apds9960: irq gesture left.
apds9960: irq gesture up.
apds9960: irq gesture down.
apds9960: irq gesture near.
apds9960: irq gesture far.
apds9960: finish gesture test.
```

```shell
apds9960 -t int 3 1 2000 1 150

apds9960: chip is Broadcom APDS9960.
apds9960: manufacturer is Broadcom.
apds9960: interface is IIC.
apds9960: driver version is 1.0.
apds9960: min supply voltage is 2.4V.
apds9960: max supply voltage is 3.6V.
apds9960: max current is 100.00mA.
apds9960: max temperature is 85.0C.
apds9960: min temperature is -40.0C.
apds9960: start interrupt test.
apds9960: proximity is 0xF8.
apds9960: proximity is 0xFF.
apds9960: red is 0x0087.
apds9960: green is 0x0037.
apds9960: blue is 0x008F.
apds9960: clear is 0x0057.
apds9960: finish interrupt test.
```

```shell
apds9960 -c read 3

1/3.
apds9960: red is 0x00C9.
apds9960: green is 0x00E1.
apds9960: blue is 0x00B9.
apds9960: clear is 0x00E3.
apds9960: proximity is 0xA7.
2/3.
apds9960: red is 0x00CB.
apds9960: green is 0x00E4.
apds9960: blue is 0x00C0.
apds9960: clear is 0x00D3.
apds9960: proximity is 0xB5.
3/3.
apds9960: red is 0x00A8.
apds9960: green is 0x00C7.
apds9960: blue is 0x00AB.
apds9960: clear is 0x00F6.
apds9960: proximity is 0x51.
```

```shell
apds9960 -c gesture 6

apds9960: irq gesture right.
apds9960: irq gesture left.
apds9960: irq gesture up.
apds9960: irq gesture down.
apds9960: irq gesture left.
apds9960: irq gesture near.
```

```shell
apds9960 -c int 3 1 2000 1 150

apds9960: proximity is 0xCF.
apds9960: proximity is 0xFF.
apds9960: red is 0x0097.
apds9960: green is 0x003F.
apds9960: blue is 0x0097.
apds9960: clear is 0x00AF.
```

```shell
apds9960 -h

apds9960 -i
	show apds9960 chip and driver information.
apds9960 -h
	show apds9960 help.
apds9960 -p
	show apds9960 pin connections of the current board.
apds9960 -t reg
	run apds9960 register test.
apds9960 -t read <times>
	run apds9960 read test.times means test times.
apds9960 -t int <times> <alslowthreshold> <alshighthreshold> <proximitylowthreshold> <proximityhighthreshold>
	run apds9960 interrupt test.times means test times.alslowthreshold is the als low threshold.alshighthreshold is the als high threshold.proximitylowthreshold is the proximity low threshold.proximityhighthreshold is the proximity high threshold.
apds9960 -t gesture <times>
	run apds9960 gesture test.times means test times.
apds9960 -c read <times>
	run apds9960 read function.times means test times.
apds9960 -c gesture <times>
	run apds9960 gesture function.times means test times.
apds9960 -c int <times> <alslowthreshold> <alshighthreshold> <proximitylowthreshold> <proximityhighthreshold>
	run apds9960 interrupt function.times means test times.alslowthreshold is the als low threshold.alshighthreshold is the als high threshold.proximitylowthreshold is the proximity low threshold.proximityhighthreshold is the proximity high threshold.
```

