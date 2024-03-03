/*
 * The metadata table definitions of a Virtual Hard Disk version 2 (VHDX) file
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

#if !defined( _VHDI_METADATA_TABLE_H )
#define _VHDI_METADATA_TABLE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vhdi_metadata_table_header vhdi_metadata_table_header_t;

struct vhdi_metadata_table_header
{
	/* The signature
	 * Consists of 8 bytes
	 * Consists of: metadata
	 */
	uint8_t signature[ 8 ];

	/* Unknown (reserved)
	 * Consists of 2 bytes
	 */
	uint8_t unknown1[ 2 ];

	/* The number of entries
	 * Consists of 2 bytes
	 */
	uint8_t number_of_entries[ 2 ];

	/* Unknown (reserved)
	 * Consists of 20 bytes
	 */
	uint8_t unknown2[ 20 ];
};

typedef struct vhdi_metadata_table_entry vhdi_metadata_table_entry_t;

struct vhdi_metadata_table_entry
{
	/* The item identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t item_identifier[ 16 ];

	/* The item offset
	 * Consists of 4 bytes
	 */
	uint8_t item_offset[ 4 ];

	/* The item size
	 * Consists of 4 bytes
	 */
	uint8_t item_size[ 4 ];

	/* Unknown (reserved)
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VHDI_METADATA_TABLE_H ) */

