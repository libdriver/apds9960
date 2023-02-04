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
 * @file      driver_apds9960.c
 * @brief     driver apds9960 source file
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

#include "driver_apds9960.h"
#include <stdlib.h>

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Broadcom APDS9960"        /**< chip name */
#define MANUFACTURER_NAME         "Broadcom"                 /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.4f                       /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                       /**< chip max supply voltage */
#define MAX_CURRENT               100.0f                     /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                     /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                      /**< chip max operating temperature */
#define DRIVER_VERSION            1000                       /**< driver version */

/**
 * @brief iic address definition
 */
#define APDS9960_ADDRESS        0x72        /**< iic address */

/**
 * @brief chip register definition
 */
#define APDS9960_REG_ENABLE         0x80        /**< enable states and interrupts register */
#define APDS9960_REG_ATIME          0x81        /**< adc integration time register */
#define APDS9960_REG_WTIME          0x83        /**< wait time register */
#define APDS9960_REG_AILTL          0x84        /**< als interrupt low threshold low byte register */
#define APDS9960_REG_AILTH          0x85        /**< als interrupt low threshold high byte register */
#define APDS9960_REG_AIHTL          0x86        /**< als interrupt high threshold low byte register */
#define APDS9960_REG_AIHTH          0x87        /**< als interrupt high threshold high byte register */
#define APDS9960_REG_PILT           0x89        /**< proximity interrupt low threshold register */
#define APDS9960_REG_PIHT           0x8B        /**< proximity interrupt high threshold register */
#define APDS9960_REG_PERS           0x8C        /**< interrupt persistence filters register */
#define APDS9960_REG_CONFIG1        0x8D        /**< configuration register one register */
#define APDS9960_REG_PPULSE         0x8E        /**< proximity pulse count and length register */
#define APDS9960_REG_CONTROL        0x8F        /**< gain control register */
#define APDS9960_REG_CONFIG2        0x90        /**< configuration register two register */
#define APDS9960_REG_ID             0x92        /**< device id register */
#define APDS9960_REG_STATUS         0x93        /**< device status register */
#define APDS9960_REG_CDATAL         0x94        /**< low byte of clear channel data register */
#define APDS9960_REG_CDATAH         0x95        /**< high byte of clear channel data register */
#define APDS9960_REG_RDATAL         0x96        /**< low byte of red channel data register */
#define APDS9960_REG_RDATAH         0x97        /**< high byte of red channel data register */
#define APDS9960_REG_GDATAL         0x98        /**< low byte of green channel data register */
#define APDS9960_REG_GDATAH         0x99        /**< high byte of green channel data register */
#define APDS9960_REG_BDATAL         0x9A        /**< low byte of blue channel data register */
#define APDS9960_REG_BDATAH         0x9B        /**< high byte of blue channel data register */
#define APDS9960_REG_PDATA          0x9C        /**< proximity data register */
#define APDS9960_REG_POFFSET_UR     0x9D        /**< proximity offset for UP and RIGHT photo diodes register */
#define APDS9960_REG_POFFSET_DL     0x9E        /**< proximity offset for DOWN and LEFT photo diodes register */
#define APDS9960_REG_CONFIG3        0x9F        /**< configuration register three register */
#define APDS9960_REG_GPENTH         0xA0        /**< gesture proximity enter threshold register */
#define APDS9960_REG_GEXTH          0xA1        /**< gesture exit threshold register */
#define APDS9960_REG_GCONF1         0xA2        /**< gesture configuration one register */
#define APDS9960_REG_GCONF2         0xA3        /**< gesture configuration two register */
#define APDS9960_REG_GOFFSET_U      0xA4        /**< gesture UP offset register */
#define APDS9960_REG_GOFFSET_D      0xA5        /**< gesture DOWN offset register */
#define APDS9960_REG_GOFFSET_L      0xA7        /**< gesture LEFT offset register */
#define APDS9960_REG_GOFFSET_R      0xA9        /**< gesture RIGHT offset register */
#define APDS9960_REG_GPULSE         0xA6        /**< gesture pulse count and length register */
#define APDS9960_REG_GCONF3         0xAA        /**< gesture configuration three register */
#define APDS9960_REG_GCONF4         0xAB        /**< gesture configuration four register */
#define APDS9960_REG_GFLVL          0xAE        /**< gesture fifo level register */
#define APDS9960_REG_GSTATUS        0xAF        /**< gesture status register */
#define APDS9960_REG_IFORCE         0xE4        /**< force interrupt register */
#define APDS9960_REG_PICLEAR        0xE5        /**< proximity interrupt clear register */
#define APDS9960_REG_CICLEAR        0xE6        /**< als clear channel interrupt clear register */
#define APDS9960_REG_AICLEAR        0xE7        /**< all non-gesture interrupts clear register */
#define APDS9960_REG_GFIFO_U        0xFC        /**< gesture fifo UP value register */
#define APDS9960_REG_GFIFO_D        0xFD        /**< gesture fifo DOWN value register */
#define APDS9960_REG_GFIFO_L        0xFE        /**< gesture fifo LEFT value register */
#define APDS9960_REG_GFIFO_R        0xFF        /**< gesture fifo RIGHT value register */

/**
 * @brief      read bytes
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *data points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_apds9960_iic_read(apds9960_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_read(APDS9960_ADDRESS, reg, data, len) != 0)        /* read the register */
    {
        return 1;                                                       /* return error */
    }
    else
    {
        return 0;                                                       /* success return 0 */
    }
}

/**
 * @brief     write bytes
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_apds9960_iic_write(apds9960_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_write(APDS9960_ADDRESS, reg, data, len) != 0)        /* write the register */
    {
        return 1;                                                        /* return error */
    }
    else
    {
        return 0;                                                        /* success return 0 */
    }
}

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 read id failed
 *            - 5 id is invalid
 * @note      none
 */
uint8_t apds9960_init(apds9960_handle_t *handle)
{
    uint8_t id;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->debug_print == NULL)                                         /* check debug_print */
    {
        return 3;                                                            /* return error */
    }
    if (handle->iic_init == NULL)                                            /* check iic_init */
    {
        handle->debug_print("apds9960: iic_init is null.\n");                /* iic_init is null */
        
        return 3;                                                            /* return error */
    }
    if (handle->iic_deinit == NULL)                                          /* check iic_deinit */
    {
        handle->debug_print("apds9960: iic_deinit is null.\n");              /* iic_deinit is null */
        
        return 3;                                                            /* return error */
    }
    if (handle->iic_read == NULL)                                            /* check iic_read */
    {
        handle->debug_print("apds9960: iic_read is null.\n");                /* iic_read is null */
        
        return 3;                                                            /* return error */
    }
    if (handle->iic_write == NULL)                                           /* check iic_write */
    {
        handle->debug_print("apds9960: iic_write is null.\n");               /* iic_write is null */
        
        return 3;                                                            /* return error */
    }
    if (handle->delay_ms == NULL)                                            /* check delay_ms */
    {
        handle->debug_print("apds9960: delay_ms is null.\n");                /* delay_ms is null */
        
        return 3;                                                            /* return error */
    }
    if (handle->receive_callback == NULL)                                    /* check receive_callback */
    {
        handle->debug_print("apds9960: receive_callback is null.\n");        /* receive_callback is null */
        
        return 3;                                                            /* return error */
    }
    
    if (handle->iic_init() != 0)                                             /* iic init */
    {
        handle->debug_print("apds9960: iic init failed.\n");                 /* iic init failed */
        
        return 1;                                                            /* return error */
    }
    if (a_apds9960_iic_read(handle, APDS9960_REG_ID, (uint8_t *)&id, 1) != 0)/* read id */
    {
        handle->debug_print("apds9960: read id failed.\n");                  /* read id failed */
        (void)handle->iic_deinit();                                          /* iic deinit */
        
        return 4;                                                            /* return error */
    }
    if (id != 0xAB)                                                          /* check id */
    {
        handle->debug_print("apds9960: id is invalid.\n");                   /* id is invalid */
        (void)handle->iic_deinit();                                          /* iic deinit */
        
        return 5;                                                            /* return error */
    }
    handle->gesture_status = 0;                                              /* clear the gesture status */
    handle->gesture_threshold = APDS9960_GESTURE_THRESHOLD;                  /* set the default gesture threshold */
    handle->gesture_sensitivity_1 = APDS9960_GESTURE_SENSITIVITY_1;          /* set the default gesture sensitivity 1 */
    handle->gesture_sensitivity_2 = APDS9960_GESTURE_SENSITIVITY_2;          /* set the default gesture sensitivity 2 */
    handle->gesture_ud_delta = 0;                                            /* set gesture_ud_delta 0 */
    handle->gesture_lr_delta = 0;                                            /* set gesture_lr_delta 0 */
    handle->gesture_ud_count = 0;                                            /* set gesture_ud_count 0 */
    handle->gesture_lr_count = 0;                                            /* set gesture_lr_count 0 */
    handle->gesture_near_count = 0;                                          /* set gesture_near_count 0 */
    handle->gesture_far_count = 0;                                           /* set gesture_far_count 0 */
    handle->inited = 1;                                                      /* flag inited */
    
    return 0;                                                                /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t apds9960_deinit(apds9960_handle_t *handle)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_ENABLE, (uint8_t *)&prev, 1);        /* read enable register */
    if (res != 0)                                                                       /* check the result */
    {
        handle->debug_print("apds9960: read enable register failed.\n");                /* read enable register failed */
        
        return 4;                                                                       /* return error */
    }
    prev &= ~(1 << 0);                                                                  /* set power down */
    res = a_apds9960_iic_write(handle, APDS9960_REG_ENABLE, (uint8_t *)&prev, 1);       /* write enable register */
    if (res != 0)                                                                       /* check the result */
    {
        handle->debug_print("apds9960: write enable register failed.\n");               /* write enable register failed */
        
        return 4;                                                                       /* return error */
    }
    res = handle->iic_deinit();                                                         /* iic deinit */
    if (res != 0)                                                                       /* check the result */
    {
        handle->debug_print("apds9960: iic deinit failed.\n");                          /* iic deinit failed */
        
        return 1;                                                                       /* return error */
    }
    else
    {
        handle->inited = 0;                                                             /* flag closed */
        
        return 0;                                                                       /* success return 0 */
    }
}

