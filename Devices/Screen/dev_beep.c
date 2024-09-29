#include "dev_beep.h"

uint8_t Beep_flg = 0;
/**
 * @brief       初始化IIC
 * @param       无
 * @retval      无
 */
void iic_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    IIC_SCL_GPIO_CLK_ENABLE();                              /* SCL引脚时钟使能 */
    IIC_SDA_GPIO_CLK_ENABLE();                              /* SDA引脚时钟使能 */

    gpio_init_struct.Pin = IIC_SCL_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* 快速 */
    HAL_GPIO_Init(IIC_SCL_GPIO_PORT, &gpio_init_struct);    /* SCL引脚初始化 */

    /* SDA引脚开漏输出,上拉, 这样就不用再设置IO方向了,开漏输出的时候(=1), 也可以读取外部信号的高低电平 */
    gpio_init_struct.Pin = IIC_SDA_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_OD;            /* 开漏输出 */
    HAL_GPIO_Init(IIC_SDA_GPIO_PORT, &gpio_init_struct);    /* SDA引脚初始化 */

    iic_stop();                                             /* 停止总线上所有设备 */
}

/**
 * @brief       IIC延时函数,用于控制IIC读写速度
 * @param       无
 * @retval      无
 */
static void iic_delay(void)
{
    uint16_t tick = 20;            /* 2us的延时, 读写速度在250Khz以内 */
		while(tick--);
}

/**
 * @brief       产生IIC起始信号
 * @param       无
 * @retval      无
 */
void iic_start(void)
{
    IIC_SDA(1);
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(0);             /* START信号: 当SCL为高时, SDA从高变成低, 表示起始信号 */
    iic_delay();
    IIC_SCL(0);             /* 钳住I2C总线，准备发送或接收数据 */
    iic_delay();
}

/**
 * @brief       产生IIC停止信号
 * @param       无
 * @retval      无
 */
void iic_stop(void)
{
    IIC_SDA(0);             /* STOP信号: 当SCL为高时, SDA从低变成高, 表示停止信号 */
    iic_delay();
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(1);             /* 发送I2C总线结束信号 */
    iic_delay();
}

/**
 * @brief       等待应答信号到来
 * @param       无
 * @retval      1，接收应答失败
 *              0，接收应答成功
 */
uint8_t iic_wait_ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;

    IIC_SDA(1);             /* 主机释放SDA线(此时外部器件可以拉低SDA线) */
    iic_delay();
    IIC_SCL(1);             /* SCL=1, 此时从机可以返回ACK */
    iic_delay();

    while (IIC_READ_SDA)    /* 等待应答 */
    {
        waittime++;

        if (waittime > 250)
        {
            iic_stop();
            rack = 1;
            break;
        }
    }

    IIC_SCL(0);             /* SCL=0, 结束ACK检查 */
    iic_delay();
    return rack;
}

/**
 * @brief       产生ACK应答
 * @param       无
 * @retval      无
 */
void iic_ack(void)
{
    IIC_SDA(0);             /* SCL 0 -> 1 时 SDA = 0,表示应答 */
    iic_delay();
    IIC_SCL(1);             /* 产生一个时钟 */
    iic_delay();
    IIC_SCL(0);
    iic_delay();
    IIC_SDA(1);             /* 主机释放SDA线 */
    iic_delay();
}

/**
 * @brief       不产生ACK应答
 * @param       无
 * @retval      无
 */
void iic_nack(void)
{
    IIC_SDA(1);             /* SCL 0 -> 1  时 SDA = 1,表示不应答 */
    iic_delay();
    IIC_SCL(1);             /* 产生一个时钟 */
    iic_delay();
    IIC_SCL(0);
    iic_delay();
}

/**
 * @brief       IIC发送一个字节
 * @param       data: 要发送的数据
 * @retval      无
 */
void iic_send_byte(uint8_t data)
{
    uint8_t t;
    
    for (t = 0; t < 8; t++)
    {
        IIC_SDA((data & 0x80) >> 7);    /* 高位先发送 */
        iic_delay();
        IIC_SCL(1);
        iic_delay();
        IIC_SCL(0);
        data <<= 1;             /* 左移1位,用于下一次发送 */
    }
    IIC_SDA(1);                 /* 发送完成, 主机释放SDA线 */
}

