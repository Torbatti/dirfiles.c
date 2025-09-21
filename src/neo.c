/*
 * Copyright (c) 2025 Arya Bakhtiari
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
// #include <sys/mman.h>

typedef unsigned int Io_File;

int
file_open(Io_File *file, const char *path, int flags)
{
    int open_result = open(path, flags);
    if (open_result == -1)
    {
        return -1;
    }

    *file = (unsigned int)open_result;

    return 0;
}

int
file_create(Io_File *file, const char *path, int perms)
{
    int open_result = open(path, O_WRONLY | O_APPEND | O_CREAT, perms);
    if (open_result == -1)
    {
        return -1;
    }

    *file = (unsigned int)open_result;

    return 0;
}

int
file_readByte(Io_File *file)
{
    char buf[1];
    int read_result = read(*file, buf, 1);
    if (read_result == -1)
    {
        printf("errno: %d", errno);
        return -1;
    }

    return buf[0];
}

int
file_readBytes(Io_File *file, char *buf, int max_read)
{
    int read_result = read(*file, buf, max_read);
    if (read_result == -1)
    {
        printf("errno: %d", errno);
        return -1;
    }

    return read_result;
}

int
file_writeBytes(Io_File *file, char *buf, int max_write)
{
    int write_result = write(*file, buf, max_write);
    if (write_result == -1)
    {
        return -1;
    }

    return write_result;
}

long
file_size(Io_File *file)
{
    struct stat file_stat;

    int fstat_result = fstat(*file, &file_stat);
    if (fstat_result == -1)
    {
        return -1;
    }

    return file_stat.st_size;
}

int
file_close(Io_File *file)
{
    int close_result = close(*file);
    if (close_result == -1)
    {
        return -1;
    }

    *file = 0;
    return 0;
}

typedef DIR Io_Dir;
typedef struct dirent Io_DirEnt;

int
dir_open(Io_Dir **dir, const char *path)
{
    *dir = opendir(path);
    if (*dir == NULL)
    {
        return -1;
    }
    return 0;
}

int
dir_read(Io_Dir *dir, Io_DirEnt **entry)
{
    *entry = readdir(dir);
    if (*entry == NULL)
    {
        return -1;
    }
    return 0;
}

int
dir_close(Io_Dir *dir)
{
    int close_result = closedir(dir);
    if (close_result == -1)
    {
        return -1;
    }
    return 0;
}