/**
 * @brief     irq handler
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_irq_handler(apds9960_handle_t *handle)
{
    uint8_t res, prev, prev1;
    uint8_t times;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_STATUS, (uint8_t *)&prev, 1);             /* read status */
    if (res != 0)                                                                            /* check the result */
    {
        handle->debug_print("apds9960: read status failed.\n");                              /* read status failed */
        
        return 1;                                                                            /* return error */
    }
    res = a_apds9960_iic_read(handle, APDS9960_REG_GSTATUS, (uint8_t *)&prev1, 1);           /* read gesture status */
    if (res != 0)                                                                            /* check the result */
    {
        handle->debug_print("apds9960: read gesture status failed.\n");                      /* read gesture status failed */
        
        return 1;                                                                            /* return error */
    }
    
    if ((prev & (1 << APDS9960_STATUS_CPSAT)) != 0)                                          /* check clear photo diode saturation */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_CPSAT);                       /* run the callback */
        }
    }
    if ((prev & (1 << APDS9960_STATUS_PGSAT)) != 0)                                          /* check analog saturation */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_PGSAT);                       /* run the callback */
        }
    }
    if ((prev & (1 << APDS9960_STATUS_PINT)) != 0)                                           /* check proximity interrupt */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_PINT);                        /* run the callback */
        }
    }
    if ((prev & (1 << APDS9960_STATUS_AINT)) != 0)                                           /* check als interrupt */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_AINT);                        /* run the callback */
        }
    }
    if ((prev & (1 << APDS9960_STATUS_GINT)) != 0)                                           /* gesture interrupt */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_GINT);                        /* run the callback */
        }
    }
    if ((prev & (1 << APDS9960_STATUS_PVALID)) != 0)                                         /* check proximity valid */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_PVALID);                      /* run the callback */
        }
    }
    if ((prev & (1 << APDS9960_STATUS_AVALID)) != 0)                                         /* check als valid */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_AVALID);                      /* run the callback */
        }
    }
    if ((prev1 & (1 << APDS9960_GESTURE_STATUS_FIFO_OVERFLOW)) != 0)                         /* check gesture fifo overflow */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_GFOV);                        /* run the callback */
        }
    }
    if ((prev1 & (1 << APDS9960_GESTURE_STATUS_FIFO_VALID)) != 0)                            /* check gesture fifo data */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_GVALID);                      /* run the callback */
        }
    }
    
    times = 3;                                                                               /* set retry times */
    while (1)                                                                                /* retry label */
    {
        prev = 0xFF;                                                                         /* set 0xFF */
        res = a_apds9960_iic_write(handle, APDS9960_REG_AICLEAR, (uint8_t *)&prev, 1);       /* clear all non-gesture interrupts */
        if (res != 0)                                                                        /* check result */
        {
            if (times != 0)                                                                  /* check retry times */
            {
                times--;                                                                     /* times-- */
                
                continue;                                                                    /* continue */
            }
            
            handle->debug_print("apds9960: clear all non-gesture interrupts failed.\n");     /* clear all non-gesture interrupts failed */
           
            return 1;                                                                        /* return error */
        }
        
        res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);         /* get gesture conf 4 register */
        if (res != 0)                                                                        /* check result */
        {
            if (times != 0)                                                                  /* check retry times */
            {
                times--;                                                                     /* times-- */
                
                continue;                                                                    /* continue */
            }
            
            handle->debug_print("apds9960: get gesture conf 4 register failed.\n");          /* get gesture conf 4 register failed */
           
            return 1;                                                                        /* return error */
        }
        prev &= ~(1 << 2);                                                                   /* clear config */
        prev |= 1 << 2;                                                                      /* set config */
        res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);        /* set gesture conf 4 register */
        if (res != 0)                                                                        /* check result */
        {
            if (times != 0)                                                                  /* check retry times */
            {
                times--;                                                                     /* times-- */
                
                continue;                                                                    /* continue */
            }
            
            handle->debug_print("apds9960: set gesture conf 4 register failed.\n");          /* set gesture conf 4 register failed */
           
            return 1;                                                                        /* return error */
        }
        
        break;                                                                               /* break */
    }
    
    prev = handle->gesture_status;                                                           /* get the gesture status */
    if ((prev & (1 << 0)) != 0)                                                              /* check far */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_GESTURE_FAR);                 /* run the callback */
        }
    }
    if ((prev & (1 << 1)) != 0)                                                              /* check near */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_GESTURE_NEAR);                /* run the callback */
        }
    }
    if ((prev & (1 << 2)) != 0)                                                              /* check down */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_GESTURE_DOWN);                /* run the callback */
        }
    }
    if ((prev & (1 << 3)) != 0)                                                              /* check up */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_GESTURE_UP);                  /* run the callback */
        }
    }
    if ((prev & (1 << 4)) != 0)                                                              /* check right */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_GESTURE_RIGHT);               /* run the callback */
        }
    }
    if ((prev & (1 << 5)) != 0)                                                              /* check left */
    {
        if (handle->receive_callback != NULL)                                                /* if valid */
        {
            handle->receive_callback(APDS9960_INTERRUPT_STATUS_GESTURE_LEFT);                /* run the callback */
        }
    }
    handle->gesture_status = 0;                                                              /* clear the gesture status */
    if (prev != 0)                                                                           /* if we find gesture */
    {
        handle->gesture_ud_delta = 0;                                                        /* set gesture_ud_delta 0 */
        handle->gesture_lr_delta = 0;                                                        /* set gesture_lr_delta 0 */
        handle->gesture_ud_count = 0;                                                        /* set gesture_ud_count 0 */
        handle->gesture_lr_count = 0;                                                        /* set gesture_lr_count 0 */
        handle->gesture_near_count = 0;                                                      /* set gesture_near_count 0 */
        handle->gesture_far_count = 0;                                                       /* set gesture_far_count 0 */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     decode gestures from the fifo data
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] **data points to data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 decode gesture from fifo failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 decode failed
 * @note      none
 */
uint8_t apds9960_gesture_decode(apds9960_handle_t *handle, uint8_t (*data)[4], uint8_t len)
{
    int8_t i;
    uint8_t u_first, d_first, l_first, r_first;
    uint8_t u_last, d_last, l_last, r_last;
    int32_t ud_ratio_first, lr_ratio_first, ud_ratio_last, lr_ratio_last;
    int32_t ud_delta, lr_delta;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    if (len < 4)                                                                         /* check len */
    {
        handle->debug_print("apds9960: fifo level must be over 4.\n");                   /* fifo level must be over 4 */
       
        return 4;                                                                        /* return error */
    }
    
    u_first = 0;                                                                         /* clear up first */
    d_first = 0;                                                                         /* clear down first */
    l_first = 0;                                                                         /* clear left first */
    r_first = 0;                                                                         /* clear right first */
    u_last = 0;                                                                          /* clear up last */
    d_last = 0;                                                                          /* clear down last */
    l_last = 0;                                                                          /* clear left last */
    r_last = 0;                                                                          /* clear right last */
    for (i = 0; i < len; i++)                                                            /* run len times */
    {
        if ((data[i][0] > handle->gesture_threshold) &&                                  /* check gesture threshold */
            (data[i][1] > handle->gesture_threshold) &&                                  /* check gesture threshold */
            (data[i][2] > handle->gesture_threshold) &&                                  /* check gesture threshold */
            (data[i][3] > handle->gesture_threshold)                                     /* check gesture threshold */
           )
        {
            u_first = data[i][0];                                                        /* set up first */
            d_first = data[i][1];                                                        /* set down first */
            l_first = data[i][2];                                                        /* set left first */
            r_first = data[i][3];                                                        /* set right first */
            
            break;                                                                       /* break */
        }
    }
    if ((u_first == 0) ||                                                                /* check up first */
        (d_first == 0) ||                                                                /* check down first */
        (l_first == 0) ||                                                                /* check left first */
        (r_first == 0)                                                                   /* check right first */
       )
    {
        goto decode;                                                                     /* go to decode */
    }
    for (i = len - 1; i >= 0; i--)                                                       /* run len times */
    {
        if ((data[i][0] > handle->gesture_threshold) &&                                  /* check gesture threshold */
            (data[i][1] > handle->gesture_threshold) &&                                  /* check gesture threshold */
            (data[i][2] > handle->gesture_threshold) &&                                  /* check gesture threshold */
            (data[i][3] > handle->gesture_threshold)                                     /* check gesture threshold */
           )
        {
            u_last = data[i][0];                                                         /* set up last */
            d_last = data[i][1];                                                         /* set down last */
            l_last = data[i][2];                                                         /* set left last */
            r_last = data[i][3];                                                         /* set right last */
            
            break;                                                                       /* break */
        }
    }
    ud_ratio_first = ((u_first - d_first) * 100) / (u_first + d_first);                  /* get ud ratio first */
    lr_ratio_first = ((l_first - r_first) * 100) / (l_first + r_first);                  /* get lr ratio first */
    ud_ratio_last = ((u_last - d_last) * 100) / (u_last + d_last);                       /* get ud ratio last */
    lr_ratio_last = ((l_last - r_last) * 100) / (l_last + r_last);                       /* get lr ratio last */
    ud_delta = ud_ratio_last - ud_ratio_first;                                           /* get ud delta */
    lr_delta = lr_ratio_last - lr_ratio_first;                                           /* get lr delta */
    handle->gesture_ud_delta += ud_delta;                                                /* gesture_ud_delta++ */
    handle->gesture_lr_delta += lr_delta;                                                /* gesture_lr_delta++ */
    
    if (handle->gesture_ud_delta >= handle->gesture_sensitivity_1)                       /* check gesture_ud_delta */
    {
        handle->gesture_ud_count = 1;                                                    /* set gesture_ud_count 1 */
    } 
    else if (handle->gesture_ud_delta  <= -handle->gesture_sensitivity_1)                /* check gesture_ud_delta */
    {
        handle->gesture_ud_count = -1;                                                   /* set gesture_ud_count -1 */
    } 
    else 
    {
        handle->gesture_ud_count = 0;                                                    /* set gesture_ud_count 0 */
    }
    if (handle->gesture_lr_delta >= handle->gesture_sensitivity_1)                       /* check gesture_lr_delta */
    {
        handle->gesture_lr_count = 1;                                                    /* set gesture_lr_count 1 */
    } 
    else if (handle->gesture_lr_delta <= -handle->gesture_sensitivity_1)                 /* check gesture_lr_delta */
    {
        handle->gesture_lr_count = -1;                                                   /* set gesture_lr_count -1 */
    } 
    else 
    {
        handle->gesture_lr_count = 0;                                                    /* set gesture_lr_count 0 */
    }
    
    if ((handle->gesture_ud_count == 0) && (handle->gesture_lr_count == 0))              /* check gesture_ud_count && gesture_lr_count */
    {
        if ((abs(ud_delta) < handle->gesture_sensitivity_2) &&                           /* check ud_delta */
            (abs(lr_delta) < handle->gesture_sensitivity_2))                             /* check lr_delta */
        {
            if ((ud_delta == 0) && (lr_delta == 0))                                      /* if ud_delta == 0 && lr_delta == 0 */
            {
                handle->gesture_near_count++;                                            /* gesture_near_count++ */
            } 
            else if ((ud_delta != 0) || (lr_delta != 0))                                 /* if ud_delta != 0 && lr_delta != 0 */
            {
                handle->gesture_far_count++;                                             /* gesture_far_count++ */
            }
            else
            {
                
            }
            if ((handle->gesture_near_count >= 10) &&                                    /* check gesture_near_count */
                (handle->gesture_far_count >= 2))                                        /* check gesture_far_count */
            {
                if ((ud_delta == 0) && (lr_delta == 0))                                  /* if ud_delta == 0 && lr_delta == 0 */
                {
                    handle->gesture_status |= 1 << 1;                                    /* near */
                } 
                else if ((ud_delta != 0) && (lr_delta != 0))                             /* if ud_delta != 0 && lr_delta != 0 */
                {
                    handle->gesture_status |= 1 << 0;                                    /* far */
                }
                else
                {
                                                                                         /* do nothing */
                }
            }
        }
    } 
    else 
    {
        if ((abs(ud_delta) < handle->gesture_sensitivity_2) &&                           /* check ud_delta */
            (abs(lr_delta) < handle->gesture_sensitivity_2))                             /* check lr_delta */
        {
            if ((ud_delta == 0) && (lr_delta == 0))                                      /* if ud_delta == 0 && lr_delta == 0 */
            {
                handle->gesture_near_count++;                                            /* gesture_near_count++ */
            }
            if (handle->gesture_near_count >= 10)                                        /* if gesture_near_count >= 10 */
            {
                handle->gesture_ud_count = 0;                                            /* set gesture_ud_count 0 */
                handle->gesture_lr_count = 0;                                            /* set gesture_lr_count 0 */
                handle->gesture_ud_delta = 0;                                            /* set gesture_ud_delta 0 */
                handle->gesture_lr_delta = 0;                                            /* set gesture_lr_delta 0 */
            }
        }
    }
    
    decode:
    
    if ((handle->gesture_ud_count == -1) && (handle->gesture_lr_count == 0))             /* if gesture_ud_count == -1 && gesture_lr_count == 0 */
    {
        handle->gesture_status |= 1 << 4;                                                /* right */
    } 
    else if ((handle->gesture_ud_count == 1) && (handle->gesture_lr_count == 0))         /* if gesture_ud_count == 1 && gesture_lr_count == 0 */
    {
        handle->gesture_status |= 1 << 5;                                                /* left */
    } 
    else if ((handle->gesture_ud_count == 0) && (handle->gesture_lr_count == 1))         /* if gesture_ud_count == 0 && gesture_lr_count == 1 */
    {
        handle->gesture_status |= 1 << 2;                                                /* down */
    } 
    else if ((handle->gesture_ud_count == 0) && (handle->gesture_lr_count == -1))        /* if gesture_ud_count == 0 && gesture_lr_count == -1 */
    {
        handle->gesture_status |= 1 << 3;                                                /* up */
    } 
    else if ((handle->gesture_ud_count == -1) && (handle->gesture_lr_count == 1))        /* if gesture_ud_count == -1 && gesture_lr_count == 1 */
    {
        if (abs(handle->gesture_ud_delta) > abs(handle->gesture_lr_delta))               /* check gesture_ud_delta && gesture_lr_delta */
        {
            handle->gesture_status |= 1 << 4;                                            /* right */
        } 
        else 
        {
            handle->gesture_status |= 1 << 2;                                            /* down */
        }
    } 
    else if ((handle->gesture_ud_count == 1) && (handle->gesture_lr_count == -1))        /* if gesture_ud_count == 1 && gesture_lr_count == -1 */
    {
        if (abs(handle->gesture_ud_delta) > abs(handle->gesture_lr_delta))               /* check gesture_ud_delta && gesture_lr_delta */
        {
            handle->gesture_status |= 1 << 5;                                            /* left */
        } 
        else 
        {
            handle->gesture_status |= 1 << 3;                                            /* up */
        }
    } 
    else if ((handle->gesture_ud_count == -1) && (handle->gesture_lr_count == -1))       /* if gesture_ud_count == -1 && gesture_lr_count == -1 */
    {
        if (abs(handle->gesture_ud_delta) > abs(handle->gesture_lr_delta))               /* check gesture_ud_delta && gesture_lr_delta */
        {
            handle->gesture_status |= 1 << 4;                                            /* right */
        } 
        else 
        {
            handle->gesture_status |= 1 << 3;                                            /* up */
        }
    } 
    else if ((handle->gesture_ud_count == 1) && (handle->gesture_lr_count == 1))         /* if gesture_ud_count == 1 && gesture_lr_count == 1 */
    {
        if (abs(handle->gesture_ud_delta) > abs(handle->gesture_lr_delta))               /* check gesture_ud_delta && gesture_lr_delta */
        {
            handle->gesture_status |= 1 << 5;                                            /* left */
        } 
        else 
        {
            handle->gesture_status |= 1 << 2;                                            /* down */
        }
    }
    else
    {
        
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     set the gesture decode threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the gesture decode threshold
 * @return    status code
 *            - 0 success
 *            - 1 set gesture decode threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_decode_threshold(apds9960_handle_t *handle, uint8_t threshold)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }
    
    handle->gesture_threshold = threshold;        /* set threshold */
    
    return 0;                                     /* success return 0 */
}

