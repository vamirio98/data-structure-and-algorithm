/**
 * File.cpp - offer the basic multi-platform file operation
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/13 15:13:33
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

bool File::exists() const
{
        struct stat st;
        return !(stat(pathname_.c_str(), &st));
}

string File::get_name() const
{
        auto pos = find_last_separator();
        if (pos != string::npos)
                return pathname_.substr(pos + 1);
        return pathname_;
}

string File::get_parent() const
{
        auto pos = find_last_separator();
        if (pos != string::npos)
                return pathname_.substr(0, pos);
        return "";
}

string File::get_absolute_path() const
{
        string abs_path{pathname_};
#ifdef unix
        string parent{pathname_};
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

        state = GetFullPathName(pathname_.c_str(), MAX_PATH, buf, nullptr);
        if (state != 0)
                abs_path = string{buf};
#endif
        return abs_path;
}

string::size_type File::find_last_separator(const string &pathname)
{
        return pathname.find_last_of(separator);
}

string::size_type File::find_last_separator() const
{
        return find_last_separator(pathname_);
}
