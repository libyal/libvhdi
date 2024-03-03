/*
 * The file footer definition of a Virtual Hard Disk (VHD) file
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

#if !defined( _VHDI_FILE_FOOTER_H )
#define _VHDI_FILE_FOOTER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vhdi_file_footer vhdi_file_footer_t;

struct vhdi_file_footer
{
	/* The signature
	 * Consists of 8 bytes
	 * Consists of: conectix
	 */
	uint8_t signature[ 8 ];

	/* The features
	 * Consists of 4 bytes
	 */
	uint8_t features[ 4 ];

	/* The format version
	 * Consists of 4 bytes
	 */
	uint8_t format_version[ 4 ];

	/* The next offset
	 * Consists of 8 bytes
	 */
	uint8_t next_offset[ 8 ];

	/* The modification time
	 * Consists of 4 bytes
	 */
	uint8_t modification_time[ 4 ];

	/* The creator application
	 * Consists of 4 bytes
	 */
	uint8_t creator_application[ 4 ];

	/* The creator version
	 * Consists of 4 bytes
	 */
	uint8_t creator_version[ 4 ];

	/* The creator (host) operating system
	 * Consists of 4 bytes
	 */
	uint8_t creator_operating_system[ 4 ];

	/* The disk size
	 * Consists of 8 bytes
	 */
	uint8_t disk_size[ 8 ];

	/* The data size
	 * Consists of 8 bytes
	 */
	uint8_t data_size[ 8 ];

	/* The disk geometry
	 * Consists of 4 bytes
	 */
	uint8_t disk_geometry[ 4 ];

	/* The disk type
	 * Consists of 4 bytes
	 */
	uint8_t disk_type[ 4 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t identifier[ 16 ];

	/* The saved state (flag)
	 * Consists of 1 byte
	 */
	uint8_t saved_state;

	/* Unknown
	 * Consists of 427 bytes
	 */
	uint8_t unknown1[ 427 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VHDI_FILE_FOOTER_H ) */

