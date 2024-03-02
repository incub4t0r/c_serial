/**
 * @file serialization.c
 * @author Daniel Chung (daniel.y.chung.mil@army.mil)
 * @brief Implementation file for serialization.h
 * @version 0.1
 * @date 2024-02-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/serialization.h"

/**
 * @brief Unpacks a buffer into a destination
 *
 * @param p_src Pointer to the source buffer
 * @param p_dst Pointer to the destination
 * @param size Size to unpack
 * @param b_swap_endian Boolean to swap endianness
 * @return int 0 on success, -1 on failure
 */
int serial_unpack (buffer_t * p_src,
                   void *     p_dst,
                   size_t     size,
                   bool       b_swap_endian)
{
    int status = -1;

    if ((ssize_t)(p_src->offset + size) > p_src->buffer_len)
    {
#ifdef DEBUG
        (void)fprintf(stderr, "buffer overflow\n");
#endif
        goto EXIT;
    }

    memcpy(p_dst, p_src->p_buffer + p_src->offset, size);

    if (b_swap_endian)
    {

        switch (size)
        {
            case sizeof(uint16_t):
                *(uint16_t *)p_dst = be16toh(*(uint16_t *)p_dst);
                break;
            case sizeof(uint32_t):
                *(uint32_t *)p_dst = be32toh(*(uint32_t *)p_dst);
                break;
            case sizeof(uint64_t):
                *(uint64_t *)p_dst = be64toh(*(uint64_t *)p_dst);
                break;
            case sizeof(uint8_t):
            default:
                break;
        }
    }

    p_src->offset += (ssize_t)size;
    status = 0;

EXIT:
    return status;
}

/**
 * @brief Packs a source into a buffer
 *
 * @param p_dst Pointer to the destination buffer
 * @param p_src Pointer to the source
 * @param size Size to pack
 * @param b_swap_endian Boolean to swap endianness
 * @return int 0 on success, -1 on failure
 */
int serial_pack (buffer_t * p_dst,
                 void *     p_src,
                 size_t     size,
                 bool       b_swap_endian)
{
    int status = -1;

    if ((ssize_t)(p_dst->offset + size) > p_dst->buffer_len)
    {
#ifdef DEBUG
        (void)fprintf(stderr, "buffer overflow\n");
#endif
        goto EXIT;
    }

    memcpy(p_dst->p_buffer + p_dst->offset, p_src, size);

    if (b_swap_endian)
    {

        switch (size)
        {
            case sizeof(uint16_t):
                *(uint16_t *)(p_dst->p_buffer + p_dst->offset)
                    = htobe16(*(uint16_t *)(p_dst->p_buffer + p_dst->offset));
                break;
            case sizeof(uint32_t):
                *(uint32_t *)(p_dst->p_buffer + p_dst->offset)
                    = htobe32(*(uint32_t *)(p_dst->p_buffer + p_dst->offset));
                break;
            case sizeof(uint64_t):
                *(uint64_t *)(p_dst->p_buffer + p_dst->offset)
                    = htobe64(*(uint64_t *)(p_dst->p_buffer + p_dst->offset));
                break;
            case sizeof(uint8_t):
            default:
                break;
        }
    }

    p_dst->offset += (ssize_t)size;
    status = 0;

EXIT:
    return status;
}

/*** end of file ***/
