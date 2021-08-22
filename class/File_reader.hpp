/**
 * File_reader.hpp - offer the multi-platform basic file read operation
 *
 * Created by Haoyuan Li on 2021/08/17
 * Last Modified: 2021/08/22 23:38:17
 */

#ifndef FILE_READER_H_
#define FILE_READER_H_

#include "File.hpp"

#include <string>
#include <cstdio>
#include <unistd.h>

class File_reader {
private:
        int fd_ = -1;
        FILE *fp_ = nullptr;

public:
        File_reader() = default;
        File_reader(const File_reader &) = delete;
        File_reader &operator=(const File_reader &) = delete;
        ~File_reader();

        /**
         * @brief Create a File_reader object, given the File to read from
         *
         * @param file The specified File object
         */
        File_reader(const File &file);

        /**
         * @brief Create a File_reader object, given the pathname of the file
         *        to read from
         *
         * @param pathname The pathname of the file
         */
        File_reader(const std::string &pathname);

        /**
         * @brief Tell if this stream is ready to be read
         *
         * @return True if the file opened successfully, false otherwise
         */
        bool ready();

        /**
         * @brief Open the given File object
         *
         * @param file The specified File object
         *
         * @return True if succeeded and false if failed
         *
         * @sa close()
         */
        bool open(const File &file);

        /**
         * @brief Open the given pathname
         *
         * @param pathname The specified pathname
         *
         * @return True if succeeded and false if failed
         *
         * @sa close()
         */
        bool open(const std::string &pathname);

        /**
         * @brief Close the File_reader object
         *
         * @return True if succeeded and false if failed
         *
         * @sa open()
         */
        bool close();

        /**
         * @brief Read a single char, allow multiple File_reader objects to
         *        read the same file at the same time while no File_writer
         *        object is used for writing
         *
         * @return The character read, or -1 if the end of the stream has been
         *         reached
         */
        int read();

        /**
         * @brief Read characters into a string, allow multiple File_reader
         *        objects to read the same file at the same time while no
         *        File_writer object is used for writing
         *
         * @param s The string used to store the characters read
         * @param len Maximum number of characters to read
         *
         * @return The number of characters read, or -1 if the end of the
         *         stream has been reached
         */
        size_t read(std::string &s, const size_t &len);

        /**
         * @brief Read characters into a portion of a string, allow multiple
         *        File_reader objects to read the same file at the same time
         *        while no File_writer object is used for writing
         *
         * @param s The string used to store the characters read
         * @param off Offset at which to start storing characters
         * @param len Maximum number of characters to read
         *
         * @return The number of characters read, or -1 if the end of the
         *         stream has been reached
         */
        size_t read(std::string &s, const size_t &off, const size_t &len);

        /**
         * @brief Reset the postion indicator associated with the file stream
         *
         * @return True if succeeded and false if failed
         */
        bool reset_pos();

        /**
         * @brief Skip characters
         *
         * @param n The number of characters to skip
         *
         * @return The number of characters actually skipped
         */
        off_t skip(const off_t &n);
};

#endif
