#!/usr/bin/env python
#
# Python-bindings read testing program
#
# Copyright (C) 2012-2022, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.

from __future__ import print_function
import argparse
import os
import sys

import pyvhdi


def get_whence_string(whence):
  """Retrieves a human readable string representation of the whence."""
  if whence == os.SEEK_CUR:
    whence_string = "SEEK_CUR"
  elif whence == os.SEEK_END:
    whence_string = "SEEK_END"
  elif whence == os.SEEK_SET:
    whence_string = "SEEK_SET"
  else:
    whence_string = "UNKNOWN"
  return whence_string


def pyvhdi_test_seek_offset_and_read_buffer(
    vhdi_file, input_offset, input_whence, input_size,
    expected_offset, expected_size):
  """Tests seeking an offset and reading a buffer."""
  description = (
      "Testing reading buffer at offset: {0:d}, whence: {1:s} of size: {2:d}"
      "\t").format(input_offset, get_whence_string(input_whence), input_size)
  print(description, end="")

  error_string = None
  result = True
  try:
    vhdi_file.seek(input_offset, input_whence)

    result_offset = vhdi_file.get_offset()
    if expected_offset != result_offset:
      result = False

    if result:
      result_size = 0
      while input_size > 0:
        read_size = 4096
        if input_size < read_size:
          read_size = input_size

        data = vhdi_file.read(size=read_size)
        data_size = len(data)

        input_size -= data_size
        result_size += data_size

        if data_size != read_size:
          break

      if result_size != expected_size:
        error_string = "Unexpected read count: {0:d}".format(result_size)
        result = False

  except Exception as exception:
    error_string = str(exception)
    if expected_offset != -1:
      result = False

  if not result:
    print("(FAIL)")
  else:
    print("(PASS)")

  if error_string:
    print(error_string)
  return result


def pyvhdi_test_read_buffer_at_offset(
    vhdi_file, input_offset, input_size,
    expected_offset, expected_size):
  """Tests reading a buffer at a specific offset."""
  description = (
      "Testing reading buffer at offset: {0:d} and size: {1:d}"
      "\t").format(input_offset, input_size)
  print(description, end="")

  error_string = None
  result = True
  try:
    result_size = 0
    while input_size > 0:
      read_size = 4096
      if input_size < read_size:
        read_size = input_size

      data = vhdi_file.read_buffer_at_offset(read_size, input_offset)
      data_size = len(data)

      input_offset += data_size
      input_size -= data_size
      result_size += data_size

      if data_size != read_size:
        break

    if input_offset != expected_offset:
      error_string = "Unexpected offset: {0:d}".format(input_offset)
      result = False

    elif result_size != expected_size:
      error_string = "Unexpected read count: {0:d}".format(result_size)
      result = False

  except Exception as exception:
    error_string = str(exception)
    if expected_offset != -1:
      result = False

  if not result:
    print("(FAIL)")
  else:
    print("(PASS)")

  if error_string:
    print(error_string)
  return result


