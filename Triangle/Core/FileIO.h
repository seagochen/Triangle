#pragma once
#ifndef _TRI_FILE_IO_H_
#define _TRI_FILE_IO_H_

#include "SysInterfaces.h"
#include "TypeDef.h"
#include "List.h"

#ifdef __cplusplus
extern "C" {
#endif

    // load data from file, in bytes
    // This method will create a backup
    // so you need to pay attention to the memory release 
    // after the end of use.
    EXTERN char* file_read(char const* filename, size_n& size);

    // write data to file, in bytes
    // This method will create a backup
    // so you need to pay attention to the memory release 
    // after the end of use.
    EXTERN void file_write(char const* filename, char * b, size_n size);

    // get the file size
    EXTERN size_n file_size(char const* filepath);

    // does the file exist?
    EXTERN bool_n path_if_exist(char const* path);

    // is path a file?
    EXTERN bool_n path_if_file(char const* path);

    // is path a dir?
    EXTERN bool_n path_if_dir(char const* path);

    // iterate a given path, list all files
    EXTERN list* search_files(char const* path, char const* pattern = "*");

#ifdef __cplusplus
};
#endif

#endif

