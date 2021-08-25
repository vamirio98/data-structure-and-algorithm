/**
 * File_reader.cpp - offer the multi-platform basic file read operation
 *
 * Created by Haoyuan Li on 2021/08/18
 * Last Modified: 2021/08/25 23:54:42
 */

#include "File_reader.hpp"
#include "File.hpp"

#include <string>
#include <cstdio>
#include <cstdlib>

#if defined(__unix__)

#include <unistd.h>
#include <sys/file.h>

#elif defined(_MSC_VER)

#include <Windows.h>

#endif

using std::string;

File_reader::File_reader(const File &file): File_reader(
                file.get_absolute_path())
{
}

File_reader::File_reader(const string &pathname)
{
        do_open(pathname);
}

File_reader::~File_reader()
{
        close();
}

bool File_reader::open(const File &file)
{
        return open(file.get_absolute_path());
}

bool File_reader::open(const string &pathname)
{
        do_open(pathname);
        return ready();
}

bool File_reader::close()
{
        bool state = false;
        if (!ready())
                return state;
        lock();
#if defined(__unix__)
        if (unlock() && ::close(fd_) == 0 && fclose(fp_) == 0)
                state = true;
#elif defined(_MSC_VER)
        if (unlock() && CloseHandle(h_file_))
                state = true;
#endif
        return state;
}

long long File_reader::skip(const long long &n)
{
        lock();
        long long offset = file_seek(0, FILE_CURRENT);
        long long ret = file_seek(n, FILE_CURRENT);
        ret = (ret == -1) ? 0 : ret - offset;
        unlock();
        return ret;
}

int File_reader::read()
{
        int c;
        lock();
#if defined(__unix__)
        if ((c = fgetc(fp_)) == EOF)
                c = -1;
#elif defined(_MSC_VER)
        DWORD n;
        if (!ReadFile(h_file_, &c, 1, &n, nullptr))
                c = -1;
#endif
        unlock();
        return c;
}

size_t File_reader::read(string &s, const size_t &len)
{
        lock();
        char *buf = new char[len + 1];
        size_t ret = 0;
#if defined(__unix__)
        ret = fread(buf, sizeof(char), len, fp_);
#elif defined(_MSC_VER)
        DWORD n = 0;
        ReadFile(h_file_, buf, len, &n, nullptr);
        ret = n;
#endif
        buf[len] = '\0';
        s = buf;
        delete [] buf;
        unlock();
        return ret;
}

size_t File_reader::read(string &s, const size_t &off, const size_t &len)
{
        string tmp{""};
        size_t ret = read(tmp, len);
        if (s.length() <= off) {
                ret = 0;
        } else {
                s.erase(off);
                s += tmp;
        }
        return ret;
}

bool File_reader::reset_pos()
{
        bool state = false;
        lock();
        if (file_seek(0, FILE_BEGIN) != -1)
                state = true;
        unlock();
        return state;
}
