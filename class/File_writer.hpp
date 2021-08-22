/**
 * File_writer.hpp - offer the multi-platform basic file write operation
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/22 15:53:50
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
         * @brief Open a file to write
         *
         * @param pathname The pathname of the file
         *
         * @return Ture if successed and false if failed
         *
         * @sa close()
         */
        bool open(const std::string &pathname);

        /**
         * @brief Open a file to write
         *
         * @param file The file object
         *
         * @return Ture if successed and false if failed
         *
         * @sa close()
         */
        bool open(const File &file);

        /**
         * @brief Close the File_writer object
         *
         * @return Ture if successed and false if failed
         *
         * @sa open()
         */
        bool close();

        /**
         * @brief Write a single character, when writing to a file, the other
         *        read and write requests to it will be blocked
         *
         * @param c Int specifying a character to be written
         *
         * @return The the character written on success and -1 on fail
         */
        int write(const int &c);

        /**
         * @brief Write a string
         *
         * @param s The string
         *
         * @return The total number of characters successfully written
         */
        size_t write(const std::string &s);

        /**
         * @brief Write a portion of a string
         *
         * @param s The string
         * @param off Offset from which to start writing characters
         * @param len Number of characters to write, default remainder
         *
         * @return The total number of characters successfully written
         */
        size_t write(const std::string &s, const size_t &off,
                        size_t len = std::string::npos);

        /**
         * @brief Append the specified character to the file, after this
         *        operation, all the new characters written by write() will
         *        be appended to the end
         *
         * @param c The character to append
         *
         * @return The the character appended on success and -1 on fail
         */
        int append(const char &c);

        /**
         * @brief Append a string, after this operation, all the new characters
         * written by write() will be appended to the end
         *
         * @param s The string
         *
         * @return The total number of characters successfully written
         */
        size_t append(const std::string &s);

        /**
         * @brief Append a portion of string, after this operation, all the
         *        new characters written by write() will be appended to the end
         *
         * @param s The string
         * @param off Offset from which to start writing characters
         * @param len Number of characters to write, default remainder
         *
         * @return The total number of characters successfully written
         */
        size_t append(const std::string &s, const size_t &off,
                        size_t len = std::string::npos);

        /**
         * @brief Flush the stream buffer
         *
         * @return Ture if successed and false if failed
         */
        bool flush();
};

#endif
