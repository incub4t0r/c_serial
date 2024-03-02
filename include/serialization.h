/**
 * @file serialization.h
 * @author Daniel Chung (daniel.y.chung.mil@army.mil)
 * @brief Header file for serialization.c
 * @version 0.1
 * @date 2024-02-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "buffer.h"

int serial_unpack (buffer_t * p_src,
                   void *     p_dst,
                   size_t     size,
                   bool       b_swap_endian);

int serial_pack (buffer_t * p_dst,
                 void *     p_src,
                 size_t     size,
                 bool       b_swap_endian);

#endif // SERIALIZATION_H

/*** end of file ***/
