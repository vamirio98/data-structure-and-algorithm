/**
 * File_reader.cpp - offer the multi-platform basic file read operation
 *
 * Created by Haoyuan Li on 2021/08/18
 * Last Modified: 2021/08/21 10:29:12
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

int File_reader::read() const
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

int File_reader::read(string &s, const int &len) const
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

void File_reader::reset() const
{
        lseek(fd_, 0, SEEK_SET);
        fseek(fp_, 0, SEEK_SET);
}

int File_reader::skip(const int &n) const
{
        auto offset = lseek(fd_, 0, SEEK_CUR);
        auto ret = lseek(fd_, n, SEEK_CUR);
        if (ret == -1) {
                ret = 0;
        } else {
                fseek(fp_, n, SEEK_CUR);
                ret -= offset;
        }
        return ret;
}

void File_reader::open(const File &file)
{
        open(file.get_absolute_path());
}

void File_reader::open(const string &pathname)
{
        fd_ = ::open(pathname.c_str(), O_RDONLY);
        fp_ = fopen(pathname.c_str(), "r");
}

void File_reader::close()
{
        if (fd_ != -1) {
                flock(fd_, LOCK_UN);
                ::close(fd_);
        }
        if (fp_ != nullptr)
                fclose(fp_);
}
