#include <stdio.h>
#include "ringbuffer.h"

#define BUFF_SPACE_SIZE  16

ringbuffer_t buf;
cat_uint8_t  space[BUFF_SPACE_SIZE];

extern void ringbuffer_print_all(ringbuffer_t *p_ringbuffer);

int main(void)
{
    unsigned char i = 0;
    unsigned char ch = 0;
    int err = 0;

    /* 初始化环形缓冲区 */
    ringbuffer_init(&buf, space, BUFF_SPACE_SIZE);

    printf("TEST RINGBUFFER\n");
    printf("buffer size=%d\n\n", BUFF_SPACE_SIZE);

    /* 放入5个数据 */
    printf("\n--->put 5 data in ringbuffer\n");
    for(i=0; i<5; i++)
    {
        err = ringbuffer_put(&buf, i);
        if(CAT_ERROR == err)
        {
            printf("data flushed when put data, i=%2d\n", i);
        }
    }
    ringbuffer_print_all(&buf);

    /* 取出3个数据 */
    printf("\n<---get 2 data in ringbuffer\n");
    for(i=0; i<2; i++)
    {
        err = ringbuffer_get(&buf, &ch);
        if(CAT_ERROR == err)
        {
            printf("data flushed when get data, i=%2d\n", i);
        }
        else
        {
            printf("    index=%2d, data=0x%x\n", i, ch);
        }
    }
    ringbuffer_print_all(&buf);

    /* 清空 */
    ringbuffer_clear(&buf);

    /* 尝试放入比缓冲区容量更大的数据 */
    printf("\n--->put 15 data in ringbuffer to make buffer full\n");
    for(i=0; i<15; i++)
    {
        err = ringbuffer_put(&buf, i);
        if(CAT_ERROR == err)
        {
            printf("data flushed when put data, i=%2d\n", i);
        }
    }
    ringbuffer_print_all(&buf);
    printf("\n--->put more 16 data in ringbuffer to flush the buffer\n");
    for(i=15; i<31; i++)
    {
        err = ringbuffer_put(&buf, i);
        if(CAT_ERROR == err)
        {
            printf("data flushed when put data, i=%2d\n", i);
        }
    }
    ringbuffer_print_all(&buf);

    /* 尝试取出比缓冲区更大的数据 */
    printf("\n<---get 17 data in ringbuffer\n");
    for(i=0; i<16; i++)
    {
        err = ringbuffer_get(&buf, &ch);
        if(CAT_ERROR == err)
        {
            printf("data flushed when get data, i=%2d\n", i);
        }
        else
        {
            printf("    index=%2d, data=0x%x\n", i, ch);
        }
    }
    ringbuffer_print_all(&buf);


    return 0;
}