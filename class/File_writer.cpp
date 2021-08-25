/**
 * File_writer.cpp - offer the multi-platform basic file write operation
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/25 23:15:25
 */

#include "File_writer.hpp"

#include <string>
#include <cstdio>

#if defined(__unix__)

#include <unistd.h>
#include <sys/file.h>

#elif defined(_MSC_VER)

#include <Windows.h>

#endif

using std::string;

File_writer::File_writer(const string &pathname)
{
        do_open(pathname);
        pathname_ = pathname;
}

File_writer::File_writer(const File &file):
        File_writer(file.get_absolute_path())
{
}

File_writer::~File_writer()
{
        close();
}

bool File_writer::open(const string &pathname)
{
        do_open(pathname);
        pathname_ = pathname;
        return ready();
}

bool File_writer::open(const File &file)
{
        return open(file.get_absolute_path());
}

bool File_writer::close()
{
        bool state = false;
        if (!ready())
                return state;
        lock();
        flush();
        pathname_ = "";
#if defined(__unix__)
        if (unlock() && ::close(fd_) == 0 && fclose(fp_) == 0)
                state = true;
#elif defined(_MSC_VER)
        if (unlock() && CloseHandle(h_file_))
                state = true;
#endif
        return state;
}

long long File_writer::skip(const long long &n)
{
        lock();
        long long offset = file_seek(0, FILE_CURRENT);
        long long ret = file_seek(n, FILE_CURRENT);
        ret = (ret == -1) ? 0 : ret - offset;
        unlock();
        return ret;
}

int File_writer::write(const int &c)
{
        int ret = -1;
        lock();
#if defined(__unix__)
        if (fputc(c, fp_) != EOF)
                ret = c;
#elif defined(_MSC_VER)
        DWORD n;
        if (WriteFile(h_file_, &c, 1, &n, nullptr))
                ret = c;
#endif
        unlock();
        return ret;
}

size_t File_writer::write(const string &s)
{
        size_t ret = 0;
        lock();
#if defined(__unix__)
        ret = fwrite(s.c_str(), sizeof(char), s.length(), fp_);
#elif defined(_MSC_VER)
        DWORD n = 0;
        if (WriteFile(h_file_, s.c_str(), s.length(), &n, nullptr))
                ret = n;
#endif
        unlock();
        return ret;
}

size_t File_writer::write(const string &s, const size_t &off, size_t len)
{
        if (len == string::npos)
                len = s.length() - off;
        return write(s.substr(off, len));
}

int File_writer::append(const char &c)
{
        int ret = -1;
        lock();
#if defined(__unix__)
        file_seek(0, FILE_END);
        if (fputc(c, fp_) != EOF)
                ret = c;
#elif defined(_MSC_VER)
        file_seek(0, FILE_END);
        DWORD n;
        if (WriteFile(h_file_, &c, 1, &n, nullptr))
                ret = c;
#endif
        unlock();
        return ret;
}

size_t File_writer::append(const string &s)
{
        size_t ret = 0;
        lock();
#if defined(__unix__)
        file_seek(0, FILE_END);
        ret = fwrite(s.c_str(), sizeof(char), s.length(), fp_);
#elif defined(_MSC_VER)
        DWORD n = 0;
        if (WriteFile(h_file_, s.c_str(), s.length(), &n, nullptr))
                ret = n;
#endif
        unlock();
        return ret;
}

size_t File_writer::append(const string &s, const size_t &off, size_t len)
{
        if (len == string::npos)
                len = s.length() - off;
        return append(s.substr(off, len));
}

bool File_writer::clear()
{
        bool state = false;
        string s = pathname_;
        if (close()) {
#if defined(__unix__)
                FILE *fp = fopen(s.c_str(), "w");
                if (fp)
                        state = (fclose(fp) == 0) ? open(s) : false;
#elif defined(_MSC_VER)
                HANDLE h_file = INVALID_HANDLE_VALUE;
                h_file = CreateFile(s.c_str(),
                                GENERIC_WRITE,
                                FILE_SHARE_READ | FILE_SHARE_WRITE,
                                nullptr,
                                CREATE_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
                                nullptr);
                if (h_file != INVALID_HANDLE_VALUE)
                        state = (CloseHandle(h_file) != 0) ? open(s) : false;
#endif
        }
        return state;
}
