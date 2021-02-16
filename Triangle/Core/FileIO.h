#pragma once
#ifndef _TRI_FILE_IO_H_
#define _TRI_FILE_IO_H_

#include "SysInterfaces.h"
#include "TypeDefinition.h"

#include <vector>
#include <string>

namespace sge {

    class FileIO {
    public:
        
        /// <summary>
        /// load data from file, returning in byte array
        /// </summary>
        /// <param name="filename">the path to a file</param>
        /// <param name="node">the reference to a filenode</param>
        EXTERN static const char* read(std::string filename);

        /// <summary>
        /// write data to file, in bytes
        /// </summary>
        /// <param name="filename">the path to a file</param>
        /// <param name="node">the reference to a filenode</param>
        EXTERN static void write(std::string filename, const char* fz);

        /// <summary>
        /// get the file size
        /// </summary>
        /// <param name="filename">the path to a file</param>
        EXTERN static size_n length(std::string filepath);

        /// <summary>
        /// does the file exist?
        /// </summary>
        /// <param name="path">the path to a file or directory</param>
        EXTERN static bool_n is_exist(std::string path);

        /// <summary>
        /// is the path a file?
        /// </summary>
        /// <param name="path">the path to a file</param>        
        EXTERN static bool_n is_file(std::string path);

        /// <summary>
        /// is the path a directory?
        /// </summary>
        /// <param name="path">the path to a directory</param>   
        EXTERN static bool_n is_dir(std::string path);

        /// <summary>
        /// iterate a given path, list all files
        /// </summary>
        /// <param name="path">the path to a directory</param> 
        /// <param name="pattern">searching pattern, the default is *</param> 
        EXTERN static std::vector<std::string>
            search_files(std::string path, std::string pattern = "*");
	};
};




#endif

