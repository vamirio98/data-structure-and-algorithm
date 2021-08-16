/**
 * test_File.cpp - test the File class
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/15 23:12:19
 */

#include "File.hpp"
#include <vector>
#include <string>
#include <assert.h>
#include <iostream>

using std::cout;
using std::endl;

using std::string;

int main()
{
#if defined(__unix__)
        File file1("./hello/world");
        File file2("../class", "test_File.cpp");
        File file3(".bashrc");
        assert(file1.get_parent() == "./hello");
#elif defined(_MSC_VER)
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
#if defined(__unix__)
        assert(file3.is_hidden());
#endif

        assert(file1.get_name() == "world");
        file1.unbind();
        assert(file1.get_name() == "");
#if defined(__unix__)
        file1.bind("./hello/world");
        assert(file1.get_path() == "./hello/world");
#elif defined(_MSC_VER)
        file1.bind(".\\hello\\world");
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
        std::vector<string> v = file1.list();
        for (const auto &s : v)
                cout << s << endl;
        cout << endl;
        v = file2.list();
        for (const auto &s : v)
                cout << s << endl;
        cout << endl;
        v = File(file2.get_parent()).list();
        for (const auto &s : v)
                cout << s << endl;
        cout << endl;
        assert(file1.get_extension() == "");
        assert(file2.get_extension() == "cpp");
        File new_file{"./hello"};
        assert(new_file.create_new_file());
#if defined(__unix__)
        system("ls -l");
#elif defined(_MSC_VER)
        system("dir");
#endif
        assert(new_file.remove());
#if defined(__unix__)
        system("ls -l");
#elif defined(_MSC_VER)
        system("dir");
#endif
        new_file.unbind();
        string s;
#if defined(__unix__)
        s = "./a";
#elif defined(_MSC_VER)
        s = ".\\a";
#endif
        new_file.bind(s);
        assert(new_file.mkdir());
#if defined(__unix__)
        system("ls -l");
#elif defined(_MSC_VER)
        system("dir");
#endif
#if defined(__unix__)
        s = "./b";
#elif defined(_MSC_VER)
        s = ".\\b";
#endif
        assert(new_file.move(s));
        assert(new_file.get_path() == s);
#if defined(__unix__)
        system("ls -l");
#elif defined(_MSC_VER)
        system("dir");
#endif
        assert(new_file.remove());
#if defined(__unix__)
        system("ls -l");
#elif defined(_MSC_VER)
        system("dir");
#endif

        return 0;
}
