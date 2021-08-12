/**
 * test_File.cpp - test the File class
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/12 22:10:09
 */

#include "File.hpp"
#include <string>
#include <assert.h>

using string = std::string;

int main()
{
        File file1("./hello/world");
        File file2(".", "test_File.cpp");
        assert(file1.get_name() == "world");
        assert(file1.get_parent() == "./hello");
        assert(!file1.exists());
        assert(file2.exists());

        return 0;
}
