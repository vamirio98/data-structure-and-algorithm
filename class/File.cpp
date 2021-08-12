/**
 * File.cpp - offer the basic multi-platform file operation
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/12 12:57:56
 */

#include "File.hpp"

#include <string>

using string = std::string;

#ifdef unix
        const string File::separator{"/"};
#else // WIN32
        const string File::separator{"\\"};
#endif

File::File(const string &pathname): pathname(pathname)
{
}

File::File(const string &parent, const string &child): pathname(parent + child)
{
}

string File::get_name() const
{
        if (pathname.empty())
                return "";
        auto pos = find_last_separator();
        if (pos != string::npos)
                return pathname.substr(pos + 1);
        return pathname;
}

string File::get_parent() const
{
        if (pathname.empty())
                return "";
        auto pos = find_last_separator();
        if (pos != string::npos)
                return pathname.substr(0, pos);
        return "";
}

string::size_type File::find_last_separator() const
{
        if (pathname.empty())
                return string::npos;
        return pathname.find_last_of(separator);
}
