#pragma once
#ifndef _TRI_FILE_IO_H_
#define _TRI_FILE_IO_H_

#include "SysInterfaces.h"
#include "TypeDefinition.h"
#include <vector>
#include <string>

namespace sge {

    struct FileNode {
        byte_n* data;
        size_n length;
    };
	
    class FileIO {
    public:
        // load data from file, in bytes
        EXTERN static void read(std::string filename, struct FileNode &node);

        // write data to file, in bytes
        EXTERN static void write(std::string filename, struct FileNode& node);

        // get the file size
        EXTERN static size_n length(std::string filepath);

        // does the file exist?
        EXTERN static bool_n is_exist(std::string path);

        // is path a file?
        EXTERN static bool_n is_file(std::string path);

        // is path a dir?
        EXTERN static bool_n is_dir(std::string path);

        // iterate a given path, list all files
        EXTERN static std::vector<std::string> search_files(std::string path, std::string pattern = "*");
	};
};




#endif

