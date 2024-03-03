/*
 * Metadata item identifier functions
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBVHDI_METADATA_ITEM_IDENTIFIER_H )
#define _LIBVHDI_METADATA_ITEM_IDENTIFIER_H

#include <common.h>
#include <types.h>

#include "libvhdi_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

/* The metadata item identifier is stored as a little endian GUID
 */
typedef struct libvhdi_metadata_item_identifier_definition libvhdi_metadata_item_identifier_definition_t;

struct libvhdi_metadata_item_identifier_definition
{
	/* The identifier
	 */
	uint8_t *identifier;

	/* The description
	 */
	const char *description;
};

LIBVHDI_EXTERN_VARIABLE \
uint8_t libvhdi_metadata_item_identifier_file_parameters[ 16 ];

LIBVHDI_EXTERN_VARIABLE \
uint8_t libvhdi_metadata_item_identifier_logical_sector_size[ 16 ];

LIBVHDI_EXTERN_VARIABLE \
uint8_t libvhdi_metadata_item_identifier_parent_locator[ 16 ];

LIBVHDI_EXTERN_VARIABLE \
uint8_t libvhdi_metadata_item_identifier_physical_sector_size[ 16 ];

LIBVHDI_EXTERN_VARIABLE \
uint8_t libvhdi_metadata_item_identifier_virtual_disk_identifier[ 16 ];

LIBVHDI_EXTERN_VARIABLE \
uint8_t libvhdi_metadata_item_identifier_virtual_disk_size[ 16 ];

#if defined( HAVE_DEBUG_OUTPUT )

const char *libvhdi_metadata_item_identifier_get_description(
             const uint8_t *metadata_item_identifier );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_METADATA_ITEM_IDENTIFIER_H ) */

