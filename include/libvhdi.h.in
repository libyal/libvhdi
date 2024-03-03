/*
 * Library to access the Virtual Hard Disk (VHD) image format
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

#if !defined( _LIBVHDI_H )
#define _LIBVHDI_H

#include <libvhdi/codepage.h>
#include <libvhdi/definitions.h>
#include <libvhdi/error.h>
#include <libvhdi/extern.h>
#include <libvhdi/features.h>
#include <libvhdi/types.h>

#include <stdio.h>

#if defined( LIBVHDI_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBVHDI_EXTERN \
const char *libvhdi_get_version(
             void );

/* Returns the access flags for reading
 */
LIBVHDI_EXTERN \
int libvhdi_get_access_flags_read(
     void );

/* Returns the access flags for reading and writing
 */
LIBVHDI_EXTERN \
int libvhdi_get_access_flags_read_write(
     void );

/* Returns the access flags for writing
 */
LIBVHDI_EXTERN \
int libvhdi_get_access_flags_write(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_get_codepage(
     int *codepage,
     libvhdi_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_set_codepage(
     int codepage,
     libvhdi_error_t **error );

/* Determines if a file contains a VHDI file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_check_file_signature(
     const char *filename,
     libvhdi_error_t **error );

#if defined( LIBVHDI_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a VHDI file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_check_file_signature_wide(
     const wchar_t *filename,
     libvhdi_error_t **error );

#endif /* defined( LIBVHDI_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVHDI_HAVE_BFIO )

/* Determines if a file contains a VHDI file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libvhdi_error_t **error );

#endif /* defined( LIBVHDI_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBVHDI_EXTERN \
void libvhdi_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_notify_set_stream(
     FILE *stream,
     libvhdi_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_notify_stream_open(
     const char *filename,
     libvhdi_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_notify_stream_close(
     libvhdi_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBVHDI_EXTERN \
void libvhdi_error_free(
      libvhdi_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_error_fprint(
     libvhdi_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_error_sprint(
     libvhdi_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_error_backtrace_fprint(
     libvhdi_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_error_backtrace_sprint(
     libvhdi_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * File functions
 * ------------------------------------------------------------------------- */

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_initialize(
     libvhdi_file_t **file,
     libvhdi_error_t **error );

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_free(
     libvhdi_file_t **file,
     libvhdi_error_t **error );

/* Signals a file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_signal_abort(
     libvhdi_file_t *file,
     libvhdi_error_t **error );

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_open(
     libvhdi_file_t *file,
     const char *filename,
     int access_flags,
     libvhdi_error_t **error );

#if defined( LIBVHDI_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_open_wide(
     libvhdi_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libvhdi_error_t **error );

#endif /* defined( LIBVHDI_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVHDI_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_open_file_io_handle(
     libvhdi_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvhdi_error_t **error );

#endif /* defined( LIBVHDI_HAVE_BFIO ) */

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_close(
     libvhdi_file_t *file,
     libvhdi_error_t **error );

/* Reads (media) data at the current offset
 * Returns the number of bytes read or -1 on error
 */
LIBVHDI_EXTERN \
ssize_t libvhdi_file_read_buffer(
         libvhdi_file_t *file,
         void *buffer,
         size_t buffer_size,
         libvhdi_error_t **error );

/* Reads (media) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBVHDI_EXTERN \
ssize_t libvhdi_file_read_buffer_at_offset(
         libvhdi_file_t *file,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libvhdi_error_t **error );

/* Seeks a certain offset of the (media) data
 * Returns the offset if seek is successful or -1 on error
 */
LIBVHDI_EXTERN \
off64_t libvhdi_file_seek_offset(
         libvhdi_file_t *file,
         off64_t offset,
         int whence,
         libvhdi_error_t **error );

/* Retrieves the current offset of the (media) data
 * Returns the offset if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_offset(
     libvhdi_file_t *file,
     off64_t *offset,
     libvhdi_error_t **error );

/* Sets the parent file of a differential image
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_set_parent_file(
     libvhdi_file_t *file,
     libvhdi_file_t *parent_file,
     libvhdi_error_t **error );

/* -------------------------------------------------------------------------
 * Meta data functions
 * ------------------------------------------------------------------------- */

/* Retrieves the file type
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_file_type(
     libvhdi_file_t *file,
     int *file_type,
     libvhdi_error_t **error );

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_format_version(
     libvhdi_file_t *file,
     uint16_t *major_version,
     uint16_t *minor_version,
     libvhdi_error_t **error );

/* Retrieves the disk type
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_disk_type(
     libvhdi_file_t *file,
     uint32_t *disk_type,
     libvhdi_error_t **error );

/* Retrieves the media size
 * Returns the 1 if succesful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_media_size(
     libvhdi_file_t *file,
     size64_t *media_size,
     libvhdi_error_t **error );

/* Retrieves the number of bytes per (logical) sector
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_bytes_per_sector(
     libvhdi_file_t *file,
     uint32_t *bytes_per_sector,
     libvhdi_error_t **error );

/* Retrieves the identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * For VHDX this value is obtained from the data write identifier
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_identifier(
     libvhdi_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     libvhdi_error_t **error );

/* Retrieves the parent identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_parent_identifier(
     libvhdi_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     libvhdi_error_t **error );

/* Retrieves the size of the UTF-8 encoded parent filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_utf8_parent_filename_size(
     libvhdi_file_t *file,
     size_t *utf8_string_size,
     libvhdi_error_t **error );

/* Retrieves the UTF-8 encoded parent filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_utf8_parent_filename(
     libvhdi_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libvhdi_error_t **error );

/* Retrieves the size of the UTF-16 encoded parent filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_utf16_parent_filename_size(
     libvhdi_file_t *file,
     size_t *utf16_string_size,
     libvhdi_error_t **error );

/* Retrieves the UTF-16 encoded parent filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_get_utf16_parent_filename(
     libvhdi_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libvhdi_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_H ) */

