/*
 * Region type identifier functions
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libvhdi_region_type_identifier.h"

uint8_t libvhdi_region_type_identifier_block_allocation_table[ 16 ] = {
	0x66, 0x77, 0xc2, 0x2d, 0x23, 0xf6, 0x00, 0x42, 0x9d, 0x64, 0x11, 0x5e, 0x9b, 0xfd, 0x4a, 0x08 };

uint8_t libvhdi_region_type_identifier_metadata_table[ 16 ] = {
	0x06, 0xa2, 0x7c, 0x8b, 0x90, 0x47, 0x9a, 0x4b, 0xb8, 0xfe, 0x57, 0x5f, 0x05, 0x0f, 0x88, 0x6e };

#if defined( HAVE_DEBUG_OUTPUT )

uint8_t libvhdi_region_type_identifier_unknown[ 16 ] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

/* The region type identifiers
 */
libvhdi_region_type_identifier_definition_t libvhdi_region_type_identifier_definitions[ ] = {
	{ libvhdi_region_type_identifier_block_allocation_table,	"Block allocation table (BAT)" },
	{ libvhdi_region_type_identifier_metadata_table,		"Metadata table" },

	{ libvhdi_region_type_identifier_unknown,			"Unknown" } };

/* Retrieves a string containing the description of the region type identifier
 */
const char *libvhdi_region_type_identifier_get_description(
             const uint8_t *region_type_identifier )
{
	int iterator = 0;

	if( region_type_identifier == NULL )
	{
		return( "Invalid region type identifier" );
	}
	while( memory_compare(
	        ( libvhdi_region_type_identifier_definitions[ iterator ] ).identifier,
	        libvhdi_region_type_identifier_unknown,
	        16 ) != 0 )
	{
		if( memory_compare(
		     ( libvhdi_region_type_identifier_definitions[ iterator ] ).identifier,
		     region_type_identifier,
		     16 ) == 0 )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libvhdi_region_type_identifier_definitions[ iterator ] ).description );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

