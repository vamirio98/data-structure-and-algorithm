/**
 * File_writer.hpp - offer the multi-platform basic file write operation
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/26 00:13:46
 */

#ifndef FILE_WRITER_H_
#define FILE_WRITER_H_

#include "File.hpp"

#include <string>
#include <cstdio>

#if defined(__unix__)

#include <unistd.h>
#include <sys/file.h>

#define FILE_BEGIN SEEK_SET
#define FILE_CURRENT SEEK_CUR
#define FILE_END SEEK_END

#elif defined(_MSC_VER)

#include <Windows.h>

#endif

class File_writer {
private:
#if defined(__unix__)
        int fd_{-1};
        FILE *fp_{nullptr};
#elif defined(_MSC_VER)
        HANDLE h_file_{INVALID_HANDLE_VALUE};
        OVERLAPPED overlapped_{0};
#endif
        std::string pathname_{""};

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
         * @brief Tell if this stream is ready to be written
         *
         * @return True if the file opened successfully, false otherwise
         */
        bool ready();

        /**
         * @brief Open a file to write
         *
         * @param pathname The pathname of the file
         *
         * @return True if succeeded and false if failed
         *
         * @sa close()
         */
        bool open(const std::string &pathname);

        /**
         * @brief Open a file to write
         *
         * @param file The file object
         *
         * @return True if succeeded and false if failed
         *
         * @sa close()
         */
        bool open(const File &file);

        /**
         * @brief Close the File_writer object
         *
         * @return True if succeeded and false if failed
         *
         * @sa open()
         */
        bool close();

        /**
         * @brief Set read/write file offset
         *
         * @param offset The number of bytes to move the file pointer
         * @param origin The position used as reference for the @offset, can
         *        be one of the following values: FILE_BEGIN, FILE_CURRENT,
         *        FILE_END
         *
         * @return The resulting offset location as measured in bytes from the
         *         beginning of the file when succeeded, -1 otherwise
         */
        long long file_seek(const long long &offset, const int &origin);

        /**
         * @brief Skip characters
         *
         * @param n The number of characters to skip
         *
         * @return The number of characters actually skipped
         */
        long long skip(const long long &n);

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
         * @return True if succeeded and false if failed
         */
        bool flush();

        /**
         * @brief Clear the whole contents of the file
         *
         * @return True if succeeded and false if failed
         */
        bool clear();

private:
        /**
         * @brief Open a file to write
         *
         * @param pathname The pathname of the file
         */
        void do_open(const std::string &pathname);

        /**
         * @brief Lock the file
         *
         * @return True if lock successfully, false otherwise
         */
        bool lock();

        /**
         * @brief Unlock the file
         *
         * @return True if unlock successfully, false otherwise
         */
        bool unlock();
};

inline bool File_writer::ready()
{
#if defined(__unix__)
        return fd_ != -1 && fp_ != nullptr;
#elif defined(_MSC_VER)
        return h_file_ != INVALID_HANDLE_VALUE;
#endif
}

inline bool File_writer::flush()
{
#if defined(__unix__)
        return fflush(fp_) == 0;
#elif defined(_MSC_VER)
        return FlushFileBuffers(h_file_);
#endif
}

inline void File_writer::do_open(const std::string &pathname)
{
#if defined(__unix__)
        fd_ = ::open(pathname.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        fp_ = fopen(pathname.c_str(), "r+");
#elif defined(_MSC_VER)
        h_file_ = CreateFile(pathname.c_str(),
                        GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        nullptr,
                        OPEN_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        nullptr);
        overlapped_.Offset = 0;
        overlapped_.OffsetHigh = 0;
#endif
}

inline bool File_writer::lock()
{
#if defined(__unix__)
        return flock(fd_, LOCK_EX) == 0;
#elif defined(_MSC_VER)
        return LockFileEx(h_file_, LOCKFILE_EXCLUSIVE_LOCK, 0,
                        MAXDWORD, MAXDWORD, &overlapped_);
#endif
}

inline bool File_writer::unlock()
{
#if defined(__unix__)
        return flock(fd_, LOCK_UN) == 0;
#elif defined(_MSC_VER)
        return UnlockFileEx(h_file_, 0, MAXDWORD, MAXDWORD, &overlapped_);
#endif
}

inline long long File_writer::file_seek(const long long &offset,
                const int &origin)
{
        long long pos = -1;
#if defined(__unix__)
        if (fseek(fp_, offset, origin) == 0)
                pos = ftell(fp_);
#elif defined(_MSC_VER)
        LARGE_INTEGER l;
        l.QuadPart = offset;
        l.LowPart = SetFilePointer(h_file_, static_cast<LONG>(l.LowPart),
                        &(l.HighPart), static_cast<DWORD>(origin));
        if (l.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
                l.QuadPart = -1;
        pos = l.QuadPart;
#endif
        return pos;
}

#endif
