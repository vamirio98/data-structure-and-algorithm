/**
 * test_RW.cpp - test the File_reader and File_writer class
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/22 10:11:14
 */

#include "File.hpp"
#include "File_reader.hpp"
#include "File_writer.hpp"

#include <iostream>

using std::string;

int main()
{
        string fname;
        fname = "." + File::separator + "test_RW.txt";

        File f(fname);
        File_writer fw(f);

        for (const auto &c : fname)
                fw.write(c);
        fw.write('\n');
        File_reader fr(f);
        for (long unsigned int i = 0; i < fname.size(); ++i)
                printf("%c\n", fr.read());
        f.remove();
}
