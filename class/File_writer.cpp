/**
 * File_writer.cpp - offer the multi-platform basic file write operation
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/22 14:59:32
 */

#include "File_writer.hpp"

#include <string>
#include <sys/file.h>
#include <cstdio>
#include <unistd.h>

using std::string;

File_writer::File_writer(const string &pathname)
{
        fd_ = ::open(pathname.c_str(), O_CREAT | O_WRONLY);
        fp_ = fopen(pathname.c_str(), "r+");
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
        bool state = false;
        fd_ = ::open(pathname.c_str(), O_CREAT | O_WRONLY);
        fp_ = fopen(pathname.c_str(), "r+");
        if (fd_ != -1 && fp_ != nullptr)
                state = true;
        return state;
}

bool File_writer::open(const File &file)
{
        return open(file.get_absolute_path());
}

bool File_writer::close()
{
        bool state = false;
        if (fd_ == -1 || fp_ == nullptr)
                return state;
        if (flock(fd_, LOCK_UN) == 0 && ::close(fd_) == 0 && fclose(fp_) == 0)
                state = true;
        return state;
}

int File_writer::write(const int &c)
{
        int ret = -1;
        flock(fd_, LOCK_EX);
        if (fputc(c, fp_) != EOF) {
                ret = c;
                lseek(fd_, 1, SEEK_CUR);
        }
        flock(fd_, LOCK_UN);
        return ret;
}

size_t File_writer::write(const string &s)
{
        size_t ret = 0;
        flock(fd_, LOCK_EX);
        ret = fwrite(s.c_str(), sizeof(char), s.length(), fp_);
        lseek(fd_, ret, SEEK_CUR);
        flock(fd_, LOCK_UN);
        return ret;
}

size_t File_writer::write(const string &s, const size_t &off, size_t len)
{
        if (len == string::npos)
                len = s.length() - off;
        return write(s.substr(off, len));
}
