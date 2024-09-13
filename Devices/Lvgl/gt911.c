#include "gt911.h"
#include "touch.h"
#include "main.h"
#include "ltdc.h"
#include <string.h>

/* GT911 5个触摸点(最多) 对应的寄存器表 */
const uint16_t GT911_TPX_TBL[5] =
{
    GT911_TP1_REG, GT911_TP2_REG, GT911_TP3_REG, GT911_TP4_REG, GT911_TP5_REG,
};

static void gt911_iic_delay(void)
{
		uint8_t i = 2;
	
		while(i--);
}

static void gt911_iic_start(void)
{
	  GT911_IIC_SDA(1);
		GT911_IIC_SCL(1);
		gt911_iic_delay();
		GT911_IIC_SDA(0);
		gt911_iic_delay();
		GT911_IIC_SCL(0);
		gt911_iic_delay();
}

static void gt911_iic_stop(void)
{
		GT911_IIC_SDA(0);
		gt911_iic_delay();
		GT911_IIC_SCL(1);
		gt911_iic_delay();
		GT911_IIC_SDA(1);
		gt911_iic_delay();
}

static uint8_t gt911_iic_wait_ack(void)
{
		uint8_t waittime = 0;
		uint8_t rack = 0;
    
    GT911_IIC_SDA(1);      /* 主机释放SDA线(此时外部器件可以拉低SDA线) */
    gt911_iic_delay();
    GT911_IIC_SCL(1);      /* SCL=1, 此时从机可以返回ACK */
    gt911_iic_delay();

    while (GT911_READ_SDA) /* 等待应答 */
    {
        waittime++;

        if (waittime > 250)
        {
            gt911_iic_stop();
            rack = 1;
            break;
        }

        gt911_iic_delay();
    }

    GT911_IIC_SCL(0);      /* SCL=0, 结束ACK检查 */
    gt911_iic_delay();

    return rack;
}

/**
 * @brief       产生ACK应答
 * @param       无
 * @retval      无
 */
static void gt911_iic_ack(void)
{
    GT911_IIC_SDA(0);      /* SCL 0 -> 1  时SDA = 0,表示应答 */
    gt911_iic_delay();
    GT911_IIC_SCL(1);
    gt911_iic_delay();
    GT911_IIC_SCL(0);
    gt911_iic_delay();
    GT911_IIC_SDA(1);      /* 主机释放SDA线 */
    gt911_iic_delay();
}

/**
 * @brief       不产生ACK应答
 * @param       无
 * @retval      无
 */
static void gt911_iic_nack(void)
{
    GT911_IIC_SDA(1);      /* SCL 0 -> 1  时 SDA = 1,表示不应答 */
    gt911_iic_delay();
    GT911_IIC_SCL(1);
    gt911_iic_delay();
    GT911_IIC_SCL(0);
    gt911_iic_delay();
}

/**
 * @brief       IIC发送一个字节
 * @param       data: 要发送的数据
 * @retval      无
 */
static void gt911_iic_send_byte(uint8_t data)
{
    uint8_t t;

    for (t = 0; t < 8; t++)
    {
        GT911_IIC_SDA((data & 0x80) >> 7); /* 高位先发送 */
        gt911_iic_delay();
        GT911_IIC_SCL(1);
        gt911_iic_delay();
        GT911_IIC_SCL(0);
        data <<= 1;                     /* 左移1位,用于下一次发送 */
    }

    GT911_IIC_SDA(1);                      /* 发送完成, 主机释放SDA线 */
}

/**
 * @brief       IIC发送一个字节
 * @param       ack:  ack=1时，发送ack; ack=0时，发送nack
 * @retval      接收到的数据
 */
static uint8_t gt911_iic_read_byte(unsigned char ack)
{
    uint8_t i, receive = 0;

    for (i = 0; i < 8; i++ )            /* 接收1个字节数据 */
    {
        receive <<= 1;                  /* 高位先输出,所以先收到的数据位要左移 */
        GT911_IIC_SCL(1);
        gt911_iic_delay();

        if (GT911_READ_SDA)
        {
            receive++;
        }

        GT911_IIC_SCL(0);
        gt911_iic_delay();
    }

    if (!ack)
    {
        gt911_iic_nack();                   /* 发送nACK */
    }
    else
    {
        gt911_iic_ack();                    /* 发送ACK */
    }

    return receive;
}

