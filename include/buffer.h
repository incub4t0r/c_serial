/**
 * @file buffer.h
 * @author Daniel Chung (daniel.y.chung.mil@army.mil)
 * @brief Header file for a buffer implementation.
 * @version 0.1
 * @date 2024-02-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

/**
 * @brief Buffer struct
 *
 * This struct is used to store a char buffer with offset and length.
 *
 * @param p_buffer Pointer to the buffer
 * @param offset Offset into the buffer
 * @param buffer_len Length of the buffer
 */
typedef struct buffer_t
{
    char *  p_buffer;
    ssize_t offset;
    ssize_t buffer_len;
} buffer_t;

buffer_t * buffer_create (ssize_t size);
int        buffer_destroy (buffer_t ** pp_buffer);
int        buffer_append (buffer_t * p_buffer, char * p_data, ssize_t data_len);

#endif // BUFFER_H

/*** end of file ***/
