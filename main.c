#include "include/buffer.h"
#include "include/serialization.h"
#include <stdio.h>

int main (int argc, char ** argv)
{
    buffer_t * p_buffer = buffer_create(1024);
    uint32_t   value    = 0x12345678;
    uint32_t   result   = 0;

    if (NULL == p_buffer)
    {
        (void)fprintf(stderr, "buffer_create failed\n");
        return -1;
    }

    if (0 != serial_pack(p_buffer, &value, sizeof(value), false))
    {
        (void)fprintf(stderr, "serial_pack failed\n");
        return -1;
    }

    // manually reset offset to unpack
    p_buffer->offset = 0;

    if (0 != serial_unpack(p_buffer, &result, sizeof(result), false))
    {
        (void)fprintf(stderr, "serial_unpack failed\n");
        return -1;
    }

    if (value != result)
    {
        (void)fprintf(stderr, "Mismatch: 0x%08x != 0x%08x\n", value, result);
        return -1;
    }

    buffer_destroy(&p_buffer);

    return 0;
}