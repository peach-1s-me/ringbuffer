/**
 * @file ringbuffer.h
 * @author 文佳源 (648137125@qq.com)
 * @brief 环形缓冲区头文件
 * @version 0.1
 * @date 2023-06-17
 * 
 * Copyright (c) 2023
 * 
 * @par 修订历史
 * <table>
 * <tr><th>版本 <th>作者 <th>日期 <th>修改内容
 * <tr><td>v1.0 <td>文佳源 <td>2023-06-17 <td>新建文件
 * </table>
 */
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "catos_config.h"
#include "catos_types.h"

#define MIN_RINGBUFFER_SIZE     4

typedef struct _ringbuffer_t ringbuffer_t;
struct _ringbuffer_t
{
    cat_uint8_t      *p_buffer;     /* 放置数据的缓冲区地址 */
    cat_uint32_t      ring_mask;    /* 用于循环头尾索引的掩码，用于代替取余操作 */
    cat_uint32_t      tail_index;   /* 尾部索引 */
    cat_uint32_t      head_index;   /* 头部索引 */
};

/**
 * @brief 缓冲区初始化
 * 
 * @param  p_ringbuffer     环形缓冲区结构体指针
 * @param  p_buffer_space   缓冲区内存空间首地址
 * @param  buffer_size      缓冲区大小(字节)
 */
void ringbuffer_init(ringbuffer_t *p_ringbuffer, cat_uint8_t *p_buffer_space, cat_uint32_t buffer_size);

/**
 * @brief 清空缓冲区里所有数据
 * 
 * @param  p_ringbuffer     环形缓冲区结构体指针
 */
void ringbuffer_clear(ringbuffer_t *p_ringbuffer);

/**
 * @brief 从缓冲区取元素
 * 
 * @param  p_ringbuffer     环形缓冲区结构体指针
 * @param  data             要存入的数据值
 * @return cat_int32_t 
 */
cat_int32_t ringbuffer_put(ringbuffer_t *p_ringbuffer, cat_uint8_t data);

/**
 * @brief 
 * 
 * @param  p_ringbuffer     环形缓冲区结构体指针
 * @param  p_data           取出的数据存放的数据地址
 * @return cat_int32_t      成功失败
 */
cat_int32_t ringbuffer_get(ringbuffer_t *p_ringbuffer, cat_uint8_t *p_data);

/**
 * @brief 
 * 
 * @param  p_ringbuffer     环形缓冲区结构体指针
 * @param  p_data           要存入的数据的起始地址
 * @param  size             要存入的数据的长度
 * @return cat_int32_t      成功失败
 */
cat_int32_t ringbuffer_put_more(ringbuffer_t *p_ringbuffer, const cat_uint8_t *p_data, cat_uint32_t size);

/**
 * @brief 
 * 
 * @param  p_ringbuffer     环形缓冲区结构体指针
 * @param  p_data           取出数据要存放的起始地址
 * @param  size             要取出数据的长度
 * @return cat_uint32_t     从环形缓冲区实际取出的数据个数(目前每个数据单位为字节)
 */
cat_uint32_t ringbuffer_get_more(ringbuffer_t *p_ringbuffer, cat_uint8_t *p_data, cat_uint32_t size);

#endif /* #ifndef RINGBUFFER_H */