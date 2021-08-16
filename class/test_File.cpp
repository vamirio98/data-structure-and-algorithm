/**
 * test_File.cpp - test the File class
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/16 13:21:35
 */

#include "File.hpp"
#include <vector>
#include <string>
#include <assert.h>
#include <iostream>

using std::cout;
using std::endl;

using std::string;

void ls(const string &arg)
{
#if defined(__unix__)
        system((string{"ls -l "} + arg).c_str());
#elif defined(_MSC_VER)
        system((string{"dir "} + arg).c_str());
#endif
}

int main(int argc, char **argv)
{
        string s1;
        string ts1;
        string s2{"test_File.cpp"};
        string s3;
#if defined(__unix__)
        s1 = "./hello/world";
        ts1 = "./hello";
        s3 = "~/.bashrc";
        File f2("../class", s2);
#elif defined(_MSC_VER)
        s1 = ".\\hello\\world";
        ts1 = ".\\hello";
        s3 = "..\\.git";
        File f2("..\\class", s2);
#endif

        File f1(s1);
        assert(f1.get_parent() == ts1);
        assert(!f1.exists());
        assert(f2.exists());
        assert(f2.is_file());
        assert(!f2.is_directory());
        assert(File{f2.get_parent()}.is_directory());
        assert(!f2.is_hidden());

        File f3(s3);
        assert(f3.is_hidden());

        assert(f1.get_name() == "world");
        f1.unbind();
        assert(f1.get_name() == "");
        f1.bind(s1);
        assert(f1.get_path() == s1);

        cout << "The absolute path of " << f1.get_path() << " is " <<
                f1.get_absolute_path() << endl << endl;
        cout << "The absolute path of " << f2.get_path() << " is " <<
                f2.get_absolute_path() << endl << endl;

        cout << "The last modified time of " << f2.get_path() << " is " <<
                File::get_time_str(f2.last_modified()) << endl << endl;

        cout << "The size of " << f1.get_path() << " is " << f1.get_size()
                << " bytes" << endl << endl;
        cout << "The size of " << f2.get_path() << " is " << f2.get_size()
                << " bytes" << endl << endl;

        assert(!f1.can_read());
        assert(!f1.can_write());
        assert(!f1.can_execute());
        assert(f2.can_read());
        assert(f2.can_write());
        assert(File(argv[0]).can_execute());
        assert(File(f2.get_parent()).can_execute());

        cout << "Expected: nothing" << endl;
        for (const auto &s : f1.list())
                cout << s << " ";
        cout << endl << endl;

        cout << "Expected: nothing" << endl;
        for (const auto &s : f2.list())
                cout << s << " ";
        cout << endl << endl;

        cout << "Expected: all files in this directory" << endl;
        for (const auto &s : File(f2.get_parent()).list())
                cout << s << " ";
        cout << endl << endl;

        assert(f1.get_extension() == "");
        assert(f2.get_extension() == "cpp");

        string s4;
#if defined(__unix__)
        s4 = "./hello";
#elif defined(_MSC_VER)
        s4 = ".\\hello";
#endif

        File f4{s4};
        assert(f4.create_new_file());
        cout << "Expected: information of file " << s4 << endl;
        ls(s4);
        cout << endl;

#if defined(__unix__)
        s4 = "./world";
#elif defined(_MSC_VER)
        s4 = ".\\world";
#endif

        assert(f4.move(s4));
        cout << "Expected: information of file " << s4 << endl;
        ls(s4);
        cout << endl;

        assert(f4.remove());
        cout << "Expected: no file named " << s4 << endl;
        ls(s4);
        cout << endl;

        f4.unbind();

#if defined(__unix__)
        s4 = "./a";
#elif defined(_MSC_VER)
        s4 = ".\\a";
#endif

        f4.bind(s4);
        assert(f4.mkdir());
        cout << "Expected: information of directory " << s4 << endl;
        ls(s4);
        cout << endl;

#if defined(__unix__)
        s4 = "./b";
#elif defined(_MSC_VER)
        s4 = ".\\b";
#endif
        assert(f4.move(s4));
        assert(f4.get_path() == s4);
        cout << "Expected: information of directory " << s4 << endl;
        ls(s4);
        cout << endl;

        assert(f4.remove());
        cout << "Expected: no file named " << s4 << endl;
        ls(s4);
        cout << endl;

        return 0;
}