/**
 * @brief      get the gesture decode threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a gesture decode threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture decode threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_decode_threshold(apds9960_handle_t *handle, uint8_t *threshold)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }
    
    *threshold = handle->gesture_threshold;       /* get threshold */
    
    return 0;                                     /* success return 0 */
}

/**
 * @brief     set the gesture decode sensitivity 1
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] sensitivity is the gesture decode sensitivity
 * @return    status code
 *            - 0 success
 *            - 1 set gesture decode sensitivity 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_decode_sensitivity_1(apds9960_handle_t *handle, int32_t sensitivity)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    handle->gesture_sensitivity_1 = sensitivity;        /* set sensitivity */
    
    return 0;                                           /* success return 0 */
}

/**
 * @brief      get the gesture decode sensitivity 1
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *sensitivity points to a gesture decode sensitivity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture decode sensitivity 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_decode_sensitivity_1(apds9960_handle_t *handle, int32_t *sensitivity)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    *sensitivity = handle->gesture_sensitivity_1;       /* get sensitivity */
    
    return 0;                                           /* success return 0 */
}

/**
 * @brief     set the gesture decode sensitivity 2
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] sensitivity is the gesture decode sensitivity
 * @return    status code
 *            - 0 success
 *            - 1 set gesture decode sensitivity 2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_decode_sensitivity_2(apds9960_handle_t *handle, int32_t sensitivity)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    handle->gesture_sensitivity_2 = sensitivity;        /* set sensitivity */
    
    return 0;                                           /* success return 0 */
}

/**
 * @brief      get the gesture decode sensitivity 2
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *sensitivity points to a gesture decode sensitivity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture decode sensitivity 2 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_decode_sensitivity_2(apds9960_handle_t *handle, int32_t *sensitivity)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    *sensitivity = handle->gesture_sensitivity_2;       /* get sensitivity */
    
    return 0;                                           /* success return 0 */
}

/**
 * @brief     set the configuration
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] conf is the chip configuration
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set conf failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_conf(apds9960_handle_t *handle, apds9960_conf_t conf, apds9960_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_ENABLE, (uint8_t *)&prev, 1);        /* get enable */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: get enable failed.\n");                          /* get enable failed */
       
        return 1;                                                                       /* return error */
    }
    prev &= ~(1 << conf);                                                               /* clear conf */
    prev |= enable << conf;                                                             /* set conf */
    res = a_apds9960_iic_write(handle, APDS9960_REG_ENABLE, (uint8_t *)&prev, 1);       /* set enable */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: set enable failed.\n");                          /* set enable failed */
       
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief      get the configuration
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  conf is the chip configuration
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get conf failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_conf(apds9960_handle_t *handle, apds9960_conf_t conf, apds9960_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_ENABLE, (uint8_t *)&prev, 1);       /* get enable */
    if (res != 0)                                                                      /* check result */
    {
        handle->debug_print("apds9960: get enable failed.\n");                         /* get enable failed */
       
        return 1;                                                                      /* return error */
    }
    *enable = (apds9960_bool_t)((prev >> conf) & 0x01);                                /* get bool */
    
    return 0;                                                                          /* success return 0 */
}

/**
 * @brief     set the adc integration time
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] integration_time is the adc integration time
 * @return    status code
 *            - 0 success
 *            - 1 set adc integration time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_adc_integration_time(apds9960_handle_t *handle, uint8_t integration_time)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    prev = integration_time;                                                           /* set integration time */
    res = a_apds9960_iic_write(handle, APDS9960_REG_ATIME, (uint8_t *)&prev, 1);       /* set atime */
    if (res != 0)                                                                      /* check result */
    {
        handle->debug_print("apds9960: set atime failed.\n");                          /* set atime failed */
       
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

/**
 * @brief      get the adc integration time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *integration_time points to an adc integration time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get adc integration time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_adc_integration_time(apds9960_handle_t *handle, uint8_t *integration_time)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_ATIME, (uint8_t *)&prev, 1);       /* get atime */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: get atime failed.\n");                         /* get atime failed */
       
        return 1;                                                                     /* return error */
    }
    *integration_time = prev;                                                         /* get integration time */
    
    return 0;                                                                         /* success return 0 */
}

/**
 * @brief      convert the adc integration time to the register raw data
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  ms is the integration time
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_adc_integration_time_convert_to_register(apds9960_handle_t *handle, float ms, uint8_t *reg)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    if (handle->inited != 1)                   /* check handle initialization */
    {
        return 3;                              /* return error */
    }
    
    *reg = (uint8_t)(256.0f - ms / 2.78f);     /* convert real data to register data */
    
    return 0;                                  /* success return 0 */
}

/**
 * @brief      convert the register raw data to the integration time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *ms points to an adc integration time buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_adc_integration_time_convert_to_data(apds9960_handle_t *handle, uint8_t reg, float *ms)
{
    if (handle == NULL)                      /* check handle */
    {
        return 2;                            /* return error */
    }
    if (handle->inited != 1)                 /* check handle initialization */
    {
        return 3;                            /* return error */
    }
    
    *ms = (float)(256 - reg) * 2.78f;        /* convert raw data to real data */
    
    return 0;                                /* success return 0 */
}

/**
 * @brief     set the wait time
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] wait_time is the wait time
 * @return    status code
 *            - 0 success
 *            - 1 set wait time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_wait_time(apds9960_handle_t *handle, uint8_t wait_time)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    prev = wait_time;                                                                  /* set wait time */
    res = a_apds9960_iic_write(handle, APDS9960_REG_WTIME, (uint8_t *)&prev, 1);       /* set wtime */
    if (res != 0)                                                                      /* check result */
    {
        handle->debug_print("apds9960: set wtime failed.\n");                          /* set wtime failed */
       
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

/**
 * @brief      get the wait time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *wait_time points to a wait time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get wait time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_wait_time(apds9960_handle_t *handle, uint8_t *wait_time)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_WTIME, (uint8_t *)&prev, 1);       /* get wtime */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: get wtime failed.\n");                         /* get wtime failed */
       
        return 1;                                                                     /* return error */
    }
    *wait_time = prev;                                                                /* get wait time */
    
    return 0;                                                                         /* success return 0 */
}

