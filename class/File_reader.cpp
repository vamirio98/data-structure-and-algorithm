/**
 * File_reader.cpp - offer the multi-platform basic file read operation
 *
 * Created by Haoyuan Li on 2021/08/18
 * Last Modified: 2021/08/22 23:38:15
 */

#include "File_reader.hpp"
#include "File.hpp"

#include <string>
#include <cstdio>
#include <sys/file.h>
#include <unistd.h>

using std::string;

File_reader::File_reader(const File &file): File_reader(
                file.get_absolute_path())
{
}

File_reader::File_reader(const string &pathname)
{
        fd_ = ::open(pathname.c_str(), O_RDONLY);
        fp_ = fopen(pathname.c_str(), "r");
}

File_reader::~File_reader()
{
        close();
}

bool File_reader::ready()
{
        return fd_ != -1 && fp_ != nullptr;
}

bool File_reader::open(const File &file)
{
        return open(file.get_absolute_path());
}

bool File_reader::open(const string &pathname)
{
        bool state = false;
        fd_ = ::open(pathname.c_str(), O_RDONLY);
        fp_ = fopen(pathname.c_str(), "r");
        if (fd_ != -1 && fp_ != nullptr)
                state = true;
        return state;
}

bool File_reader::close()
{
        bool state = false;
        if (fd_ == -1 || fp_ == nullptr)
                return state;
        if (flock(fd_, LOCK_UN) == 0 && ::close(fd_) == 0 && fclose(fp_) == 0)
                state = true;
        return state;
}

int File_reader::read()
{
        int c;
        flock(fd_, LOCK_SH);
        if ((c = fgetc(fp_)) == EOF)
                c = -1;
        else
                lseek(fd_, 1, SEEK_CUR);
        flock(fd_, LOCK_UN);
        return c;
}

size_t File_reader::read(string &s, const size_t &len)
{
        flock(fd_, LOCK_SH);
        char buf[len + 1];
        auto n = fread(buf, sizeof(char), len, fp_);
        lseek(fd_, n, SEEK_CUR);
        buf[len] = '\0';
        s = buf;
        flock(fd_, LOCK_UN);
        return n;
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
        flock(fd_, LOCK_SH);
        if (lseek(fd_, 0, SEEK_SET) == 0 && fseek(fp_, 0, SEEK_SET) == 0)
                state = true;
        flock(fd_, LOCK_UN);
        return state;
}

off_t File_reader::skip(const off_t &n)
{
        flock(fd_, LOCK_SH);
        auto offset = lseek(fd_, 0, SEEK_CUR);
        auto ret = lseek(fd_, n, SEEK_CUR);
        if (ret == -1) {
                ret = 0;
        } else {
                fseek(fp_, n, SEEK_CUR);
                ret -= offset;
        }
        flock(fd_, LOCK_UN);
        return ret;
}
