#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <string>
#include "List.h"
#include "Validators.h"

char* file_read(char const* filename, size_n& size)
{
    if (filename == nullptr)
    {
        std::cerr << "filename cannot be null or empty" << std::endl;
        return nullptr;
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = file.tellg();
    std::streamoff len = pos;

    // memory allocation
    char* ptr = (char*)malloc(len);

    // read data to ptr
    file.seekg(0, std::ios::beg);
    file.read(ptr, len);

    // file close
    file.close();

    // returning
    size = len;
    return ptr;
}

void file_write(char const* filename, char* b, size_n size)
{
    if (filename == nullptr)
    {
        std::cerr << "filename cannot be null or empty" << std::endl;
        return;
    }

    if (size <= 0 || b == nullptr)
    {
        std::cerr << "data is null or empty" << std::endl;
        return;
    }

    std::fstream file;
    file.open(filename, std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "error while writing to file" << std::endl;
        return;
    }

    file.seekg(0, std::ios::beg);
    file.write(b, size);
    file.close();
}

size_n file_size(char const* filename)
{
    using namespace boost::filesystem;

    path p(filename);
    if (not exists(p) or is_directory(p)) { return -1; }

    // return the file size
    return (size_n) file_size(p);
}

bool_n path_if_exist(char const* dir_path)
{
    using namespace boost::filesystem;

    path p(dir_path);
    return exists(p);
}

bool_n path_if_file(char const* dir_path)
{
    using namespace boost::filesystem;

    path p(dir_path);
    if (not exists(p)) return FALSE;
    return is_regular_file(p);
}

bool_n path_if_dir(char const* dir_path)
{
    using namespace boost::filesystem;

    path p(dir_path);
    if (not exists(p)) return FALSE;
    return is_directory(p);
}

list* search_files(char const* dir_path, char const* pattern) 
{
    using namespace boost::filesystem;

    path p(dir_path);
    if (exists(p) and not is_directory(p)) {
        std::cerr << "invalid path, you must given a folder path" << std::endl;
        return nullptr;
    }

    // the end mark of iterator
    directory_iterator end_itr;

    // create an empty list for data storing
    list* file_list = list_create_empty();

    // cycle through the directory
    for (directory_iterator itr(p); itr != end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            std::string current_file = itr->path().string();

            // basic node
            basic_node* node = nullptr;

            // regular check, * means all files
            if (strcmp(pattern, "*") == 0) {
                node = node_copy_data(current_file.length(), DATA_STRING, current_file.c_str());
            }
            else { // pick up some certain files

                if (reg_contains_pattern(current_file.c_str(), pattern) == TRUE) {
                    node = node_copy_data(current_file.length(), DATA_STRING, current_file.c_str());
                }
                else {
                    node = nullptr;
                }
            }

            if (node != nullptr) { // append the node to list
                list_append(file_list, node);
            }
        }

        else if(is_directory(itr->path())) {
            // search files from sub folders
            list* sub_files = search_files(itr->path().string().c_str(), pattern);

            if (sub_files == nullptr) { // skip
                continue;
            }

            if (list_elements(sub_files) > 0) { // merge list
                list_extend(file_list, sub_files);
            }
            else { // dispose the empty list
                list_dispose(sub_files);
            }
        }
    }

    return file_list;
}