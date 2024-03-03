/*
 * The region table definitions of a Virtual Hard Disk version 2 (VHDX) file
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

#if !defined( _VHDI_REGION_TABLE_H )
#define _VHDI_REGION_TABLE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vhdi_region_table_header vhdi_region_table_header_t;

struct vhdi_region_table_header
{
	/* The signature
	 * Consists of 4 bytes
	 * Consists of: regi
	 */
	uint8_t signature[ 4 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];
};

typedef struct vhdi_region_table_entry vhdi_region_table_entry_t;

struct vhdi_region_table_entry
{
	/* The type identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t type_identifier[ 16 ];

	/* The data offset
	 * Consists of 8 bytes
	 */
	uint8_t data_offset[ 8 ];

	/* The data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* The is required flag
	 * Consists of 4 bytes
	 */
	uint8_t is_required_flag[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VHDI_REGION_TABLE_H ) */

