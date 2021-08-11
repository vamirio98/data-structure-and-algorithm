/**
 * test_File.cpp - test the File class
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/12 00:02:10
 */

#include "File.hpp"
#include <string>
#include <assert.h>

using string = std::string;

int main()
{
        string fname{"hello/world"};
        File file(fname);
        assert(string{"world"} == file.get_name());

        return 0;
}
