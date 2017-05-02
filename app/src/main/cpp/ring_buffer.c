//
// Created by yinlijun on 2017/4/27.
//

#include <malloc.h>
#include <string.h>
#include "app_sys_log.h"
#include "ring_buffer.h"

struct RingBuffer{
    uint8_t *ring_buffer;
    uint32_t fill_index;
    uint32_t consume_index;
    uint32_t buffer_len;
    uint32_t size;
};
#define MIN_RING_BUFFER_LENGTH (10)//(8192)
#define MAX_RING_BUFFER_LENGTH (12288)

RingBuffer* ring_buffer_create(uint32_t size) {
    if(size < MIN_RING_BUFFER_LENGTH || size > MAX_RING_BUFFER_LENGTH ) {
        return NULL;
    }
    RingBuffer* thiz = (RingBuffer *)malloc(sizeof(RingBuffer));
    thiz->ring_buffer = (uint8_t *)malloc(size);
    if(thiz->ring_buffer == NULL) {
        free(thiz);
        return NULL;
    }
    memset(thiz->ring_buffer, 0, size);
    thiz->fill_index = 0;
    thiz->consume_index = 0;
    thiz->size = size;
    thiz->buffer_len = 0;

    return thiz;
}

uint32_t ring_buffer_append_data(RingBuffer* thiz, uint8_t *data, uint32_t data_len) {
    if(thiz == NULL || data == NULL || data_len <= 0) {
        return 0;
    }
    uint32_t fill_to_index = (thiz->fill_index + data_len) % thiz->size;
    uint32_t ret = data_len;
    uint32_t free_len = ring_buffer_get_free_len(thiz);
    if(data_len > free_len) {
        return 0;
    }

    thiz->buffer_len += data_len;
    if(data_len + thiz->fill_index < thiz->size) {
        memcpy(thiz->ring_buffer + thiz->fill_index, data, data_len);
    } else {
        //到buffer尾部
        uint32_t first_sec_len = thiz->size - thiz->fill_index;
        memcpy(thiz->ring_buffer + thiz->fill_index, data, first_sec_len);
        uint32_t second_sec_len = data_len - first_sec_len;
        memcpy(thiz->ring_buffer, data + first_sec_len, second_sec_len);
    }
    thiz->fill_index = fill_to_index;

    return ret;
}

uint32_t ring_buffer_get_free_len(RingBuffer* thiz) {
    return thiz->size - thiz->buffer_len;
}

uint32_t ring_buffer_get_buffer_len(RingBuffer* thiz) {
    return thiz->buffer_len;
}

uint32_t ring_buffer_append_consume_data(RingBuffer* thiz, uint8_t* data, uint32_t data_len) {
    if(thiz == NULL || data == NULL || data_len <= 0) {
        return 0;
    }
    uint32_t buffer_len = ring_buffer_get_buffer_len(thiz);
    //实际消费长度
    data_len = buffer_len >= data_len ? data_len : buffer_len;
    uint32_t new_consume_index = (data_len + thiz->consume_index) % thiz->size;
    thiz->buffer_len -= data_len;

    if(data_len + thiz->consume_index < thiz->size) {
        memcpy(thiz->ring_buffer + thiz->consume_index, data, data_len);
    } else {
        //到buffer尾部
        uint32_t  first_sec_len = thiz->size - thiz->consume_index;
        memcpy(thiz->ring_buffer + thiz->consume_index, data, first_sec_len);
        uint32_t second_sec_len = data_len - first_sec_len;
        memcpy(thiz->ring_buffer, data + first_sec_len, second_sec_len);
    }
    thiz->consume_index = new_consume_index;
    return data_len;
}

void ring_buffer_dump(RingBuffer* thiz) {
#ifdef DUMP_FREE_SPACE
    app_sys_dump(NULL, thiz->ring_buffer, thiz->size);
    app_sys_debug("fill_index %d, consume_index %d", thiz->fill_index, thiz->consume_index);
#else
    if(thiz->buffer_len < 1) {
        return;
    }
    uint32_t index = thiz->consume_index;
    if(index + thiz->buffer_len < thiz->size) {
        app_sys_dump("dump ring buffer", thiz->ring_buffer + index, thiz->buffer_len);
    } else {
        app_sys_dump("dump ring buffer 1", thiz->ring_buffer + index, thiz->size - index);
        app_sys_dump("dump ring buffer 2", thiz->ring_buffer, thiz->fill_index);
    }
#endif
}