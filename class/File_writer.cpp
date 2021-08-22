/**
 * File_writer.cpp - offer the multi-platform basic file write operation
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/21 11:38:58
 */

#include "File_writer.hpp"

#include <string>
#include <sys/file.h>
#include <cstdio>
#include <unistd.h>

using std::string;

File_writer::File_writer(const string &pathname)
{
        fd_ = open(pathname.c_str(), O_CREAT | O_WRONLY);
        fp_ = fopen(pathname.c_str(), "r+");
}

File_writer::File_writer(const File &file):
        File_writer(file.get_absolute_path())
{
}

File_writer::~File_writer()
{
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