/**
 * @brief      convert the wait time to the register raw data
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  ms is the wait time
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 1 get configuration register 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_wait_time_convert_to_register(apds9960_handle_t *handle, float ms, uint8_t *reg)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG1, (uint8_t *)&prev, 1);        /* get configuration register 1 */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get configuration register 1 failed.\n");         /* get configuration register 1 failed */
       
        return 1;                                                                        /* return error */
    }
    
    if ((prev & (1 << 1)) != 0)                                                          /* check wait long */
    {
        *reg = (uint8_t)(256.0f - ms / (2.78f * 12.0f));                                 /* convert real data to register data */
    }
    else
    {
        *reg = (uint8_t)(256.0f - ms / 2.78f);                                           /* convert real data to register data */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief      convert the register raw data to the wait time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *ms points to a wait time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get configuration register 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_wait_time_convert_to_data(apds9960_handle_t *handle, uint8_t reg, float *ms)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG1, (uint8_t *)&prev, 1);        /* get configuration register 1 */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get configuration register 1 failed.\n");         /* get configuration register 1 failed */
       
        return 1;                                                                        /* return error */
    }
    
    if ((prev & (1 << 1)) != 0)                                                          /* check wait long */
    {
        *ms = (float)(256 - reg) * 2.78f * 12.0f;                                        /* convert raw data to real data */
    }
    else
    {
        *ms = (float)(256 - reg) * 2.78f;                                                /* convert raw data to real data */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     set the als interrupt low threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the low threshold
 * @return    status code
 *            - 0 success
 *            - 1 set als interrupt low threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_als_interrupt_low_threshold(apds9960_handle_t *handle, uint16_t threshold)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    buf[0] = (threshold >> 0) & 0xFF;                                                /* set lsb */
    buf[1] = (threshold >> 8) & 0xFF;                                                /* set msb */
    res = a_apds9960_iic_write(handle, APDS9960_REG_AILTL, (uint8_t *)buf, 2);       /* set ailtl */
    if (res != 0)                                                                    /* check result */
    {
        handle->debug_print("apds9960: set ailtl failed.\n");                        /* set ailtl failed */
       
        return 1;                                                                    /* return error */
    }
    
    return 0;                                                                        /* success return 0 */
}

/**
 * @brief      get the als interrupt low threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a low threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get als interrupt low threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_als_interrupt_low_threshold(apds9960_handle_t *handle, uint16_t *threshold)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_AILTL, (uint8_t *)buf, 2);       /* get ailtl */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("apds9960: get ailtl failed.\n");                       /* get ailtl failed */
       
        return 1;                                                                   /* return error */
    }
    *threshold = (uint16_t)(((uint16_t)buf[1] << 8) | buf[0]);                      /* set threshold */
    
    return 0;                                                                       /* success return 0 */
}

/**
 * @brief     set the als interrupt high threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the high threshold
 * @return    status code
 *            - 0 success
 *            - 1 set als interrupt high threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_als_interrupt_high_threshold(apds9960_handle_t *handle, uint16_t threshold)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    buf[0] = (threshold >> 0) & 0xFF;                                                /* set lsb */
    buf[1] = (threshold >> 8) & 0xFF;                                                /* set msb */
    res = a_apds9960_iic_write(handle, APDS9960_REG_AIHTL, (uint8_t *)buf, 2);       /* set aihtl */
    if (res != 0)                                                                    /* check result */
    {
        handle->debug_print("apds9960: set aihtl failed.\n");                        /* set aihtl failed */
       
        return 1;                                                                    /* return error */
    }
    
    return 0;                                                                        /* success return 0 */
}

/**
 * @brief      get the als interrupt high threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a high threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get als interrupt high threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_als_interrupt_high_threshold(apds9960_handle_t *handle, uint16_t *threshold)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_AIHTL, (uint8_t *)buf, 2);       /* get aihtl */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("apds9960: get aihtl failed.\n");                       /* get aihtl failed */
       
        return 1;                                                                   /* return error */
    }
    *threshold = (uint16_t)(((uint16_t)buf[1] << 8) | buf[0]);                      /* set threshold */
    
    return 0;                                                                       /* success return 0 */
}

/**
 * @brief     set the proximity interrupt low threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the low threshold
 * @return    status code
 *            - 0 success
 *            - 1 set proximity interrupt low threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_interrupt_low_threshold(apds9960_handle_t *handle, uint8_t threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    prev = threshold;                                                                 /* set low threshold */
    res = a_apds9960_iic_write(handle, APDS9960_REG_PILT, (uint8_t *)&prev, 1);       /* set pilt */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: set pilt failed.\n");                          /* set pilt failed */
       
        return 1;                                                                     /* return error */
    }
    
    return 0;                                                                         /* success return 0 */
}

/**
 * @brief      get the proximity interrupt low threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a low threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity interrupt low threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_interrupt_low_threshold(apds9960_handle_t *handle, uint8_t *threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PILT, (uint8_t *)&prev, 1);       /* get pilt */
    if (res != 0)                                                                    /* check result */
    {
        handle->debug_print("apds9960: get pilt failed.\n");                         /* get pilt failed */
       
        return 1;                                                                    /* return error */
    }
    *threshold = prev;                                                               /* get low threshold */
    
    return 0;                                                                        /* success return 0 */
}

/**
 * @brief     set the proximity interrupt high threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the high threshold
 * @return    status code
 *            - 0 success
 *            - 1 set proximity interrupt high threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_interrupt_high_threshold(apds9960_handle_t *handle, uint8_t threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    prev = threshold;                                                                 /* set high threshold */
    res = a_apds9960_iic_write(handle, APDS9960_REG_PIHT, (uint8_t *)&prev, 1);       /* set piht */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: set piht failed.\n");                          /* set piht failed */
       
        return 1;                                                                     /* return error */
    }
    
    return 0;                                                                         /* success return 0 */
}

/**
 * @brief      get the proximity interrupt high threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a high threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity interrupt high threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_interrupt_high_threshold(apds9960_handle_t *handle, uint8_t *threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PIHT, (uint8_t *)&prev, 1);       /* get piht */
    if (res != 0)                                                                    /* check result */
    {
        handle->debug_print("apds9960: get piht failed.\n");                         /* get piht failed */
       
        return 1;                                                                    /* return error */
    }
    *threshold = prev;                                                               /* get high threshold */
    
    return 0;                                                                        /* success return 0 */
}

/**
 * @brief     set the proximity interrupt cycle
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] cycle is the proximity interrupt cycle
 * @return    status code
 *            - 0 success
 *            - 1 set proximity interrupt cycle failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_interrupt_cycle(apds9960_handle_t *handle, apds9960_proximity_interrupt_cycle_t cycle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PERS, (uint8_t *)&prev, 1);        /* get persistence register */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: get persistence register failed.\n");          /* get persistence register failed */
       
        return 1;                                                                     /* return error */
    }
    prev &= ~(0xF << 4);                                                              /* clear config */
    prev |= cycle << 4;                                                               /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_PERS, (uint8_t *)&prev, 1);       /* set persistence register */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: set persistence register failed.\n");          /* set persistence register failed */
       
        return 1;                                                                     /* return error */
    }
    
    return 0;                                                                         /* success return 0 */
}

/**
 * @brief      get the proximity interrupt cycle
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *cycle points to a proximity interrupt cycle buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity interrupt cycle failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_interrupt_cycle(apds9960_handle_t *handle, apds9960_proximity_interrupt_cycle_t *cycle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PERS, (uint8_t *)&prev, 1);        /* get persistence register */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: get persistence register failed.\n");          /* get persistence register failed */
       
        return 1;                                                                     /* return error */
    }
    *cycle = (apds9960_proximity_interrupt_cycle_t)((prev >> 4) & 0xF);               /* set cycle */
    
    return 0;                                                                         /* success return 0 */
}

/**
 * @brief     set the als interrupt cycle
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] cycle is the als interrupt cycle
 * @return    status code
 *            - 0 success
 *            - 1 set als interrupt cycle failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_als_interrupt_cycle(apds9960_handle_t *handle, apds9960_als_interrupt_cycle_t cycle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PERS, (uint8_t *)&prev, 1);        /* get persistence register */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: get persistence register failed.\n");          /* get persistence register failed */
       
        return 1;                                                                     /* return error */
    }
    prev &= ~(0xF << 0);                                                              /* clear config */
    prev |= cycle << 0;                                                               /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_PERS, (uint8_t *)&prev, 1);       /* set persistence register */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: set persistence register failed.\n");          /* set persistence register failed */
       
        return 1;                                                                     /* return error */
    }
    
    return 0;                                                                         /* success return 0 */
}

/**
 * @brief      get the als interrupt cycle
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *cycle points to an als interrupt cycle buffer
 * @return     status code
 *             - 0 success
 *             - 1 get als interrupt cycle failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_als_interrupt_cycle(apds9960_handle_t *handle, apds9960_als_interrupt_cycle_t *cycle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PERS, (uint8_t *)&prev, 1);        /* get persistence register */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("apds9960: get persistence register failed.\n");          /* get persistence register failed */
       
        return 1;                                                                     /* return error */
    }
    *cycle = (apds9960_als_interrupt_cycle_t)((prev >> 0) & 0xF);                     /* get als interrupt cycle */
    
    return 0;                                                                         /* success return 0 */
}

/**
 * @brief     enable or disable the wait long
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set wait long failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_wait_long(apds9960_handle_t *handle, apds9960_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG1, (uint8_t *)&prev, 1);        /* get configuration register 1 */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get configuration register 1 failed.\n");         /* get configuration register 1 failed */
       
        return 1;                                                                        /* return error */
    }
    prev &= ~(1 << 1);                                                                   /* clear config */
    prev |= enable << 1;                                                                 /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CONFIG1, (uint8_t *)&prev, 1);       /* set configuration register 1 */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: set configuration register 1 failed.\n");         /* set configuration register 1 failed */
       
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief      get the wait long status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get wait long failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_wait_long(apds9960_handle_t *handle, apds9960_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG1, (uint8_t *)&prev, 1);        /* get configuration register 1 */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get configuration register 1 failed.\n");         /* get configuration register 1 failed */
       
        return 1;                                                                        /* return error */
    }
    *enable = (apds9960_bool_t)((prev >> 1) & 0x1);                                      /* get bool */
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     set the proximity pulse length
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] len is the proximity pulse length
 * @return    status code
 *            - 0 success
 *            - 1 set proximity pulse length failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_pulse_length(apds9960_handle_t *handle, apds9960_proximity_pulse_length_t len)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PPULSE, (uint8_t *)&prev, 1);              /* get proximity pulse count register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("apds9960: get proximity pulse count register failed.\n");        /* get proximity pulse count register failed */
       
        return 1;                                                                             /* return error */
    }
    prev &= ~(3 << 6);                                                                        /* clear config */
    prev |= len << 6;                                                                         /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_PPULSE, (uint8_t *)&prev, 1);             /* set proximity pulse count register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("apds9960: set proximity pulse count register failed.\n");        /* set proximity pulse count register failed */
       
        return 1;                                                                             /* return error */
    }
    
    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief      get the proximity pulse length
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *len points to a proximity pulse length buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity pulse length failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_pulse_length(apds9960_handle_t *handle, apds9960_proximity_pulse_length_t *len)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PPULSE, (uint8_t *)&prev, 1);              /* get proximity pulse count register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("apds9960: get proximity pulse count register failed.\n");        /* get proximity pulse count register failed */
       
        return 1;                                                                             /* return error */
    }
    *len = (apds9960_proximity_pulse_length_t)((prev >> 6) & 0x3);                            /* get length */
    
    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief     set the proximity pulse count
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] count is the proximity pulse count
 * @return    status code
 *            - 0 success
 *            - 1 set proximity pulse count failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 count is over 63
 * @note      none
 */
