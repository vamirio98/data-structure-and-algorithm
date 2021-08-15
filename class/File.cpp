/**
 * File.cpp - offer the basic multi-platform file operation
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/15 22:58:59
 */

#include "File.hpp"

#include <vector>
#include <string>
#include <sys/stat.h>
#include <ctime>
#include <cstdlib>

#if defined(__unix__)

#include <unistd.h>
#include <dirent.h>

#elif defined(_MSC_VER)

#include <windows.h>
#include <io.h>
#define stat _stat
#define access _access
#define R_OK 4
#define W_OK 2
#define X_OK 0

#endif

using std::string;

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

void File::bind(const string &pathname)
{
        pathname_ = pathname;
}

void File::unbind()
{
        pathname_.clear();
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
        localtime_r(&t, &bt);
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

std::vector<string> File::list(const string &pathname)
{
        std::vector<string> filelist;
#if defined(__unix__)
        DIR *dp;
        struct dirent *p;
        do {
                if ((dp = opendir(pathname.c_str())) == nullptr)
                        break;
                while ((p = readdir(dp)))
                        filelist.push_back(p->d_name);
                closedir(dp);
        } while (0);
#elif defined(_MSC_VER)
        WIN32_FIND_DATA ffd;
        HANDLE h_find = INVALID_HANDLE_VALUE;
        do {
                h_find = FindFirstFile((pathname + separator + "*").c_str(), &ffd);
                if (h_find == INVALID_HANDLE_VALUE)
                        break;
                do {
                        filelist.push_back(ffd.cFileName);
                } while (FindNextFile(h_find, &ffd));
                FindClose(h_find);
        } while (0); 
#endif
        return filelist;
}

string File::get_extension(const string &pathname)
{
        string ext{""};
        auto spos = find_last_separator(pathname);
        auto dpos = pathname.find_last_of(".");
        if (dpos != string::npos && dpos != 0 && (spos == string::npos ||
                                dpos > spos))
                ext = pathname.substr(dpos + 1);
        return ext;
}

string File::get_extension() const
{
        return get_extension(pathname_);
}

std::vector<string> File::list() const
{
        return list(pathname_);
}

bool File::create_new_file(const string &pathname)
{
        bool state = false;
        if (exists(pathname))
                return state;
        auto p = fopen(pathname.c_str(), "w");
        if (p) {
                fclose(p);
                state = true;
        }
        return state;
}

bool File::create_new_file()
{
        return create_new_file(pathname_);
}

bool File::remove(const string &pathname)
{
        bool state = false;
        if (!exists(pathname))
                return state;
        state = ::remove(pathname.c_str()) == 0;
        return state;
}

bool File::remove()
{
        return remove(pathname_);
}

bool File::mkdir(const string &pathname, mode_t mode)
{
        return ::mkdir(pathname.c_str(), mode) == 0;
}

bool File::mkdir(mode_t mode)
{
        return mkdir(pathname_, mode);
}

string::size_type File::find_last_separator(const string &pathname)
{
        return pathname.find_last_of(separator);
}

string::size_type File::find_last_separator() const
{
        return find_last_separator(pathname_);
}
