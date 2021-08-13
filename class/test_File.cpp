/**
 * test_File.cpp - test the File class
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/13 14:32:25
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
        File file1("./hello/world");
        File file2("../class", "test_File.cpp");
        assert(file1.get_name() == "world");
        assert(file1.get_parent() == "./hello");
        assert(!file1.exists());
        assert(file2.exists());
        cout << file1.get_absolute_path() << endl;
        cout << file2.get_absolute_path() << endl;

        return 0;
}