uint8_t apds9960_set_proximity_pulse_count(apds9960_handle_t *handle, uint16_t count)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    if (count > 0x3F)                                                                         /* check count */
    {
        handle->debug_print("apds9960: count is over 63.\n");                                 /* count is over 63 */
       
        return 4;                                                                             /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PPULSE, (uint8_t *)&prev, 1);              /* get proximity pulse count register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("apds9960: get proximity pulse count register failed.\n");        /* get proximity pulse count register failed */
       
        return 1;                                                                             /* return error */
    }
    prev &= ~(0x3F << 0);                                                                     /* clear config */
    prev |= (count & 0x3F) << 0;                                                              /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_PPULSE, (uint8_t *)&prev, 1);             /* set proximity pulse count register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("apds9960: set proximity pulse count register failed.\n");        /* set proximity pulse count register failed */
       
        return 1;                                                                             /* return error */
    }
    
    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief      get the proximity pulse count
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *count points to a proximity pulse count buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity pulse count failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_get_proximity_pulse_count(apds9960_handle_t *handle, uint16_t *count)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PPULSE, (uint8_t *)&prev, 1);              /* get proximity pulse count register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("apds9960: get proximity pulse count register failed.\n");        /* get proximity pulse count register failed */
       
        return 1;                                                                             /* return error */
    }
    *count = prev & 0x3F;                                                                     /* get count */
    
    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief     set the led current
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] current is the led current
 * @return    status code
 *            - 0 success
 *            - 1 set led current failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_led_current(apds9960_handle_t *handle, apds9960_led_current_t current)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONTROL, (uint8_t *)&prev, 1);        /* get control register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get control register failed.\n");                 /* get control register failed */
       
        return 1;                                                                        /* return error */
    }
    prev &= ~(0x3 << 6);                                                                 /* clear config */
    prev |= current << 6;                                                                /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CONTROL, (uint8_t *)&prev, 1);       /* set control register register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: set control register register failed.\n");        /* set control register failed */
       
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief      get the led current
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *current points to a led current buffer
 * @return     status code
 *             - 0 success
 *             - 1 get led current failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_led_current(apds9960_handle_t *handle, apds9960_led_current_t *current)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONTROL, (uint8_t *)&prev, 1);        /* get control register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get control register failed.\n");                 /* get control register failed */
       
        return 1;                                                                        /* return error */
    }
    *current = (apds9960_led_current_t)((prev >> 6) & 0x3);                              /* get the current */
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     set the proximity gain
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] gain is the proximity gain
 * @return    status code
 *            - 0 success
 *            - 1 set proximity gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_gain(apds9960_handle_t *handle, apds9960_proximity_gain_t gain)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONTROL, (uint8_t *)&prev, 1);        /* get control register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get control register failed.\n");                 /* get control register failed */
       
        return 1;                                                                        /* return error */
    }
    prev &= ~(0x3 << 2);                                                                 /* clear config */
    prev |= gain << 2;                                                                   /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CONTROL, (uint8_t *)&prev, 1);       /* set control register register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: set control register register failed.\n");        /* set control register failed */
       
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief      get the proximity gain
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *gain points to a proximity gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_gain(apds9960_handle_t *handle, apds9960_proximity_gain_t *gain)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONTROL, (uint8_t *)&prev, 1);        /* get control register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get control register failed.\n");                 /* get control register failed */
       
        return 1;                                                                        /* return error */
    }
    *gain = (apds9960_proximity_gain_t)((prev >> 2) & 0x3);                              /* get the gain */
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     set the als color gain
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] gain is the als color gain
 * @return    status code
 *            - 0 success
 *            - 1 set als color gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_als_color_gain(apds9960_handle_t *handle, apds9960_als_color_gain_t gain)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONTROL, (uint8_t *)&prev, 1);        /* get control register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get control register failed.\n");                 /* get control register failed */
       
        return 1;                                                                        /* return error */
    }
    prev &= ~(0x3 << 0);                                                                 /* clear config */
    prev |= gain << 0;                                                                   /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CONTROL, (uint8_t *)&prev, 1);       /* set control register register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: set control register register failed.\n");        /* set control register failed */
       
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief      get the als color gain
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *gain points to an als color gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get als color gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_als_color_gain(apds9960_handle_t *handle, apds9960_als_color_gain_t *gain)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONTROL, (uint8_t *)&prev, 1);        /* get control register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get control register failed.\n");                 /* get control register failed */
       
        return 1;                                                                        /* return error */
    }
    *gain = (apds9960_als_color_gain_t)((prev >> 0) & 0x3);                              /* get the gain */
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     set the saturation interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] saturation is the saturation interrupt type
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set saturation interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_saturation_interrupt(apds9960_handle_t *handle, apds9960_saturation_interrupt_t saturation, apds9960_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG2, (uint8_t *)&prev, 1);          /* get control 2 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get control 2 register failed.\n");                 /* get control 2 register failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~(1 << saturation);                                                            /* clear config */
    prev |= enable << saturation;                                                          /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CONFIG2, (uint8_t *)&prev, 1);         /* set control register 2 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: set control 2 register register failed.\n");        /* set control 2 register failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the saturation interrupt
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  saturation is the saturation interrupt type
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get saturation interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_saturation_interrupt(apds9960_handle_t *handle, apds9960_saturation_interrupt_t saturation, apds9960_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG2, (uint8_t *)&prev, 1);          /* get control 2 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get control 2 register failed.\n");                 /* get control 2 register failed */
       
        return 1;                                                                          /* return error */
    }
    *enable = (apds9960_bool_t)((prev >> saturation) & 0x01);                              /* get the saturation */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     set the led boost
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] boost is the led boost
 * @return    status code
 *            - 0 success
 *            - 1 set led boost failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_led_boost(apds9960_handle_t *handle, apds9960_led_boost_t boost)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG2, (uint8_t *)&prev, 1);          /* get control 2 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get control 2 register failed.\n");                 /* get control 2 register failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~(0x3 << 4);                                                                   /* clear config */
    prev |= boost << 4;                                                                    /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CONFIG2, (uint8_t *)&prev, 1);         /* set control register 2 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: set control 2 register register failed.\n");        /* set control 2 register failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the led boost
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *boost points to a led boost buffer
 * @return     status code
 *             - 0 success
 *             - 1 get led boost failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_led_boost(apds9960_handle_t *handle, apds9960_led_boost_t *boost)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG2, (uint8_t *)&prev, 1);          /* get control 2 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get control 2 register failed.\n");                 /* get control 2 register failed */
       
        return 1;                                                                          /* return error */
    }
    *boost = (apds9960_led_boost_t)((prev >> 4) & 0x3);                                    /* set the LED boost */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_status(apds9960_handle_t *handle, uint8_t *status)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_STATUS, (uint8_t *)&prev, 1);       /* get status register */
    if (res != 0)                                                                      /* check result */
    {
        handle->debug_print("apds9960: get status register failed.\n");                /* get status register failed */
       
        return 1;                                                                      /* return error */
    }
    *status = prev;                                                                    /* set the status */
    
    return 0;                                                                          /* success return 0 */
}

/**
 * @brief      read the rgbc data
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *red points to a red buffer
 * @param[out] *green points to a green buffer
 * @param[out] *blue points to a blue buffer
 * @param[out] *clear points to a clear buffer
 * @return     status code
 *             - 0 success
 *             - 1 read rgbc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_read_rgbc(apds9960_handle_t *handle, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear)
{
    uint8_t res;
    uint8_t buf[8];
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CDATAL, (uint8_t *)&buf[0], 2);       /* get cdatal register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get cdatal register failed.\n");                  /* get cdatal register failed */
       
        return 1;                                                                        /* return error */
    }
    res = a_apds9960_iic_read(handle, APDS9960_REG_RDATAL, (uint8_t *)&buf[2], 2);       /* get rdatal register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get rdatal register failed.\n");                  /* get rdatal register failed */
       
        return 1;                                                                        /* return error */
    }
    res = a_apds9960_iic_read(handle, APDS9960_REG_GDATAL, (uint8_t *)&buf[4], 2);       /* get gdatal register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get gdatal register failed.\n");                  /* get gdatal register failed */
       
        return 1;                                                                        /* return error */
    }
    res = a_apds9960_iic_read(handle, APDS9960_REG_BDATAL, (uint8_t *)&buf[6], 2);       /* get bdatal register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get bdatal register failed.\n");                  /* get bdatal register failed */
       
        return 1;                                                                        /* return error */
    }
    *red = (uint16_t)(((uint16_t)buf[3] << 0) | buf[2]);                                 /* set the red */
    *green = (uint16_t)(((uint16_t)buf[5] << 0) | buf[4]);                               /* set the green */
    *blue = (uint16_t)(((uint16_t)buf[7] << 0) | buf[6]);                                /* set the blue */
    *clear = (uint16_t)(((uint16_t)buf[1] << 0) | buf[0]);                               /* set the clear */
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief      read the proximity data
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *proximity points to a proximity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read proximity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_read_proximity(apds9960_handle_t *handle, uint8_t *proximity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_PDATA, (uint8_t *)&prev, 1);        /* get proximity data register */
    if (res != 0)                                                                      /* check result */
    {
        handle->debug_print("apds9960: get proximity data register failed.\n");        /* get proximity data register failed */
       
        return 1;                                                                      /* return error */
    }
    *proximity = prev;                                                                 /* set the proximity */
    
    return 0;                                                                          /* success return 0 */
}

/**
 * @brief     set the proximity up right offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the proximity offset
 * @return    status code
 *            - 0 success
 *            - 1 set proximity up right offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_up_right_offset(apds9960_handle_t *handle, int8_t offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    if (offset >= 0)                                                                              /* if >= 0 */
    {
        prev = offset;                                                                            /* set the positive */
    }
    else                                                                                          /* < 0 */
    {
        prev = 0x80;                                                                              /* set the 0x80 */
        prev |= (-offset);                                                                        /* set the negative */
    }
    res = a_apds9960_iic_write(handle, APDS9960_REG_POFFSET_UR, (uint8_t *)&prev, 1);             /* set proximity offset up right register */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("apds9960: set proximity offset up right register failed.\n");        /* set proximity offset up right register failed */
       
        return 1;                                                                                 /* return error */
    }
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief      get the proximity up right offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a proximity offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity up right offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_up_right_offset(apds9960_handle_t *handle, int8_t *offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_POFFSET_UR, (uint8_t *)&prev, 1);             /* get proximity offset up right register */
    if (res != 0)                                                                                /* check result */
    {
        handle->debug_print("apds9960: get proximity offset up right register failed.\n");       /* get proximity offset up right register failed */
       
        return 1;                                                                                /* return error */
    }
    if ((prev & 0x80) != 0)                                                                      /* if < 0 */
    {
        prev &= ~0x80;                                                                           /* clear 0x80 */
        *offset = -(int8_t)(prev);                                                               /* set the offset */
    }
    else                                                                                         /* >= 0 */
    {
        *offset = (int8_t)(prev);                                                                /* set the offset */
    }
    
    return 0;                                                                                    /* success return 0 */
}

