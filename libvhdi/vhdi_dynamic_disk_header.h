/*
 * The dynamic disk header definition of a Virtual Hard Disk (VHD) file
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

#if !defined( _VHDI_DYNAMIC_DISK_HEADER_H )
#define _VHDI_DYNAMIC_DISK_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vhdi_dynamic_disk_header vhdi_dynamic_disk_header_t;

struct vhdi_dynamic_disk_header
{
	/* The signature
	 * Consists of 8 bytes
	 * Consists of: cxsparse
	 */
	uint8_t signature[ 8 ];

	/* The next offset
	 * Consists of 8 bytes
	 */
	uint8_t next_offset[ 8 ];

	/* The block table offset
	 * Consists of 8 bytes
	 */
	uint8_t block_table_offset[ 8 ];

	/* The format version
	 * Consists of 4 bytes
	 */
	uint8_t format_version[ 4 ];

	/* The number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* The block size
	 * Consists of 4 bytes
	 */
	uint8_t block_size[ 4 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The parent identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t parent_identifier[ 16 ];

	/* The parent modification time
	 * Consists of 4 bytes
	 */
	uint8_t parent_modification_time[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The parent filename
	 * Consists of 512 bytes
	 */
	uint8_t parent_filename[ 512 ];

	/* The parent locator entries
	 * Consists of 192 bytes
	 */
	uint8_t parent_locator_entries[ 192 ];

	/* Unknown
	 * Consists of 256 bytes
	 */
	uint8_t unknown2[ 256 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VHDI_DYNAMIC_DISK_HEADER_H ) */

