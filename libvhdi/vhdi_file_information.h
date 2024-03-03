/*
 * The file information definition of a Virtual Hard Disk version 2 (VHDX) file
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

#if !defined( _VHDI_FILE_INFORMATION_H )
#define _VHDI_FILE_INFORMATION_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vhdi_file_information vhdi_file_information_t;

struct vhdi_file_information
{
	/* The signature
	 * Consists of 8 bytes
	 * Consists of: vhdxfile
	 */
	uint8_t signature[ 8 ];

	/* The creator
	 * Consists of 512 bytes
	 */
	uint8_t creator[ 512 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VHDI_FILE_INFORMATION_H ) */

