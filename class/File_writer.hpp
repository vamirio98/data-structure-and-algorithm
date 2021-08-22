/**
 * File_writer.hpp - offer the multi-platform basic file write operation
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/21 11:33:28
 */

#ifndef FILE_WRITER_H_
#define FILE_WRITER_H_

#include "File.hpp"

#include <string>
#include <cstdio>
#include <unistd.h>

class File_writer {
private:
        int fd_ = -1;
        FILE *fp_ = nullptr;

public:
        File_writer() = default;
        File_writer(const File_writer &) = delete;
        File_writer &operator=(const File_writer &) = delete;
        ~File_writer();

        /**
         * @brief Create a File_writer object, given the pathname of the file
         *        to write to, create the file if it does not exist
         *
         * @param pathname The pathname of the file
         */
        File_writer(const std::string &pathname);

        /**
         * @brief Create a File_writer object, given the File to write to,
         *        create the file if it does not exist
         *
         * @param file The specified File object
         */
        File_writer(const File &file);

        /**
         * @brief Write a single character
         *
         * @param c Int specifying a character to be written
         *
         * @return The the character written on success and -1 on fail
         */
        int write(const int &c);
};

#endif
