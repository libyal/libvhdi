/*
 * Parent locator entry functions
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

#if !defined( _LIBVHDI_PARENT_LOCATOR_ENTRY_H )
#define _LIBVHDI_PARENT_LOCATOR_ENTRY_H

#include <common.h>
#include <types.h>

#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_parent_locator_entry libvhdi_parent_locator_entry_t;

struct libvhdi_parent_locator_entry
{
	/* The key data offset
	 */
	uint32_t key_data_offset;

	/* The value data offset
	 */
	uint32_t value_data_offset;

	/* The key data size
	 */
	uint16_t key_data_size;

	/* The value data size
	 */
	uint16_t value_data_size;

	/* The key data
	 */
	uint8_t *key_data;

	/* The value data
	 */
	uint8_t *value_data;
};

int libvhdi_parent_locator_entry_initialize(
     libvhdi_parent_locator_entry_t **parent_locator_entry,
     libcerror_error_t **error );

int libvhdi_parent_locator_entry_free(
     libvhdi_parent_locator_entry_t **parent_locator_entry,
     libcerror_error_t **error );

int libvhdi_parent_locator_entry_read_data(
     libvhdi_parent_locator_entry_t *parent_locator_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvhdi_parent_locator_entry_read_key_value_data(
     libvhdi_parent_locator_entry_t *parent_locator_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvhdi_parent_locator_compare_key_with_utf8_string(
     libvhdi_parent_locator_entry_t *parent_locator_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error );

int libvhdi_parent_locator_get_value_as_guid(
     libvhdi_parent_locator_entry_t *parent_locator_entry,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_PARENT_LOCATOR_ENTRY_H ) */

