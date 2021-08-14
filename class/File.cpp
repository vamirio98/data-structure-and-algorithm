/**
 * File.cpp - offer the basic multi-platform file operation
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/14 17:33:45
 */

#include "File.hpp"

#include <string>
#include <sys/stat.h>
#include <ctime>
#include <cstdlib>

#if defined(__unix__)

#include <unistd.h>

#elif defined(_MSC_VER)

#include <windows.h>
#include <io.h>
#define stat _stat
#define access _access
#define R_OK 4
#define W_OK 2
#define X_OK 0

#endif

using string = std::string;

#if defined(__unix__)
        const string File::separator{"/"};
#elif defined(_MSC_VER)
        const string File::separator{"\\"};
#endif

File::File(const string &pathname): pathname_(pathname)
{
}

File::File(const string &parent, const string &child):
        pathname_(parent + separator + child)
{
}

bool File::exists(const string &pathname)
{
        struct stat s;
        return stat(pathname.c_str(), &s) == 0;
}

bool File::exists() const
{
        return exists(pathname_);
}

bool File::is_file(const string &pathname)
{
        bool state{false};
#if defined(__unix__)
        struct stat s;
        if (stat(pathname.c_str(), &s) == 0)
                state = S_ISREG(s.st_mode);
#elif defined(_MSC_VER)
        if(!(GetFileAttributes(pathname.c_str()) & FILE_ATTRIBUTE_DIRECTORY))
                state = true;
#endif
        return state;
}

bool File::is_file() const
{
        return is_file(pathname_);
}

bool File::is_directory(const string &pathname)
{
        bool state{false};
#if defined(__unix__)
        struct stat s;
        if (stat(pathname.c_str(), &s) == 0)
                state = S_ISDIR(s.st_mode);
#elif defined(_MSC_VER)
        if (GetFileAttributes(pathname.c_str()) & FILE_ATTRIBUTE_DIRECTORY)
                state = true;
#endif
        return state;
}

bool File::is_directory() const
{
        return is_directory(pathname_);
}

bool File::is_hidden(const string &pathname)
{
        bool state{false};
#if defined(__unix__)
        state = (get_name(pathname)[0] == '.');
#elif defined(_MSC_VER)
        if (GetFileAttributes(pathname.c_str()) & FILE_ATTRIBUTE_HIDDEN)
                state = true;
#endif
        return state;
}

bool File::is_hidden() const
{
        return is_hidden(pathname_);
}

string File::get_name(const string &pathname)
{
        auto pos = find_last_separator(pathname);
        if (pos != string::npos)
                return pathname.substr(pos + 1);
        return pathname;
}

string File::get_name() const
{
        return get_name(pathname_);
}

string File::get_path() const
{
        return pathname_;
}

string File::get_parent(const string &pathname)
{
        auto pos = find_last_separator(pathname);
        if (pos != string::npos)
                return pathname.substr(0, pos);
        return "";
}

string File::get_parent() const
{
        return get_parent(pathname_);
}

string File::get_absolute_path(const string &pathname)
{
        string abs_path{pathname};
#if defined(__unix__)
        string parent{pathname};
        string child{""};
        char *p;
        while (!parent.empty() && !(p = realpath(parent.c_str(), nullptr))) {
                auto pos = find_last_separator(parent);
                if (pos == string::npos)
                        break;
                child = parent.substr(pos) + child;
                parent = parent.substr(0, pos);
        }
        if (p) {
                abs_path = string{p} + child;
                free(p);
        }
#elif defined(_MSC_VER)
        DWORD state = 0;
        TCHAR buf[MAX_PATH] = TEXT("");

        state = GetFullPathName(pathname.c_str(), MAX_PATH, buf, nullptr);
        if (state != 0)
                abs_path = string{buf};
#endif
        return abs_path;
}

string File::get_absolute_path() const
{
        return get_absolute_path(pathname_);
}

time_t File::last_modified(const string &pathname)
{
        time_t t = 0;
        struct stat s;
        if (stat(pathname.c_str(), &s) == 0)
                t = s.st_mtime;
        return t;
}

time_t File::last_modified() const
{
        return last_modified(pathname_);
}

string File::get_time_str(const time_t &t, const string &format)
{
        struct tm bt;
#if defined(__unix__)
        localtime_r(&t, &tmp);
#elif defined(_MSC_VER)
        localtime_s(&bt, &t);
#endif
        char buf[64];
        strftime(buf, sizeof(buf), format.c_str(), &bt);
        return string{buf};
}

long File::get_size(const string &pathname)
{
        long size = 0;
        struct stat s;
        if (stat(pathname.c_str(), &s) == 0 && is_file(pathname))
                size = s.st_size;
        return size;
}

long File::get_size() const
{
        return get_size(pathname_);
}

bool File::can_read(const string &pathname)
{
        return access(pathname.c_str(), R_OK) == 0;
}

bool File::can_read() const
{
        return can_read(pathname_);
}

bool File::can_write(const string &pathname)
{
        return access(pathname.c_str(), W_OK) == 0;
}

bool File::can_write() const
{
        return can_write(pathname_);
}

bool File::can_execute(const string &pathname)
{
        return access(pathname.c_str(), X_OK) == 0;
}

bool File::can_execute() const
{
        return can_execute(pathname_);
}

string::size_type File::find_last_separator(const string &pathname)
{
        return pathname.find_last_of(separator);
}

string::size_type File::find_last_separator() const
{
        return find_last_separator(pathname_);
}
