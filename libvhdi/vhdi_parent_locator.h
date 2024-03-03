/*
 * The parent locator definitions of a Virtual Hard Disk version 2 (VHDX) file
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

#if !defined( _VHDI_PARENT_LOCATOR_H )
#define _VHDI_PARENT_LOCATOR_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vhdi_parent_locator_header vhdi_parent_locator_header_t;

struct vhdi_parent_locator_header
{
	/* The type identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t type_identifier[ 16 ];

	/* Unknown (reserved)
	 * Consists of 2 bytes
	 */
	uint8_t unknown1[ 2 ];

	/* The number of entries
	 * Consists of 2 bytes
	 */
	uint8_t number_of_entries[ 2 ];
};

typedef struct vhdi_parent_locator_entry vhdi_parent_locator_entry_t;

struct vhdi_parent_locator_entry
{
	/* The key data offset
	 * Consists of 4 bytes
	 */
	uint8_t key_data_offset[ 4 ];

	/* The value data offset
	 * Consists of 4 bytes
	 */
	uint8_t value_data_offset[ 4 ];

	/* The key data size
	 * Consists of 2 bytes
	 */
	uint8_t key_data_size[ 2 ];

	/* The value data size
	 * Consists of 2 bytes
	 */
	uint8_t value_data_size[ 2 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VHDI_PARENT_LOCATOR_H ) */