/**
 * @brief     set the proximity down left offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the proximity offset
 * @return    status code
 *            - 0 success
 *            - 1 set proximity down left offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_down_left_offset(apds9960_handle_t *handle, int8_t offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    if (offset >= 0)                                                                               /* if >= 0 */
    {
        prev = offset;                                                                             /* set the positive */
    }
    else                                                                                           /* <0 */
    {
        prev = 0x80;                                                                               /* set the 0x80 */
        prev |= (-offset);                                                                         /* set the negative */
    }
    res = a_apds9960_iic_write(handle, APDS9960_REG_POFFSET_DL, (uint8_t *)&prev, 1);              /* set proximity offset down left register */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("apds9960: set proximity offset down left register failed.\n");        /* set proximity offset down left register failed */
       
        return 1;                                                                                  /* return error */
    }
    
    return 0;                                                                                      /* success return 0 */
}

/**
 * @brief      get the proximity down left offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a proximity offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity down left offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_down_left_offset(apds9960_handle_t *handle, int8_t *offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_POFFSET_DL, (uint8_t *)&prev, 1);              /* get proximity offset down left register */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("apds9960: get proximity offset down left register failed.\n");       /* get proximity offset down left register failed */
       
        return 1;                                                                                 /* return error */
    }
    if ((prev & 0x80) != 0)                                                                       /* if < 0 */
    {
        prev &= ~0x80;                                                                            /* clear 0x80 */
        *offset = -(int8_t)(prev);                                                                /* set the offset */
    }
    else                                                                                          /* >= 0 */
    {
        *offset = (int8_t)(prev);                                                                 /* set the offset */
    }
    
    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     enable or disable the proximity gain compensation
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set proximity gain compensation failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_gain_compensation(apds9960_handle_t *handle, apds9960_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG3, (uint8_t *)&prev, 1);          /* get control 3 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get control 3 register failed.\n");                 /* get control 3 register failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~(1 << 5);                                                                     /* clear config */
    prev |= enable << 5;                                                                   /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CONFIG3, (uint8_t *)&prev, 1);         /* set control register 3 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: set control 3 register register failed.\n");        /* set control 3 register failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the proximity gain compensation status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity gain compensation failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_gain_compensation(apds9960_handle_t *handle, apds9960_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG3, (uint8_t *)&prev, 1);          /* get control 3 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get control 3 register failed.\n");                 /* get control 3 register failed */
       
        return 1;                                                                          /* return error */
    }
    *enable = (apds9960_bool_t)((prev >> 5) & 0x01);                                       /* get bool */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     enable or disable sleeping after interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sleep after interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_sleep_after_interrupt(apds9960_handle_t *handle, apds9960_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG3, (uint8_t *)&prev, 1);          /* get control 3 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get control 3 register failed.\n");                 /* get control 3 register failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~(1 << 4);                                                                     /* clear config */
    prev |= enable << 4;                                                                   /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CONFIG3, (uint8_t *)&prev, 1);         /* set control register 3 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: set control 3 register register failed.\n");        /* set control 3 register failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the sleeping after interrupt status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sleep after interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_sleep_after_interrupt(apds9960_handle_t *handle, apds9960_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG3, (uint8_t *)&prev, 1);          /* get control 3 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get control 3 register failed.\n");                 /* get control 3 register failed */
       
        return 1;                                                                          /* return error */
    }
    *enable = (apds9960_bool_t)((prev >> 4) & 0x01);                                       /* get bool */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     enable or disable the proximity mask
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] mask is the proximity mask
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set proximity mask failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_proximity_mask(apds9960_handle_t *handle, apds9960_proximity_mask_t mask, apds9960_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG3, (uint8_t *)&prev, 1);          /* get control 3 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get control 3 register failed.\n");                 /* get control 3 register failed */
       
        return 1;                                                                          /* return error */
    }
    prev &= ~(1 << mask);                                                                  /* clear config */
    prev |= enable << mask;                                                                /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CONFIG3, (uint8_t *)&prev, 1);         /* set control register 3 register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: set control 3 register register failed.\n");        /* set control 3 register failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the proximity mask status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  mask is the proximity mask
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get proximity mask failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_proximity_mask(apds9960_handle_t *handle, apds9960_proximity_mask_t mask, apds9960_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_CONFIG3, (uint8_t *)&prev, 1);       /* get control 3 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: get control 3 register failed.\n");              /* get control 3 register failed */
       
        return 1;                                                                       /* return error */
    }
    *enable = (apds9960_bool_t)((prev >> mask) & 0x01);                                 /* get bool */
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief     set the gesture proximity enter threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the gesture proximity enter threshold
 * @return    status code
 *            - 0 success
 *            - 1 set gesture proximity enter threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_proximity_enter_threshold(apds9960_handle_t *handle, uint8_t threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                                   /* check handle */
    {
        return 2;                                                                                         /* return error */
    }
    if (handle->inited != 1)                                                                              /* check handle initialization */
    {
        return 3;                                                                                         /* return error */
    }
    
    prev = threshold;                                                                                     /* set threshold */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GPENTH, (uint8_t *)&prev, 1);                         /* set gesture proximity enter threshold register */
    if (res != 0)                                                                                         /* check result */
    {
        handle->debug_print("apds9960: set gesture proximity enter threshold register failed.\n");        /* set gesture proximity enter threshold register failed */
       
        return 1;                                                                                         /* return error */
    }
    
    return 0;                                                                                             /* success return 0 */
}

/**
 * @brief      get the gesture proximity enter threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a gesture proximity enter threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture proximity enter threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_proximity_enter_threshold(apds9960_handle_t *handle, uint8_t *threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                                   /* check handle */
    {
        return 2;                                                                                         /* return error */
    }
    if (handle->inited != 1)                                                                              /* check handle initialization */
    {
        return 3;                                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GPENTH, (uint8_t *)&prev, 1);                          /* get gesture proximity enter threshold register */
    if (res != 0)                                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture proximity enter threshold register failed.\n");        /* get gesture proximity enter threshold register failed */
       
        return 1;                                                                                         /* return error */
    }
    *threshold = prev;                                                                                    /* set threshold */
    
    return 0;                                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture proximity exit threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the gesture proximity exit threshold
 * @return    status code
 *            - 0 success
 *            - 1 set gesture proximity exit threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_proximity_exit_threshold(apds9960_handle_t *handle, uint8_t threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                                  /* check handle */
    {
        return 2;                                                                                        /* return error */
    }
    if (handle->inited != 1)                                                                             /* check handle initialization */
    {
        return 3;                                                                                        /* return error */
    }
    
    prev = threshold;                                                                                    /* set threshold */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GEXTH, (uint8_t *)&prev, 1);                         /* set gesture proximity exit threshold register */
    if (res != 0)                                                                                        /* check result */
    {
        handle->debug_print("apds9960: set gesture proximity exit threshold register failed.\n");        /* set gesture proximity exit threshold register failed */
       
        return 1;                                                                                        /* return error */
    }
    
    return 0;                                                                                            /* success return 0 */
}

/**
 * @brief      get the gesture proximity exit threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a gesture proximity exit threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture proximity exit threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_proximity_exit_threshold(apds9960_handle_t *handle, uint8_t *threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                                  /* check handle */
    {
        return 2;                                                                                        /* return error */
    }
    if (handle->inited != 1)                                                                             /* check handle initialization */
    {
        return 3;                                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GEXTH, (uint8_t *)&prev, 1);                          /* get gesture proximity exit threshold register */
    if (res != 0)                                                                                        /* check result */
    {
        handle->debug_print("apds9960: get gesture proximity exit threshold register failed.\n");        /* get gesture proximity exit threshold register failed */
       
        return 1;                                                                                        /* return error */
    }
    *threshold = prev;                                                                                   /* set the threshold */
    
    return 0;                                                                                            /* success return 0 */
}

/**
 * @brief     set the gesture fifo threshold
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] threshold is the gesture fifo threshold
 * @return    status code
 *            - 0 success
 *            - 1 set gesture fifo threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_fifo_threshold(apds9960_handle_t *handle, apds9960_gesture_fifo_threshold_t threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF1, (uint8_t *)&prev, 1);          /* get gesture control 1 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 1 register failed.\n");        /* get gesture control 1 register failed */
       
        return 1;                                                                         /* return error */
    }
    prev &= ~(3 << 6);                                                                    /* clear config */
    prev |= threshold << 6;                                                               /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF1, (uint8_t *)&prev, 1);         /* set gesture control 1 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: set gesture control 1 register failed.\n");        /* set gesture control 1 register failed */
       
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief      get the gesture fifo threshold
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *threshold points to a gesture fifo threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture fifo threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_fifo_threshold(apds9960_handle_t *handle, apds9960_gesture_fifo_threshold_t *threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF1, (uint8_t *)&prev, 1);          /* get gesture control 1 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 1 register failed.\n");        /* get gesture control 1 register failed */
       
        return 1;                                                                         /* return error */
    }
    *threshold = (apds9960_gesture_fifo_threshold_t)((prev >> 6) & 0x3);                  /* set the threshold */
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture exit persistence
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] persistence is the gesture exit persistence
 * @return    status code
 *            - 0 success
 *            - 1 set gesture exit persistence failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_exit_persistence(apds9960_handle_t *handle, apds9960_gesture_exit_persistence_t persistence)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF1, (uint8_t *)&prev, 1);          /* get gesture control 1 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 1 register failed.\n");        /* get gesture control 1 register failed */
       
        return 1;                                                                         /* return error */
    }
    prev &= ~(3 << 0);                                                                    /* clear config */
    prev |= persistence << 0;                                                             /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF1, (uint8_t *)&prev, 1);         /* set gesture control 1 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: set gesture control 1 register failed.\n");        /* set gesture control 1 register failed */
       
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief      get the gesture exit persistence
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *persistence points to a gesture exit persistence buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture exit persistence failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_exit_persistence(apds9960_handle_t *handle, apds9960_gesture_exit_persistence_t *persistence)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF1, (uint8_t *)&prev, 1);          /* get gesture control 1 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 1 register failed.\n");        /* get gesture control 1 register failed */
       
        return 1;                                                                         /* return error */
    }
    *persistence = (apds9960_gesture_exit_persistence_t)((prev >> 0) & 0x3);              /* set the persistence */
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture exit mask
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] mask is the exit mask
 * @return    status code
 *            - 0 success
 *            - 1 set gesture exit mask failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 mask is over 0xF
 * @note      none
 */
