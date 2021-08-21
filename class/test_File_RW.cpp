/**
 * test_File_RW.cpp - test the File_reader and File_writer class
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/21 10:27:52
 */

#include "File.hpp"
#include "File_reader.hpp"

#include <iostream>

using std::string;
using std::cout;
using std::endl;

int main()
{
        string s;
        s = "." + File::separator + "test_RW.txt";
        File f(s);
        File_reader fr1(f);
        File_reader fr2(s);
        for (int i = 0; i < 5; ++i)
                cout << fr1.read() << endl;
        string s1;
        fr1.read(s1, 6);
        cout << s1 << endl;
        fr1.reset();
        fr1.read(s1, 6);
        cout << s1 << endl;
        fr2.skip(3);
        fr2.read(s1, 6);
        cout << s1 << endl;
}
