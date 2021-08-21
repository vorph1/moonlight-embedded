/*
 * This file is part of Moonlight Embedded.
 *
 * Copyright (C) 2017 Iwan Timmer
 *
 * Moonlight is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Moonlight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Moonlight; if not, see <http://www.gnu.org/licenses/>.
 */

#include "util.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int set_int(char *path, int value) {
  int fd = open(path, O_RDWR);
  if(fd >= 0) {

    int length = snprintf( NULL, 0, "%d", value );
    char* str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", value );
    int ret = write(fd, str, length);
    if (ret < 0)
      printf("Failed to set int parameter %s to: %s, error %d!\n", path, str, ret);

    free(str);
    close(fd);
    return 0;
  } else
    return -1;
}

int set_bool(char *path, bool value) {
  int fd = open(path, O_RDWR);

  if(fd >= 0) {
    int ret = write(fd, value ? "1" : "0", 1);
    if (ret < 0)
      printf("Failed to set boolean parameter %s, error %d!\n", path, ret);

    close(fd);
    return 0;
  } else
    return -1;
}

int read_file(char *path, char* output, int output_len) {
  int fd = open(path, O_RDONLY);

  if(fd >= 0) {
    output_len = read(fd, output, output_len);
    close(fd);
    return output_len;
  } else
    return -1;
}