/**
 * @brief       IIC读取一个字节
 * @param       ack:  ack=1时，发送ack; ack=0时，发送nack
 * @retval      接收到的数据
 */
uint8_t iic_read_byte(uint8_t ack)
{
    uint8_t i, receive = 0;

    for (i = 0; i < 8; i++ )    /* 接收1个字节数据 */
    {
        receive <<= 1;          /* 高位先输出,所以先收到的数据位要左移 */
        IIC_SCL(1);
        iic_delay();

        if (IIC_READ_SDA)
        {
            receive++;
        }
        
        IIC_SCL(0);
        iic_delay();
    }

    if (!ack)
    {
        iic_nack();             /* 发送nACK */
    }
    else
    {
        iic_ack();              /* 发送ACK */
    }

    return receive;
}


/**
 * @brief       初始化PCF8574
 * @param       无
 * @retval      0, 成功;
                1, 失败;
 */
uint8_t pcf8574_init(void)
{
    uint8_t temp = 0;
    
    GPIO_InitTypeDef gpio_init_struct;
    PCF8574_GPIO_CLK_ENABLE();                               /* 使能GPIOB时钟 */

    gpio_init_struct.Pin = PCF8574_GPIO_PIN;                 /* PB12 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                 /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                     /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_HIGH;                /* 高速 */
    HAL_GPIO_Init(PCF8574_GPIO_PORT, &gpio_init_struct);     /* 初始化IO */

    iic_init();                                              /* IIC初始化 */

    /* 检查PCF8574是否在位 */
    iic_start();
    iic_send_byte(PCF8574_ADDR);                             /* 写地址 */
    temp = iic_wait_ack();                                   /* 等待应答,通过判断是否有ACK应答,来判断PCF8574的状态 */
    iic_stop();                                              /* 产生一个停止条件 */
    pcf8574_write_byte(0XFF);                                /* 默认情况下所有IO输出高电平 */
    return temp;
}

/**
 * @brief       读取PCF8574的8位IO值
 * @param       无
 * @retval      读到的数据
 */
uint8_t pcf8574_read_byte(void)
{ 
    uint8_t temp = 0;

    iic_start();
    iic_send_byte(PCF8574_ADDR | 0X01);   /* 进入接收模式 */
    iic_wait_ack();
    temp = iic_read_byte(0);
    iic_stop();                           /* 产生一个停止条件 */

    return temp;
}

/**
 * @brief       向PCF8574写入8位IO值
 * @param       data   : 要写入的数据
 * @retval      无
 */
void pcf8574_write_byte(uint8_t data)
{
    iic_start();  
    iic_send_byte(PCF8574_ADDR | 0X00);   /* 发送器件地址0X40,写数据 */
    iic_wait_ack();
    iic_send_byte(data);                  /* 发送字节 */
    iic_wait_ack();
    iic_stop();                           /* 产生一个停止条件  */
    HAL_Delay(10); 
}

/**
 * @brief       设置PCF8574某个IO的高低电平
 * @param       bit    : 要设置的IO编号,0~7
 * @param       sta    : IO的状态;0或1
 * @retval      无
 */
void pcf8574_write_bit(uint8_t bit, uint8_t sta)
{
    uint8_t data;

    data = pcf8574_read_byte();          /* 先读出原来的设置 */

    if (sta == 0)
    {
        data &= ~(1 << bit);
    }
    else
    {
        data |= 1 << bit;
    }

    pcf8574_write_byte(data);            /* 写入新的数据 */
}

/**
 * @brief       读取PCF8574的某个IO的值
 * @param       bit     : 要读取的IO编号, 0~7
 * @retval      此IO口的值(状态, 0/1)
 */
uint8_t pcf8574_read_bit(uint8_t bit)
{
    uint8_t data;

    data = pcf8574_read_byte();          /* 先读取这个8位IO的值  */

    if (data & (1 << bit))
    {
        return 1;
    }
    else 
    {
        return 0; 
    }
}  

void beep_func(void)
{
		static uint16_t Count = 0;
		if(Beep_flg == 1)
		{
				Count++;
				if(Count > 25)
				{
						Beep_flg = 0;
						Count = 0;
				}
				pcf8574_write_byte(0xFE);
		}else if(Beep_flg == 0)
		{
				pcf8574_write_byte(0xFF);
		}else
		{
		}
}