uint8_t apds9960_set_gesture_exit_mask(apds9960_handle_t *handle, uint8_t mask)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    if (mask > 0xF)                                                                       /* check result */
    {
        handle->debug_print("apds9960: mask is over 0xF.\n");                             /* mask is over 0xF */
       
        return 4;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF1, (uint8_t *)&prev, 1);          /* get gesture control 1 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 1 register failed.\n");        /* get gesture control 1 register failed */
       
        return 1;                                                                         /* return error */
    }
    prev &= ~(0xF << 2);                                                                  /* clear config */
    prev |= (mask & 0xF) << 2;                                                            /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF1, (uint8_t *)&prev, 1);         /* set gesture control 1 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: set gesture control 1 register failed.\n");        /* set gesture control 1 register failed */
       
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief      get the gesture exit mask
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *mask points to an exit mask buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture exit mask failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_exit_mask(apds9960_handle_t *handle, uint8_t *mask)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF1, (uint8_t *)&prev, 1);          /* get gesture control 1 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 1 register failed.\n");        /* get gesture control 1 register failed */
       
        return 1;                                                                         /* return error */
    }
    *mask = (prev >> 2) & 0xF;                                                            /* set the mask */
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture gain
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] gain is the gesture gain
 * @return    status code
 *            - 0 success
 *            - 1 set gesture gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_gain(apds9960_handle_t *handle, apds9960_gesture_gain_control_t gain)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF2, (uint8_t *)&prev, 1);          /* get gesture control 2 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 2 register failed.\n");        /* get gesture control 2 register failed */
       
        return 1;                                                                         /* return error */
    }
    prev &= ~(0x3 << 5);                                                                  /* clear config */
    prev |= gain << 5;                                                                    /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF2, (uint8_t *)&prev, 1);         /* set gesture control 2 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: set gesture control 2 register failed.\n");        /* set gesture control 2 register failed */
       
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief      get the gesture gain
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *gain points to a gesture gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_gain(apds9960_handle_t *handle, apds9960_gesture_gain_control_t *gain)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF2, (uint8_t *)&prev, 1);          /* get gesture control 2 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 2 register failed.\n");        /* get gesture control 2 register failed */
       
        return 1;                                                                         /* return error */
    }
    *gain = (apds9960_gesture_gain_control_t)((prev >> 5) & 0x3);                         /* set the gain */
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture led current
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] current is the gesture led current
 * @return    status code
 *            - 0 success
 *            - 1 set gesture led current failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_led_current(apds9960_handle_t *handle, apds9960_gesture_led_current_t current)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF2, (uint8_t *)&prev, 1);          /* get gesture control 2 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 2 register failed.\n");        /* get gesture control 2 register failed */
       
        return 1;                                                                         /* return error */
    }
    prev &= ~(0x3 << 3);                                                                  /* clear config */
    prev |= current << 3;                                                                 /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF2, (uint8_t *)&prev, 1);         /* set gesture control 2 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: set gesture control 2 register failed.\n");        /* set gesture control 2 register failed */
       
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief      get the gesture led current
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *current points to a gesture led current buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture led current failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_led_current(apds9960_handle_t *handle, apds9960_gesture_led_current_t *current)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF2, (uint8_t *)&prev, 1);          /* get gesture control 2 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 2 register failed.\n");        /* get gesture control 2 register failed */
       
        return 1;                                                                         /* return error */
    }
    *current = (apds9960_gesture_led_current_t)((prev >> 3) & 0x3);                       /* set the current */
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture wait time
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] t is the gesture wait time
 * @return    status code
 *            - 0 success
 *            - 1 set gesture wait time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_wait_time(apds9960_handle_t *handle, apds9960_gesture_wait_time_t t)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF2, (uint8_t *)&prev, 1);          /* get gesture control 2 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 2 register failed.\n");        /* get gesture control 2 register failed */
       
        return 1;                                                                         /* return error */
    }
    prev &= ~(0x7 << 0);                                                                  /* clear config */
    prev |= t << 0;                                                                       /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF2, (uint8_t *)&prev, 1);         /* set gesture control 2 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: set gesture control 2 register failed.\n");        /* set gesture control 2 register failed */
       
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief      get the gesture wait time
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *t points to a gesture wait time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture wait time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_wait_time(apds9960_handle_t *handle, apds9960_gesture_wait_time_t *t)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF2, (uint8_t *)&prev, 1);          /* get gesture control 2 register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture control 2 register failed.\n");        /* get gesture control 2 register failed */
       
        return 1;                                                                         /* return error */
    }
    *t = (apds9960_gesture_wait_time_t)((prev >> 0) & 0x7);                               /* set the wait time */
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture up offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the gesture up offset
 * @return    status code
 *            - 0 success
 *            - 1 set gesture up offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_up_offset(apds9960_handle_t *handle, int8_t offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    if (offset >= 0)                                                                       /* if >= 0 */
    {
        prev = offset;                                                                     /* set the positive */
    }
    else                                                                                   /* <0 */
    {
        prev = 0x80;                                                                       /* set the 0x80 */
        prev |= (-offset);                                                                 /* set the negative */
    }
    res = a_apds9960_iic_write(handle, APDS9960_REG_GOFFSET_U, (uint8_t *)&prev, 1);       /* set gesture up offset register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: set gesture up offset register failed.\n");         /* set gesture up offset register failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the gesture up offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a gesture up offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture up offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_up_offset(apds9960_handle_t *handle, int8_t *offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GOFFSET_U, (uint8_t *)&prev, 1);       /* get gesture up offset register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture up offset register failed.\n");        /* get gesture up offset register failed */
       
        return 1;                                                                         /* return error */
    }
    if ((prev & 0x80) != 0)                                                               /* if < 0 */
    {
        prev &= ~0x80;                                                                    /* clear 0x80 */
        *offset = -(int8_t)(prev);                                                        /* set the offset */
    }
    else                                                                                  /* >= 0 */
    {
        *offset = (int8_t)(prev);                                                         /* set the offset */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture down offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the gesture down offset
 * @return    status code
 *            - 0 success
 *            - 1 set gesture down offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_down_offset(apds9960_handle_t *handle, int8_t offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    if (offset >= 0)                                                                       /* if >= 0 */
    {
        prev = offset;                                                                     /* set the positive */
    }
    else                                                                                   /* <0 */
    {
        prev = 0x80;                                                                       /* set the 0x80 */
        prev |= (-offset);                                                                 /* set the negative */
    }
    res = a_apds9960_iic_write(handle, APDS9960_REG_GOFFSET_D, (uint8_t *)&prev, 1);       /* set gesture down offset register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: set gesture down offset register failed.\n");       /* set gesture down offset register failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the gesture down offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a gesture down offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture down offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_down_offset(apds9960_handle_t *handle, int8_t *offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GOFFSET_D, (uint8_t *)&prev, 1);       /* get gesture down offset register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture down offset register failed.\n");      /* get gesture down offset register failed */
       
        return 1;                                                                         /* return error */
    }
    if ((prev & 0x80) != 0)                                                               /* if < 0 */
    {
        prev &= ~0x80;                                                                    /* clear 0x80 */
        *offset = -(int8_t)(prev);                                                        /* set the offset */
    }
    else                                                                                  /* >= 0 */
    {
        *offset = (int8_t)(prev);                                                         /* set the offset */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture left offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the gesture left offset
 * @return    status code
 *            - 0 success
 *            - 1 set gesture left offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_left_offset(apds9960_handle_t *handle, int8_t offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    if (offset >= 0)                                                                       /* if >= 0 */
    {
        prev = offset;                                                                     /* set the positive */
    }
    else                                                                                   /* <0 */
    {
        prev = 0x80;                                                                       /* set the 0x80 */
        prev |= (-offset);                                                                 /* set the negative */
    }
    res = a_apds9960_iic_write(handle, APDS9960_REG_GOFFSET_L, (uint8_t *)&prev, 1);       /* set gesture left offset register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: set gesture left offset register failed.\n");       /* set gesture left offset register failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the gesture left offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a gesture left offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture left offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_left_offset(apds9960_handle_t *handle, int8_t *offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GOFFSET_L, (uint8_t *)&prev, 1);       /* get gesture left offset register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture left offset register failed.\n");      /* get gesture left offset register failed */
       
        return 1;                                                                         /* return error */
    }
    if ((prev & 0x80) != 0)                                                               /* if < 0 */
    {
        prev &= ~0x80;                                                                    /* clear 0x80 */
        *offset = -(int8_t)(prev);                                                        /* set the offset */
    }
    else                                                                                  /* >= 0 */
    {
        *offset = (int8_t)(prev);                                                         /* set the offset */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture right offset
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] offset is the gesture right offset
 * @return    status code
 *            - 0 success
 *            - 1 set gesture right offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_right_offset(apds9960_handle_t *handle, int8_t offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    if (offset >= 0)                                                                       /* if >= 0 */
    {
        prev = offset;                                                                     /* set the positive */
    }
    else                                                                                   /* <0 */
    {
        prev = 0x80;                                                                       /* set the 0x80 */
        prev |= (-offset);                                                                 /* set the negative */
    }
    res = a_apds9960_iic_write(handle, APDS9960_REG_GOFFSET_R, (uint8_t *)&prev, 1);       /* set gesture right offset register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: set gesture right offset register failed.\n");      /* set gesture right offset register failed */
       
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the gesture right offset
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *offset points to a gesture right offset buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture right offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_right_offset(apds9960_handle_t *handle, int8_t *offset)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GOFFSET_R, (uint8_t *)&prev, 1);       /* get gesture right offset register */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("apds9960: get gesture right offset register failed.\n");     /* get gesture right offset register failed */
       
        return 1;                                                                         /* return error */
    }
    if ((prev & 0x80) != 0)                                                               /* if < 0 */
    {
        prev &= ~0x80;                                                                    /* clear 0x80 */
        *offset = -(int8_t)(prev);                                                        /* set the offset */
    }
    else                                                                                  /* >= 0 */
    {
        *offset = (int8_t)(prev);                                                         /* set the offset */
    }
    
    return 0;                                                                             /* success return 0 */
}

