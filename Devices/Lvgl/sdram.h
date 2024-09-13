#ifndef __SDRAM_H
#define __SDRAM_H

#include "stdint.h"

#define BANK5_SDRAM_ADDR    ((uint32_t)(0XC0000000))  /* SDRAM开始地址 */
/* 定义三个内存池 */
#define SRAMIN                  0                               /* 内部内存池 */
#define SRAMCCM                 1                               /* CCM内存池(此部分SRAM仅仅CPU可以访问!!!) */
#define SRAMEX                  2                               /* 外部内存池(SDRAM) */

/* 定义内存管理表类型,当外扩SDRAM的时候，必须使用uint32_t类型，否则可以定义成uint16_t，以节省内存占用 */
#define MT_TYPE     uint32_t
#define SRAMBANK                3                               /* 定义支持的SRAM块数. */
/* mem1内存参数设定.mem1完全处于内部SRAM里面. */
#define MEM1_BLOCK_SIZE         64                              /* 内存块大小为64字节 */
#define MEM1_MAX_SIZE           20 * 1024                       /* 最大管理内存 160K，具体管理大小根据实际工程配置 */
#define MEM1_ALLOC_TABLE_SIZE   MEM1_MAX_SIZE/MEM1_BLOCK_SIZE   /* 内存表大小 */
/* mem2内存参数设定.mem2处于CCM,用于管理CCM(特别注意,这部分SRAM,仅CPU可以访问!!) */
#define MEM2_BLOCK_SIZE         64                              /* 内存块大小为64字节 */
#define MEM2_MAX_SIZE           60 * 1024                       /* 最大管理内存60K */
#define MEM2_ALLOC_TABLE_SIZE   MEM2_MAX_SIZE/MEM2_BLOCK_SIZE   /* 内存表大小 */
/* mem3内存参数设定.mem2的内存池处于外部SDRAM里面 */
#define MEM3_BLOCK_SIZE         64                              /* 内存块大小为64字节 */
#define MEM3_MAX_SIZE           50 * 1024                       /* 最大管理内存28912K，具体管理大小根据实际工程配置 */
#define MEM3_ALLOC_TABLE_SIZE   MEM3_MAX_SIZE/MEM3_BLOCK_SIZE   /* 内存表大小 */
/* SDRAM配置参数 */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

/* 内存管理控制器 */
struct _m_mallco_dev
{
    void (*init)(uint8_t);              /* 初始化 */
    uint16_t (*perused)(uint8_t);       /* 内存使用率 */
    uint8_t *membase[SRAMBANK];         /* 内存池 管理SRAMBANK个区域的内存 */
    uint32_t *memmap[SRAMBANK];         /* 内存管理状态表 */
    uint8_t  memrdy[SRAMBANK];          /* 内存管理是否就绪 */
};

void sdram_initialization_sequence(void);

void my_mem_set(void *s, uint8_t c, uint32_t count);  /* 设置内存 */
void my_mem_copy(void *des, void *src, uint32_t n);   /* 复制内存 */
void my_mem_init(uint8_t memx);                       /* 内存管理初始化函数(外/内部调用) */
uint32_t my_mem_malloc(uint8_t memx, uint32_t size);  /* 内存分配(内部调用) */
uint8_t my_mem_free(uint8_t memx, uint32_t offset);   /* 内存释放(内部调用) */
uint16_t my_mem_perused(uint8_t memx) ;               /* 获得内存使用率(外/内部调用)  */
/* 用户调用函数 */
void myfree(uint8_t memx, void *ptr);                   /* 内存释放(外部调用) */
void *mymalloc(uint8_t memx, uint32_t size);            /* 内存分配(外部调用) */
void *myrealloc(uint8_t memx, void *ptr, uint32_t size);/* 重新分配内存(外部调用) */


#endif
