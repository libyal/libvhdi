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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libvhdi_metadata_item_identifier.h"

uint8_t libvhdi_metadata_item_identifier_file_parameters[ 16 ] = {
	0x37, 0x67, 0xa1, 0xca, 0x36, 0xfa, 0x43, 0x4d, 0xb3, 0xb6, 0x33, 0xf0, 0xaa, 0x44, 0xe7, 0x6b };

uint8_t libvhdi_metadata_item_identifier_logical_sector_size[ 16 ] = {
	0x1d, 0xbf, 0x41, 0x81, 0x6f, 0xa9, 0x09, 0x47, 0xba, 0x47, 0xf2, 0x33, 0xa8, 0xfa, 0xab, 0x5f };

uint8_t libvhdi_metadata_item_identifier_parent_locator[ 16 ] = {
	0x2d, 0x5f, 0xd3, 0xa8, 0x0b, 0xb3, 0x4d, 0x45, 0xab, 0xf7, 0xd3, 0xd8, 0x48, 0x34, 0xab, 0x0c };

uint8_t libvhdi_metadata_item_identifier_physical_sector_size[ 16 ] = {
	0xc7, 0x48, 0xa3, 0xcd, 0x5d, 0x44, 0x71, 0x44, 0x9c, 0xc9, 0xe9, 0x88, 0x52, 0x51, 0xc5, 0x56 };

uint8_t libvhdi_metadata_item_identifier_virtual_disk_identifier[ 16 ] = {
	0xab, 0x12, 0xca, 0xbe, 0xe6, 0xb2, 0x23, 0x45, 0x93, 0xef, 0xc3, 0x09, 0xe0, 0x00, 0xc7, 0x46 };

uint8_t libvhdi_metadata_item_identifier_virtual_disk_size[ 16 ] = {
	0x24, 0x42, 0xa5, 0x2f, 0x1b, 0xcd, 0x76, 0x48, 0xb2, 0x11, 0x5d, 0xbe, 0xd8, 0x3b, 0xf4, 0xb8 };

#if defined( HAVE_DEBUG_OUTPUT )

uint8_t libvhdi_metadata_item_identifier_unknown[ 16 ] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

/* The metadata item identifiers
 */
libvhdi_metadata_item_identifier_definition_t libvhdi_metadata_item_identifier_definitions[ ] = {
	{ libvhdi_metadata_item_identifier_file_parameters,		"File parameters" },
	{ libvhdi_metadata_item_identifier_logical_sector_size,		"Logical sector size" },
	{ libvhdi_metadata_item_identifier_parent_locator,		"Parent locator" },
	{ libvhdi_metadata_item_identifier_physical_sector_size,	"Physical sector size" },
	{ libvhdi_metadata_item_identifier_virtual_disk_identifier,	"Virtual disk identifier" },
	{ libvhdi_metadata_item_identifier_virtual_disk_size,		"Virtual disk size" },

	{ libvhdi_metadata_item_identifier_unknown,			"Unknown" } };

/* Retrieves a string containing the description of the metadata item identifier
 */
const char *libvhdi_metadata_item_identifier_get_description(
             const uint8_t *metadata_item_identifier )
{
	int iterator = 0;

	if( metadata_item_identifier == NULL )
	{
		return( "Invalid metadata item identifier" );
	}
	while( memory_compare(
	        ( libvhdi_metadata_item_identifier_definitions[ iterator ] ).identifier,
	        libvhdi_metadata_item_identifier_unknown,
	        16 ) != 0 )
	{
		if( memory_compare(
		     ( libvhdi_metadata_item_identifier_definitions[ iterator ] ).identifier,
		     metadata_item_identifier,
		     16 ) == 0 )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libvhdi_metadata_item_identifier_definitions[ iterator ] ).description );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