/**
 * @brief     set the gesture pulse length
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] len is the gesture pulse length
 * @return    status code
 *            - 0 success
 *            - 1 set gesture pulse length failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_pulse_length(apds9960_handle_t *handle, apds9960_gesture_pulse_length_t len)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GPULSE, (uint8_t *)&prev, 1);              /* get gesture pulse count register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("apds9960: get gesture pulse count register failed.\n");          /* get gesture pulse count register failed */
       
        return 1;                                                                             /* return error */
    }
    prev &= ~(3 << 6);                                                                        /* clear config */
    prev |= len << 6;                                                                         /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GPULSE, (uint8_t *)&prev, 1);             /* set gesture pulse count register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("apds9960: set gesture pulse count register failed.\n");          /* set gesture pulse count register failed */
       
        return 1;                                                                             /* return error */
    }
    
    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief      get the gesture pulse length
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *len points to a gesture pulse length buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture pulse length failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_pulse_length(apds9960_handle_t *handle, apds9960_gesture_pulse_length_t *len)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GPULSE, (uint8_t *)&prev, 1);            /* get gesture pulse count register */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("apds9960: get gesture pulse count register failed.\n");        /* get gesture pulse count register failed */
       
        return 1;                                                                           /* return error */
    }
    *len = (apds9960_gesture_pulse_length_t)((prev >> 6) & 0x3);                            /* get length */
    
    return 0;                                                                               /* success return 0 */
}

/**
 * @brief     set the gesture pulse count
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] count is the gesture pulse count
 * @return    status code
 *            - 0 success
 *            - 1 set gesture pulse count failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 count is over 63
 * @note      none
 */
uint8_t apds9960_set_gesture_pulse_count(apds9960_handle_t *handle, uint16_t count)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    if (count > 0x3F)                                                                       /* check count */
    {
        handle->debug_print("apds9960: count is over 63.\n");                               /* count is over 63 */
       
        return 4;                                                                           /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GPULSE, (uint8_t *)&prev, 1);            /* get gesture pulse count register */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("apds9960: get gesture pulse count register failed.\n");        /* get gesture pulse count register failed */
       
        return 1;                                                                           /* return error */
    }
    prev &= ~(0x3F << 0);                                                                   /* clear config */
    prev |= (count & 0x3F) << 0;                                                            /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GPULSE, (uint8_t *)&prev, 1);           /* set gesture pulse count register */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("apds9960: set gesture pulse count register failed.\n");        /* set gesture pulse count register failed */
       
        return 1;                                                                           /* return error */
    }
    
    return 0;                                                                               /* success return 0 */
}

/**
 * @brief      get the gesture pulse count
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *count points to a gesture pulse count buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture pulse count failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_pulse_count(apds9960_handle_t *handle, uint16_t *count)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GPULSE, (uint8_t *)&prev, 1);            /* get gesture pulse count register */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("apds9960: get gesture pulse count register failed.\n");        /* get gesture pulse count register failed */
       
        return 1;                                                                           /* return error */
    }
    *count = prev & 0x3F;                                                                   /* get count */
    
    return 0;                                                                               /* success return 0 */
}

/**
 * @brief     set the gesture dimension
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] s is the gesture dimension
 * @return    status code
 *            - 0 success
 *            - 1 set gesture dimension failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_dimension(apds9960_handle_t *handle, apds9960_gesture_dimension_select_t s)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF3, (uint8_t *)&prev, 1);        /* get gesture conf 3 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: get gesture conf 3 register failed.\n");         /* get gesture conf 3 register failed */
       
        return 1;                                                                       /* return error */
    }
    prev &= ~(3 << 0);                                                                  /* clear config */
    prev |= s << 0;                                                                     /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF3, (uint8_t *)&prev, 1);       /* set gesture conf 3 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: set gesture conf 3 register failed.\n");         /* set gesture conf 3 register failed */
       
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief      get the gesture dimension
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *s points to a gesture dimension buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture dimension failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_dimension_select(apds9960_handle_t *handle, apds9960_gesture_dimension_select_t *s)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF3, (uint8_t *)&prev, 1);        /* get gesture conf 3 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: get gesture conf 3 register failed.\n");         /* get gesture conf 3 register failed */
       
        return 1;                                                                       /* return error */
    }
    *s = (apds9960_gesture_dimension_select_t)(prev & 0x3);                             /* get the select */
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief     clear the gesture fifo status
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 gesture fifo clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_gesture_fifo_clear(apds9960_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);        /* get gesture conf 4 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: get gesture conf 4 register failed.\n");         /* get gesture conf 4 register failed */
       
        return 1;                                                                       /* return error */
    }
    prev &= ~(1 << 2);                                                                  /* clear config */
    prev |= 1 << 2;                                                                     /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);       /* set gesture conf 4 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: set gesture conf 4 register failed.\n");         /* set gesture conf 4 register failed */
       
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief     enable or disable the gesture interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set gesture interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_interrupt(apds9960_handle_t *handle, apds9960_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);        /* get gesture conf 4 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: get gesture conf 4 register failed.\n");         /* get gesture conf 4 register failed */
       
        return 1;                                                                       /* return error */
    }
    prev &= ~(1 << 1);                                                                  /* clear config */
    prev |= enable << 1;                                                                /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);       /* set gesture conf 4 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: set gesture conf 4 register failed.\n");         /* set gesture conf 4 register failed */
       
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief      get the gesture interrupt status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_interrupt(apds9960_handle_t *handle, apds9960_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);        /* get gesture conf 4 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: get gesture conf 4 register failed.\n");         /* get gesture conf 4 register failed */
       
        return 1;                                                                       /* return error */
    }
    *enable = (apds9960_bool_t)((prev >> 1) & 0x1);                                     /* set bool */
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief     enable or disable the gesture mode
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set gesture mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_gesture_mode(apds9960_handle_t *handle, apds9960_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);        /* get gesture conf 4 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: get gesture conf 4 register failed.\n");         /* get gesture conf 4 register failed */
       
        return 1;                                                                       /* return error */
    }
    prev &= ~(1 << 0);                                                                  /* clear config */
    prev |= enable << 0;                                                                /* set config */
    res = a_apds9960_iic_write(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);       /* set gesture conf 4 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: set gesture conf 4 register failed.\n");         /* set gesture conf 4 register failed */
       
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief      get the gesture mode status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_mode(apds9960_handle_t *handle, apds9960_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GCONF4, (uint8_t *)&prev, 1);        /* get gesture conf 4 register */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: get gesture conf 4 register failed.\n");         /* get gesture conf 4 register failed */
       
        return 1;                                                                       /* return error */
    }
    *enable = (apds9960_bool_t)((prev >> 0) & 0x1);                                     /* set bool */
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief      get the gesture fifo level
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *level points to a gesture fifo level buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture fifo level failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_fifo_level(apds9960_handle_t *handle, uint8_t *level)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GFLVL, (uint8_t *)&prev, 1);            /* get gesture fifo level register */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("apds9960: get gesture fifo level register failed.\n");        /* get gesture fifo level register failed */
       
        return 1;                                                                          /* return error */
    }
    *level = prev;                                                                         /* set fifo level */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief      get the gesture status
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gesture status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_gesture_status(apds9960_handle_t *handle, uint8_t *status)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GSTATUS, (uint8_t *)&prev, 1);        /* get gesture status register */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: get gesture status register failed.\n");          /* get gesture status register failed */
       
        return 1;                                                                        /* return error */
    }
    *status = prev;                                                                      /* set status */
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     force an interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 force interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_force_interrupt(apds9960_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    prev = 0xFF;                                                                        /* set 0xFF */
    res = a_apds9960_iic_write(handle, APDS9960_REG_IFORCE, (uint8_t *)&prev, 1);       /* forces an interrupt */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("apds9960: forces an interrupt failed.\n");                 /* forces an interrupt failed */
       
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

/**
 * @brief     clear the proximity interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 proximity interrupt clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_proximity_interrupt_clear(apds9960_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    prev = 0xFF;                                                                         /* set 0xFF */
    res = a_apds9960_iic_write(handle, APDS9960_REG_PICLEAR, (uint8_t *)&prev, 1);       /* proximity interrupt clear */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: proximity interrupt clear failed.\n");            /* proximity interrupt clear failed */
       
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     clear the als interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 als interrupt clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_als_interrupt_clear(apds9960_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    prev = 0xFF;                                                                         /* set 0xFF */
    res = a_apds9960_iic_write(handle, APDS9960_REG_CICLEAR, (uint8_t *)&prev, 1);       /* als interrupt clear */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("apds9960: als interrupt clear failed.\n");                  /* als interrupt clear failed */
       
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     clear the all not gesture interrupt
 * @param[in] *handle points to an apds9960 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 all non gesture interrupt clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_all_non_gesture_interrupt_clear(apds9960_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    prev = 0xFF;                                                                             /* set 0xFF */
    res = a_apds9960_iic_write(handle, APDS9960_REG_AICLEAR, (uint8_t *)&prev, 1);           /* clear all non-gesture interrupts */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("apds9960: clear all non-gesture interrupts failed.\n");         /* clear all non-gesture interrupts failed */
       
        return 1;                                                                            /* return error */
    }
    
    return 0;                                                                                /* success return 0 */
}

/**
 * @brief         read data from the gesture fifo
 * @param[in]     *handle points to an apds9960 handle structure
 * @param[out]    **data points to a data buffer
 * @param[in,out] *len points to a data length buffer
 * @return        status code
 *                - 0 success
 *                - 1 read gesture fifo failed
 *                - 2 handle is NULL
 *                - 3 handle is not initialized
 * @note          none
 */
uint8_t apds9960_read_gesture_fifo(apds9960_handle_t *handle, uint8_t (*data)[4], uint8_t *len)
{
    uint8_t res;
    uint8_t level;
    
    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }
    
    res = a_apds9960_iic_read(handle, APDS9960_REG_GFLVL, (uint8_t *)&level, 1);                /* get gesture fifo level register */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("apds9960: get gesture fifo level register failed.\n");             /* get gesture fifo level register failed */
       
        return 1;                                                                               /* return error */
    }
    
    *len = level < (*len) ? level : (*len);
    res = a_apds9960_iic_read(handle, APDS9960_REG_GFIFO_U, (uint8_t *)data, (*len) * 4);       /* read gesture fifo */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("apds9960: read gesture fifo failed.\n");                           /* read gesture fifo failed */
       
        return 1;                                                                               /* return error */
    }
    
    return 0;                                                                                   /* success return 0 */
}

/**
 * @brief     set the chip register
 * @param[in] *handle points to an apds9960 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apds9960_set_reg(apds9960_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                    /* check handle */
    {
        return 2;                                          /* return error */
    }
    if (handle->inited != 1)                               /* check handle initialization */
    {
        return 3;                                          /* return error */
    }
    
    if (a_apds9960_iic_write(handle, reg, buf, len) != 0)  /* write data */
    {
        return 1;                                          /* return error */
    }
    else
    {
        return 0;                                          /* success return 0 */
    }
}

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an apds9960 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apds9960_get_reg(apds9960_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                   /* check handle */
    {
        return 2;                                         /* return error */
    }
    if (handle->inited != 1)                              /* check handle initialization */
    {
        return 3;                                         /* return error */
    }
    
    if (a_apds9960_iic_read(handle, reg, buf, len) != 0)  /* read data */
    {
        return 1;                                         /* return error */
    }
    else
    {
        return 0;                                         /* success return 0 */
    }
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an apds9960 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t apds9960_info(apds9960_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(apds9960_info_t));                       /* initialize apds9960 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
