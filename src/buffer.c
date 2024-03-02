/**
 * @file buffer.c
 * @author Daniel Chung (daniel.y.chung.mil@army.mil)
 * @brief Implementation of a buffer.
 * @version 0.1
 * @date 2024-02-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/buffer.h"

/**
 * @brief Creates a buffer of size on heap
 *
 * @param size Size of buffer
 * @return buffer_t* On success, pointer to buffer_t. On failure, NULL.
 */
buffer_t * buffer_create (ssize_t size)
{
    buffer_t * p_buffer = NULL;

    if (0 > size)
    {
        (void)fprintf(stderr, "Buffer create error: Invalid arguments\n");
        goto EXIT;
    }

    p_buffer = (buffer_t *)calloc(1, sizeof(buffer_t));

    if (NULL == p_buffer)
    {
        perror("Error: malloc failed\n");
        goto EXIT;
    }

    p_buffer->p_buffer = (char *)calloc(1, size * sizeof(char));

    if (NULL == p_buffer->p_buffer)
    {
        perror("Error: malloc failed\n");
        free(p_buffer);
        p_buffer = NULL;
        goto EXIT;
    }

    p_buffer->offset     = 0;
    p_buffer->buffer_len = size;

EXIT:
    return p_buffer;
}

/**
 * @brief Destroys a buffer
 *
 * Sets pointer to buffer to NULL after destroying buffer
 * @param pp_buffer Pointer to pointer to buffer_t
 * @return int 0 on success, -1 on failure
 */
int buffer_destroy (buffer_t ** pp_buffer)
{
    int status = -1;

    if (NULL == *pp_buffer)
    {
        (void)fprintf(stderr, "[-] Error: Invalid arguments\n");
        goto EXIT;
    }

    free((*pp_buffer)->p_buffer);
    free(*pp_buffer);
    *pp_buffer = NULL;
    status     = 0;

EXIT:
    return status;
}

/**
 * @brief Appends data to buffer
 *
 * @param p_buffer Pointer to buffer_t
 * @param p_data Pointer to data to append
 * @param data_len Length of data to append
 * @return int 0 on success, -1 on failure
 */
int buffer_append (buffer_t * p_buffer, char * p_data, ssize_t data_len)
{
    int status = -1;

    // Check for NULL pointers and negative data length
    if ((NULL == p_buffer) || (NULL == p_data) || (0 > data_len))
    {
        goto EXIT;
    }

    if (p_buffer->offset + data_len > p_buffer->buffer_len)
    {
        p_buffer->p_buffer = (char *)realloc(p_buffer->p_buffer,
                                             p_buffer->buffer_len + data_len);

        if (NULL == p_buffer->p_buffer)
        {
            goto EXIT;
        }

        p_buffer->buffer_len += data_len;
    }

    memcpy(p_buffer->p_buffer + p_buffer->offset, p_data, data_len);
    p_buffer->offset += data_len;
    status = 0;

EXIT:
    return status;
}

/*** end of file ***/
