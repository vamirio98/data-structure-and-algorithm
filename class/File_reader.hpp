/**
 * File_reader.hpp - offer the multi-platform basic file read operation
 *
 * Created by Haoyuan Li on 2021/08/17
 * Last Modified: 2021/08/26 09:52:50
 */

#ifndef FILE_READER_H_
#define FILE_READER_H_

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

class File_reader {
private:
#if defined(__unix__)
        int fd_ = -1;
        FILE *fp_ = nullptr;
#elif defined(_MSC_VER)
        HANDLE h_file_{INVALID_HANDLE_VALUE};
        OVERLAPPED overlapped_{0};
#endif

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
         * @brief Read a single char, while reading from a file, other read
         *        requests are allowed but other write requests will be
         *        blocked
         *
         * @return The character read, or -1 if the end of the stream has been
         *         reached
         */
        int read();

        /**
         * @brief Read characters into a string, while reading from a file,
         *        other read requests are allowed but other write requests
         *        will be blocked
         *
         * @param s The string used to store the characters read
         * @param len Maximum number of characters to read
         *
         * @return The total number of bytes successfully read
         */
        size_t read(std::string &s, const size_t &len);

        /**
         * @brief Read characters into a portion of a string, while reading
         *        from a file, other read requests are allowed but other
         *        write requests will be blocked
         *
         * @param s The string used to store the characters read
         * @param off Offset at which to start storing characters
         * @param len Maximum number of characters to read
         *
         * @return The total number of bytes successfully read
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
        long long skip(const long long &n);

private:
        /**
         * @brief Open a file to read
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
};

inline bool File_reader::ready()
{
#if defined(__unix__)
        return fd_ != -1 && fp_ != nullptr;
#elif defined(_MSC_VER)
        return h_file_ != INVALID_HANDLE_VALUE;
#endif
}

inline void File_reader::do_open(const std::string &pathname)
{
#if defined(__unix__)
        fd_ = ::open(pathname.c_str(), O_RDONLY);
        fp_ = fopen(pathname.c_str(), "r");
#elif defined(_MSC_VER)
        h_file_ = CreateFile(pathname.c_str(),
                        GENERIC_READ,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        nullptr,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        nullptr);
#endif
}

inline bool File_reader::lock()
{
#if defined(__unix__)
        return flock(fd_, LOCK_SH) == 0;
#elif defined(_MSC_VER)
        return LockFileEx(h_file_, 0, 0,
                        MAXDWORD, MAXDWORD, &overlapped_);
#endif
}

inline bool File_reader::unlock()
{
#if defined(__unix__)
        return flock(fd_, LOCK_UN) == 0;
#elif defined(_MSC_VER)
        return UnlockFileEx(h_file_, 0, MAXDWORD, MAXDWORD, &overlapped_);
#endif
}

inline long long File_reader::file_seek(const long long &offset,
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
