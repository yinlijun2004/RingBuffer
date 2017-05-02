//
// Created by yinlijun on 2017/4/27.
//

#ifndef CRCDEMO_RING_BUFFER_H
#define CRCDEMO_RING_BUFFER_H

#include <stdint.h>

struct RingBuffer;
typedef struct RingBuffer RingBuffer;

/** 创建一个RingBuffer对象，表示环形buffer,可以避免重复申请内存。
 * @param[in] size RingBuffer的可容纳字节长度。
 * @return RingBuffer RingBuffer对象。
 */
RingBuffer* ring_buffer_create(uint32_t size);

/** 往RingBuffer追加数据。
 * @param[in] data 数据。
 * @param[in] data_len 数据长度。
 * @return 实际追加的数据长度，如果剩余空间不足，返回0，不追加任何数据。
 */
uint32_t ring_buffer_append_data(RingBuffer* thiz, uint8_t *data, uint32_t data_len);

/** 消费数据。
 * @param[in] data 用于存放消费数据的buffer。
 * @param[in] data_len buffer长度，如果RingBuffer中的数据长度小于buffer长度，返回实际消费的长度。
 * @return 实际消费的长度。
 */
uint32_t ring_buffer_append_consume_data(RingBuffer* thiz, uint8_t* data, uint32_t data_len);

/** 打印所有在RingBuffer中的数据
 */
void ring_buffer_dump(RingBuffer* thiz);

/** 获取当前数据长度。
 */
uint32_t ring_buffer_get_buffer_len(RingBuffer* thiz);

/** 获取剩余空间长度。
 */
uint32_t ring_buffer_get_free_len(RingBuffer* thiz);

#endif //CRCDEMO_RING_BUFFER_H
