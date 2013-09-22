/*
 * The internal definitions
 *
 * Copyright (c) 2010-2013, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( LIBFGUID_INTERNAL_DEFINITIONS_H )
#define LIBFGUID_INTERNAL_DEFINITIONS_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBFGUID for local use of libfguid
 */
#if !defined( HAVE_LOCAL_LIBFGUID )
#include <libfguid/definitions.h>

/* The definitions in <libfguid/definitions.h> are copied here
 * for local use of libfguid
 */
#else
#include <byte_stream.h>

#define LIBFGUID_VERSION					20130413

/* The version string
 */
#define LIBFGUID_VERSION_STRING					"20130413"

/* The byte order definitions
 */
#define LIBFGUID_ENDIAN_BIG					_BYTE_STREAM_ENDIAN_BIG
#define LIBFGUID_ENDIAN_LITTLE					_BYTE_STREAM_ENDIAN_LITTLE

/* The GUID identifier version definitions
 */
enum LIBFGUID_IDENTIFIER_VERSIONS
{
	LIBFGUID_IDENTIFIER_VERSION_TIME_BASED			= 1,
	LIBFGUID_IDENTIFIER_VERSION_DCE				= 2,
	LIBFGUID_IDENTIFIER_VERSION_NAME_BASED			= 3,
	LIBFGUID_IDENTIFIER_VERSION_RANDOM_BASED		= 4
};

/* The string format definition flags
 */
enum LIBFGUID_STRING_FORMAT_FLAGS
{
	/* Format the using lower case
	 */
	LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE		= 0x00000001UL,

	/* Format the using upper case
	 */
	LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE		= 0x00000002UL,

	/* Format the using mixed case
	 */
	LIBFGUID_STRING_FORMAT_FLAG_USE_MIXED_CASE		= 0x00000003UL,

	/* Format the using surrounding braces { GUID }
	 */
	LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES	= 0x00000004UL
};

#endif

#endif