def pyvhdi_test_read(vhdi_file):
  """Tests the read function."""
  media_size = vhdi_file.media_size

  # Case 0: test full read

  # Test: offset: 0 size: <media_size>
  # Expected result: offset: 0 size: <media_size>
  read_offset = 0
  read_size = media_size

  if not pyvhdi_test_seek_offset_and_read_buffer(
      vhdi_file, read_offset, os.SEEK_SET, read_size,
      read_offset, read_size):
    return False

  if not pyvhdi_test_seek_offset_and_read_buffer(
      vhdi_file, read_offset, os.SEEK_SET, read_size,
      read_offset, read_size):
    return False

  # Case 1: test buffer at offset read

  # Test: offset: <media_size / 7> size: <media_size / 2>
  # Expected result: offset: <media_size / 7> size: <media_size / 2>
  read_offset, _ = divmod(media_size, 7)
  read_size, _ = divmod(media_size, 2)

  if not pyvhdi_test_seek_offset_and_read_buffer(
      vhdi_file, read_offset, os.SEEK_SET, read_size,
      read_offset, read_size):
    return False

  if not pyvhdi_test_seek_offset_and_read_buffer(
      vhdi_file, read_offset, os.SEEK_SET, read_size,
      read_offset, read_size):
    return False

  # Case 2: test read beyond media size

  if media_size < 1024:
    # Test: offset: <media_size - 1024> size: 4096
    # Expected result: offset: -1 size: <undetermined>
    read_offset = media_size - 1024
    read_size = 4096

    if not pyvhdi_test_seek_offset_and_read_buffer(
        vhdi_file, read_offset, os.SEEK_SET, read_size, -1, -1):
      return False

    if not pyvhdi_test_seek_offset_and_read_buffer(
        vhdi_file, read_offset, os.SEEK_SET, read_size, -1, -1):
      return False

  else:
    # Test: offset: <media_size - 1024> size: 4096
    # Expected result: offset: <media_size - 1024> size: 1024
    read_offset = media_size - 1024
    read_size = 4096

    if not pyvhdi_test_seek_offset_and_read_buffer(
        vhdi_file, read_offset, os.SEEK_SET, read_size,
        read_offset, 1024):
      return False

    if not pyvhdi_test_seek_offset_and_read_buffer(
        vhdi_file, read_offset, os.SEEK_SET, read_size,
        read_offset, 1024):
      return False

  # Case 3: test buffer at offset read

  # Test: offset: <media_size / 7> size: <media_size / 2>
  # Expected result: offset: < ( media_size / 7 ) + ( media_size / 2 ) > size: <media_size / 2>
  read_offset, _ = divmod(media_size, 7)
  read_size, _ = divmod(media_size, 2)

  if not pyvhdi_test_read_buffer_at_offset(
      vhdi_file, read_offset, read_size,
      read_offset + read_size, read_size):
    return False

  if not pyvhdi_test_read_buffer_at_offset(
      vhdi_file, read_offset, read_size,
      read_offset + read_size, read_size):
    return False

  return True


def pyvhdi_test_read_file(filename):
  """Tests the read function with a file."""
  vhdi_file = pyvhdi.file()

  vhdi_file.open(filename, "r")

  vhdi_parent_file = None
  if vhdi_file.parent_identifier:
    vhdi_parent_file = pyvhdi.file()

    parent_filename = os.path.join(
      os.path.dirname(filename), vhdi_file.parent_filename)
    vhdi_parent_file.open(parent_filename, "r")

    vhdi_file.set_parent(vhdi_parent_file)

  result = pyvhdi_test_read(vhdi_file)
  vhdi_file.close()

  if vhdi_parent_file:
    vhdi_parent_file.close()

  return result


def pyvhdi_test_read_file_object(filename):
  """Tests the read function with a file-like object."""
  file_object = open(filename, "rb")
  vhdi_file = pyvhdi.file()

  vhdi_file.open_file_object(file_object, "r")

  vhdi_parent_file = None
  if vhdi_file.parent_identifier:
    vhdi_parent_file = pyvhdi.file()

    parent_filename = os.path.join(
      os.path.dirname(filename), vhdi_file.parent_filename)
    vhdi_parent_file.open(parent_filename, "r")

    vhdi_file.set_parent(vhdi_parent_file)

  result = pyvhdi_test_read(vhdi_file)
  vhdi_file.close()

  if vhdi_parent_file:
    vhdi_parent_file.close()

  return result


def pyvhdi_test_read_file_no_open(filename):
  """Tests the read function with a file without open."""
  description = "Testing read of without open:\t"
  print(description, end="")

  vhdi_file = pyvhdi.file()

  error_string = None
  result = False
  try:
    vhdi_file.read(size=4096)
  except Exception as exception:
    error_string = str(exception)
    result = True

  if not result:
    print("(FAIL)")
  else:
    print("(PASS)")

  if error_string:
    print(error_string)
  return result


def main():
  args_parser = argparse.ArgumentParser(
      description="Tests read.")

  args_parser.add_argument(
      "source", nargs="?", action="store", metavar="FILENAME",
      default=None, help="The source filename.")

  options = args_parser.parse_args()

  if not options.source:
    print("Source value is missing.")
    print("")
    args_parser.print_help()
    print("")
    return False

  if not pyvhdi_test_read_file(options.source):
    return False

  if not pyvhdi_test_read_file_object(options.source):
    return False

  if not pyvhdi_test_read_file_no_open(options.source):
    return False

  return True


if __name__ == "__main__":
  if not main():
    sys.exit(1)
  else:
    sys.exit(0)
