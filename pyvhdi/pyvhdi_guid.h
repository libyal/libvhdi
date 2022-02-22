/*
 * GUID functions
 *
 * Copyright (C) 2012-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYVHDI_GUID_H )
#define _PYVHDI_GUID_H

#include <common.h>
#include <types.h>

#include "pyvhdi_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

PyObject *pyvhdi_string_new_from_guid(
           const uint8_t *guid_buffer,
           size_t guid_buffer_size );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVHDI_GUID_H ) */

