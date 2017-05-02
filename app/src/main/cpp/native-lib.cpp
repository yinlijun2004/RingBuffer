#include <jni.h>
#include <string>
#include <assert.h>
#include "app_sys_log.h"

extern "C" {

#include "ring_buffer.h"
    jstring
    Java_com_trendit_ringbuffer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
        uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
        RingBuffer* ring = ring_buffer_create(12);
        ring_buffer_dump(ring);
        app_sys_debug("add %d data", sizeof(data));
        int ret = ring_buffer_append_data(ring, data, sizeof(data));
        assert(ret == 5);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);
        uint8_t consume[12] = {0};
        app_sys_debug("consume %d data", 8);
        ret = ring_buffer_append_consume_data(ring, consume, 8);
        assert(ret == 5);
        app_sys_debug("consume %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", sizeof(data));
        ret = ring_buffer_append_data(ring, data, sizeof(data));
        assert(ret == 5);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);
        app_sys_debug("consume %d data", 8);
        ret = ring_buffer_append_consume_data(ring, consume, 8);
        assert(ret == 5);
        app_sys_debug("consume %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", sizeof(data));
        ret = ring_buffer_append_data(ring, data, sizeof(data));
        assert(ret == 5);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);
        app_sys_debug("consume %d data", 2);
        ret = ring_buffer_append_consume_data(ring, consume, 2);
        assert(ret == 2);
        app_sys_debug("consume %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", sizeof(data));
        ret = ring_buffer_append_data(ring, data, sizeof(data));
        assert(ret == 5);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);
        app_sys_debug("consume %d data", sizeof(consume));
        ret = ring_buffer_append_consume_data(ring, consume, sizeof(consume));
        assert(ret == 8);
        app_sys_debug("consume %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", sizeof(data));
        ret = ring_buffer_append_data(ring, data, sizeof(data));
        assert(ret == 5);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);
        app_sys_debug("consume %d data", sizeof(consume));
        ret = ring_buffer_append_consume_data(ring, consume, sizeof(consume));
        assert(ret == 5);
        app_sys_debug("consume %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", sizeof(data));
        ret = ring_buffer_append_data(ring, data, sizeof(data));
        assert(ret == 5);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);
        app_sys_debug("consume %d data", sizeof(consume));
        ret = ring_buffer_append_consume_data(ring, consume, sizeof(consume));
        assert(ret == 5);
        app_sys_debug("consume %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", sizeof(data));
        ret = ring_buffer_append_data(ring, data, sizeof(data));
        assert(ret == 5);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);
        app_sys_debug("consume %d data", 0);
        ret = ring_buffer_append_consume_data(ring, consume, 0);
        assert(ret == 0);
        app_sys_debug("consume %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("consume %d data", 1);
        ret = ring_buffer_append_consume_data(ring, consume, 1);
        assert(ret == 1);
        app_sys_debug("consume %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", sizeof(data));
        ret = ring_buffer_append_data(ring, data, sizeof(data));
        assert(ret == 5);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", sizeof(data));
        ret = ring_buffer_append_data(ring, data, sizeof(data));
        assert(ret == 0);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", 3);
        ret = ring_buffer_append_data(ring, data, 3);
        assert(ret == 3);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("add %d data", 3);
        ret = ring_buffer_append_data(ring, data, 3);
        assert(ret == 0);
        app_sys_debug("add %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("consume %d data", 12);
        ret = ring_buffer_append_consume_data(ring, consume, 12);
        assert(ret == 12);
        app_sys_debug("consume %d data indeed", ret);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        app_sys_debug("consume %d data", 12);
        ret = ring_buffer_append_consume_data(ring, consume, 12);
        assert(ret == 0);
        app_sys_debug("consume %d data indeed", 0);
        ring_buffer_dump(ring);

        app_sys_debug("================================================");

        return env->NewStringUTF("ring buffer test");
    }
}