/**
 * test_File.cpp - test the File class
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/14 16:39:06
 */

#include "File.hpp"
#include <string>
#include <assert.h>
#include <iostream>

using std::cout;
using std::endl;

using string = std::string;

int main()
{
#ifdef unix
        File file1("./hello/world");
        File file2("../class", "test_File.cpp");
        File file3(".bashrc");
        assert(file1.get_parent() == "./hello");
#else // WIN32
        File file1(".\\hello\\world");
        File file2("..\\class", "test_File.cpp");
        assert(file1.get_parent() == ".\\hello");
#endif

        assert(!file1.exists());
        assert(file2.exists());
        assert(file2.is_file());
        assert(!file2.is_directory());
        assert(File{file2.get_parent()}.is_directory());
        assert(!file2.is_hidden());
#ifdef unix
        assert(file3.is_hidden());
#endif

        assert(file1.get_name() == "world");
#ifdef unix
        assert(file1.get_path() == "./hello/world");
#else // WIN32
        assert(file1.get_path() == ".\\hello\\world");
#endif
        cout << file1.get_absolute_path() << endl;
        cout << file2.get_absolute_path() << endl;
        cout << File::get_time_str(file2.last_modified()) << endl;
        cout << file1.get_size() << endl;
        cout << file2.get_size() << endl;
        assert(!file1.can_read());
        assert(!file1.can_write());
        assert(!file1.can_execute());
        assert(file2.can_read());
        assert(file2.can_write());
        assert(File(file2.get_parent()).can_execute());

        return 0;
}