/************************************************************************************************************
*
*
*
*************************************************************************************************************/
uint8_t g_gt_tnum = 5;

/**
 * @brief       向gt911写入一次数据
 * @param       reg : 起始寄存器地址
 * @param       buf : 数据缓缓存区
 * @param       len : 写数据长度
 * @retval      0, 成功; 1, 失败;
 */
static uint8_t gt911_wr_reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    uint8_t ret = 0;
    gt911_iic_start();
    gt911_iic_send_byte(GT911_CMD_WR);    /* 发送写命令 */
    gt911_iic_wait_ack();
    gt911_iic_send_byte(reg >> 8);         /* 发送高8位地址 */
    gt911_iic_wait_ack();
    gt911_iic_send_byte(reg & 0XFF);       /* 发送低8位地址 */
    gt911_iic_wait_ack();

    for (i = 0; i < len; i++)
    {
        gt911_iic_send_byte(buf[i]);       /* 发数据 */
        ret = gt911_iic_wait_ack();

        if (ret)break;
    }

    gt911_iic_stop();                      /* 产生一个停止条件 */
    return ret;
}

/**
 * @brief       从gt9xxx读出一次数据
 * @param       reg : 起始寄存器地址
 * @param       buf : 数据缓缓存区
 * @param       len : 读数据长度
 * @retval      无
 */
static void gt911_rd_reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    gt911_iic_start();
    gt911_iic_send_byte(GT911_CMD_WR);                        /* 发送写命令 */
    gt911_iic_wait_ack();
    gt911_iic_send_byte(reg >> 8);                             /* 发送高8位地址 */
    gt911_iic_wait_ack();
    gt911_iic_send_byte(reg & 0XFF);                           /* 发送低8位地址 */
    gt911_iic_wait_ack();
    gt911_iic_start();
    gt911_iic_send_byte(GT911_CMD_RD);                        /* 发送读命令 */
    gt911_iic_wait_ack();

    for (i = 0; i < len; i++)
    {
        buf[i] = gt911_iic_read_byte(i == (len - 1) ? 0 : 1);  /* 发数据 */
    }

    gt911_iic_stop();                                          /* 产生一个停止条件 */
}

/**
 * @brief       初始化gt9xxx触摸屏
 * @param       无
 * @retval      0, 初始化成功; 1, 初始化失败;
 */
uint8_t gt911_init(void)
{
    uint8_t temp[5];

    GT911_IIC_SDA(1);
    GT911_IIC_SCL(1);                                           /* 初始化电容屏的I2C总线 */
    GT911_RST(0);                                               /* 复位 */
    HAL_Delay(10);
    GT911_RST(1);                                              /* 释放复位 */

    HAL_Delay(100);
    gt911_rd_reg(GT911_PID_REG, temp, 4);                 /* 读取产品ID */
    temp[4] = 0;
    /* 判断一下是否是特定的触摸屏 */
    if (strcmp((char *)temp, "911") && strcmp((char *)temp, "9147") && strcmp((char *)temp, "1158") && strcmp((char *)temp, "9271"))
    {
        return 1;   /* 若不是触摸屏用到的GT911/9147/1158/9271，则初始化失败，需硬件查看触摸IC型号以及查看时序函数是否正确 */
    }
    //printf("CTP ID:%s\r\n", temp);                          /* 打印ID */
    temp[0] = 0X02;
    gt911_wr_reg(GT911_CTRL_REG, temp, 1);                /* 软复位GT9XXX */
    
    HAL_Delay(10);
    temp[0] = 0X00;
    gt911_wr_reg(GT911_CTRL_REG, temp, 1);                /* 结束复位, 进入读坐标状态 */

    return 0;
}

/**
 * @brief       扫描触摸屏(采用查询方式)
 * @param       mode : 电容屏未用到次参数, 为了兼容电阻屏
 * @retval      当前触屏状态
 *   @arg       0, 触屏无触摸; 
 *   @arg       1, 触屏有触摸;
 */
