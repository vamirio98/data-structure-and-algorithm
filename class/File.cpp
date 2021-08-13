/**
 * File.cpp - offer the basic multi-platform file operation
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/13 17:29:49
 */

#include "File.hpp"

#include <string>
#include <sys/stat.h>

#ifdef unix
        #include <cstdlib>
#else // WIN32
        #include <windows.h>
#endif

using string = std::string;

#ifdef unix
        const string File::separator{"/"};
#else // WIN32
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
#ifdef unix
        struct stat s;
        if (stat(pathname.c_str(), &s) == 0)
                state = S_ISREG(s.st_mode);
#else // WIN32
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
#ifdef unix
        struct stat s;
        if (stat(pathname.c_str(), &s) == 0)
                state = S_ISDIR(s.st_mode);
#else // WIN32
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
#ifdef unix
        state = (get_name(pathname)[0] == '.');
#else // WIN32
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
#ifdef unix
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
#else // WIN32
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

string::size_type File::find_last_separator(const string &pathname)
{
        return pathname.find_last_of(separator);
}

string::size_type File::find_last_separator() const
{
        return find_last_separator(pathname_);
}
