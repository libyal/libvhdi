/*
 * Checksum functions
 *
 * Copyright (C) 2012-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBVHDI_CHECKSUM_H )
#define _LIBVHDI_CHECKSUM_H

#include <common.h>
#include <types.h>

#include "libvhdi_libcerror.h"
#include "libvhdi_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBVHDI_EXTERN_VARIABLE \
uint32_t libvhdi_checksum_crc32_table[ 256 ];

LIBVHDI_EXTERN_VARIABLE \
int libvhdi_checksum_crc32_table_computed;

void libvhdi_checksum_initialize_crc32_table(
      uint32_t polynomial );

int libvhdi_checksum_calculate_crc32(
     uint32_t *checksum,
     const uint8_t *buffer,
     size_t size,
     uint32_t initial_value,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_CHECKSUM_H ) */