uint8_t gt911_scan(uint8_t mode)
{
    uint8_t buf[4];
    uint8_t i = 0;
    uint8_t res = 0;
    uint16_t temp;
    uint16_t tempsta;
    static uint8_t t = 0;                   /* 控制查询间隔,从而降低CPU占用率 */
    t++;

    if ((t % 10) == 0 || t < 10)            /* 空闲时,每进入10次CTP_Scan函数才检测1次,从而节省CPU使用率 */
    {
        gt911_rd_reg(GT911_GSTID_REG, &mode, 1);              /* 读取触摸点的状态 */

        if ((mode & 0X80) && ((mode & 0XF) <= g_gt_tnum))
        {
            i = 0;
            gt911_wr_reg(GT911_GSTID_REG, &i, 1);             /* 清标志 */
        }

        if ((mode & 0XF) && ((mode & 0XF) <= g_gt_tnum))
        {
            temp = 0XFFFF << (mode & 0XF);  /* 将点的个数转换为1的位数,匹配tp_dev.sta定义 */
            tempsta = tp_dev.sta;           /* 保存当前的tp_dev.sta值 */
            tp_dev.sta = (~temp) | TP_PRES_DOWN | TP_CATH_PRES;
            tp_dev.x[g_gt_tnum - 1] = tp_dev.x[0];              /* 保存触点0的数据,保存在最后一个上 */
            tp_dev.y[g_gt_tnum - 1] = tp_dev.y[0];

            for (i = 0; i < g_gt_tnum; i++)
            {
                if (tp_dev.sta & (1 << i))  /* 触摸有效? */
                {
                    gt911_rd_reg(GT911_TPX_TBL[i], buf, 4);   /* 读取XY坐标值 */

                    if (lcddev.id == 0X5510 || lcddev.id == 0X9806 || lcddev.id == 0X7796)     /* 4.3寸800*480 和 3.5寸480*320 MCU屏 */
                    {
                        if (tp_dev.touchtype & 0X01)            /* 横屏 */
                        {
                            tp_dev.x[i] = lcddev.width - (((uint16_t)buf[3] << 8) + buf[2]);
                            tp_dev.y[i] = ((uint16_t)buf[1] << 8) + buf[0];
                        }
                        else
                        {
                            tp_dev.x[i] = ((uint16_t)buf[1] << 8) + buf[0];
                            tp_dev.y[i] = ((uint16_t)buf[3] << 8) + buf[2];
                        }
                    }
                    else                    /* 其他型号 */
                    {
                        if (tp_dev.touchtype & 0X01)            /* 横屏 */
                        {
                            tp_dev.x[i] = ((uint16_t)buf[1] << 8) + buf[0];
                            tp_dev.y[i] = ((uint16_t)buf[3] << 8) + buf[2];
                        }
                        else
                        {
                            tp_dev.x[i] = lcddev.width - (((uint16_t)buf[3] << 8) + buf[2]);
                            tp_dev.y[i] = ((uint16_t)buf[1] << 8) + buf[0];
                        }
                    }

                    //printf("x[%d]:%d,y[%d]:%d\r\n", i, tp_dev.x[i], i, tp_dev.y[i]);
                }
            }

            res = 1;

            if (tp_dev.x[0] > lcddev.width || tp_dev.y[0] > lcddev.height)  /* 非法数据(坐标超出了) */
            {
                if ((mode & 0XF) > 1)       /* 有其他点有数据,则复第二个触点的数据到第一个触点. */
                {
                    tp_dev.x[0] = tp_dev.x[1];
                    tp_dev.y[0] = tp_dev.y[1];
                    t = 0;                  /* 触发一次,则会最少连续监测10次,从而提高命中率 */
                }
                else                        /* 非法数据,则忽略此次数据(还原原来的) */
                {
                    tp_dev.x[0] = tp_dev.x[g_gt_tnum - 1];
                    tp_dev.y[0] = tp_dev.y[g_gt_tnum - 1];
                    mode = 0X80;
                    tp_dev.sta = tempsta;   /* 恢复tp_dev.sta */
                }
            }
            else 
            {
                t = 0;                      /* 触发一次,则会最少连续监测10次,从而提高命中率 */
            }
        }
    }

    if ((mode & 0X8F) == 0X80)              /* 无触摸点按下 */
    {
        if (tp_dev.sta & TP_PRES_DOWN)      /* 之前是被按下的 */
        {
            tp_dev.sta &= ~TP_PRES_DOWN;    /* 标记按键松开 */
        }
        else                                /* 之前就没有被按下 */
        {
            tp_dev.x[0] = 0xffff;
            tp_dev.y[0] = 0xffff;
            tp_dev.sta &= 0XE000;           /* 清除点有效标记 */
        }
    }

    if (t > 240)
    {
        t = 10;                             /* 重新从10开始计数 */
    }

    return res;
}











