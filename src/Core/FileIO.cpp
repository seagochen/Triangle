/// c++ standard libraries
#include <iostream>
#include <fstream>
#include <memory>

/// boost libraries
#include <boost/filesystem.hpp>

#include <string>

#include "Core/FileIO.h"
#include "Core/Validators.h"
#include "Core/CommonTool.hpp"
#include "Core/StrUtils.h"

using namespace sge;
using namespace boost;


const char* FileIO::read(std::string filename)
{
    if (not is_file(filename)) {
        throw PTR_ERROR(__FILE__, __LINE__, "Filename cannot be null or empty");
    }

    // get the file length
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = file.tellg();
    std::streamoff len = pos;

    // char ptr to hold the content copied from the given file
    char* fz = (char*) calloc(len + 1, sizeof(char));

    // read data to ptr
    file.seekg(0, std::ios::beg);
    file.read(fz, len);
    file.close();

    // use shared ptr to wrap the original c97 ptr
    return fz;
}


void FileIO::write(std::string filename, const char* fz)
{
    if (fz == nullptr) {
        throw PTR_ERROR(__FILE__, __LINE__, "Data is null");
    }

    std::fstream file;
    file.open(filename, std::ios::out | std::ios::binary);
    if (!file) {
        throw PTR_ERROR(__FILE__, __LINE__, "Error(s) occurs while writing to file");
    }

    // write data to file
    file.seekg(0, std::ios::beg);
    file.write(fz, strlen(fz));
    file.close();
}


bool_n FileIO::mkdir(std::string folderpath)
{
    using namespace boost::filesystem;

    if (not is_exist(folderpath)) {
        path p(folderpath);
        return filesystem::create_directories(p);
    } elif (not is_dir(folderpath)) {
        std::cerr << folderpath << " is exists, but a file" << std::endl;
        return FALSE;
    }
};


size_n FileIO::length(std::string filepath)
{
    using namespace boost::filesystem;

    path p(filepath);
    if (not exists(p) or is_directory(p)) { return -1; }

    // return the file size
    return boost::filesystem::file_size(p);
}

bool_n FileIO::is_exist(std::string path)
{
    using namespace boost::filesystem;

    boost::filesystem::path p(path);
    return exists(p);
}

bool_n FileIO::is_file(std::string path)
{
    using namespace boost::filesystem;

    boost::filesystem::path p(path);
    if (not exists(p)) return FALSE;
    return is_regular_file(p);
}

bool_n FileIO::is_dir(std::string path)
{
    using namespace boost::filesystem;

    boost::filesystem::path p(path);
    if (not exists(p)) return FALSE;
    return is_directory(p);
}

std::vector<std::string> FileIO::search_files(std::string path, std::string pattern)
{
    using namespace boost::filesystem;

    boost::filesystem::path p(path);
    if (exists(p) and not is_directory(p)) {
        throw PTR_ERROR(__FILE__, __LINE__, "Invalid path");
    }

    // the end mark of iterator
    directory_iterator end_itr;

    // create an empty list for data storing
    std::vector<std::string> file_list;

    // cycle through the directory
    for (directory_iterator itr(p); itr != end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            std::string current_file = itr->path().string();

            // regular check, * means all files
            if (strcmp(pattern.c_str(), "*") == 0) {
                file_list.push_back(current_file);
            }
            else { // pick up some certain files

                if (Validator::contains_pattern(current_file.c_str(), pattern.c_str()) == TRUE) {
                    file_list.push_back(current_file);
                }
            }
        }

        else if (is_directory(itr->path())) {
            // search files from sub folders
            std::vector<std::string> sub_files = search_files(itr->path().string().c_str(), pattern);

            if (sub_files.size() <= 0) { // skip
                continue;
            }
            else {
                for (auto file : sub_files) {
                    file_list.push_back(file);
                }
            }
        }
    }

    return file_list;
}
