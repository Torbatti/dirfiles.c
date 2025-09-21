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

#include "neo.c"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("USAGE: dirfiles [folder path]");
        return -1;
    }
    printf("argc: %d\n", argc);
    printf("cwd: %s\n", argv[0]);
    printf("argv[1]: %s\n", argv[1]);
    printf("len(argv[1]): %d\n", strlen(argv[1]));

    Io_Dir *directory = NULL;
    Io_DirEnt *entry = NULL;
    Io_File file = 0;
    int file_count = 0;

    int diropen_result = dir_open(&directory, argv[1]);
    if (diropen_result == -1)
    {
        printf("error: dir_open failed !");
        return -1;
    }

    int filecreate_result = file_create(&file, "dirfile.txt", 0666);
    if (filecreate_result == -1)
    {
        printf("error: file_create failed !");
        return -1;
    }

    // TODO(AABIB): FIX THIS!!!
    int filewrite_result = file_writeBytes(&file, argv[1], strlen(argv[1]));
    if (filewrite_result == -1)
    {
        printf("error: file_writeBytes failed !");
        return -1;
    }

    while (1)
    {
        filewrite_result = file_writeBytes(&file, "\n", 1);
        if (filewrite_result == -1)
        {
            printf("error: file_writeBytes failed !");
            return -1;
        }

        int diread_result = dir_read(directory, &entry);
        if (diread_result == -1)
        {
            printf("error: dir_read failed !");
            return -1;
        }

        file_count++;
        printf("File %3d: %s\n",
               file_count,
               entry->d_name);

        filewrite_result = file_writeBytes(&file, entry->d_name, strlen(entry->d_name));
        if (filewrite_result == -1)
        {
            printf("error: file_writeBytes failed !");
            return -1;
        }
    }

    int fileclose_result = file_close(&file);
    if (fileclose_result == -1)
    {
        printf("error: file_close failed !");
        return -1;
    }

    int dirclose_result = dir_close(directory);
    if (dirclose_result == -1)
    {
        printf("error: dir_close failed !");
        return -1;
    }

    return 0;
}
