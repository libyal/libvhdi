/*
 * The image header definition of a Virtual Hard Disk version 2 (VHDX) file
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

#if !defined( _VHDI_IMAGE_HEADER_H )
#define _VHDI_IMAGE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vhdi_image_header vhdi_image_header_t;

struct vhdi_image_header
{
	/* The signature
	 * Consists of 4 bytes
	 * Consists of: head
	 */
	uint8_t signature[ 4 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The sequence number
	 * Consists of 8 bytes
	 */
	uint8_t sequence_number[ 8 ];

	/* The file write identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t file_write_identifier[ 16 ];

	/* The data write identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t data_write_identifier[ 16 ];

	/* The log identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t log_identifier[ 16 ];

	/* The log (journal) format version
	 * Consists of 2 bytes
	 */
	uint8_t log_format_version[ 2 ];

	/* The format version
	 * Consists of 2 bytes
	 */
	uint8_t format_version[ 2 ];

	/* The log (journal) size
	 * Consists of 4 bytes
	 */
	uint8_t log_size[ 4 ];

	/* The log (journal) offset
	 * Consists of 8 bytes
	 */
	uint8_t log_offset[ 8 ];

	/* Unknown (reserved)
	 * Consists of 4016 bytes
	 */
	uint8_t unknown1[ 4016 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VHDI_IMAGE_HEADER_H ) */

