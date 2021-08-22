/**
 * test_RW.cpp - test the File_reader and File_writer class
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/22 15:56:12
 */

#include "File.hpp"
#include "File_reader.hpp"
#include "File_writer.hpp"

#include <iostream>

using std::string;
using std::cout;
using std::endl;

int main()
{
        string fname;
        fname = "." + File::separator + "test_RW.txt";
        string txt = "hello world";

        File f(fname);
        File_writer fw(f);

        for (const auto &c : fname)
                fw.write(c);
        fw.write('\n');
        fw.close();

        File_reader fr(f);
        for (long unsigned int i = 0; i < fname.size(); ++i)
                printf("%c", fr.read());
        cout << endl;

        fw.open(f);
        for (const auto &c : txt)
                fw.write(c);
        fw.write('\n');
        fw.write(fname);
        fw.append('c');
        fw.append('\n');
        fw.append(txt, 2);
        fw.write(fname);
        fw.flush();

        fr.reset();
        int c;
        while ((c = fr.read()) != -1)
                printf("%c", c);
        cout << endl;

        fw.close();
        f.remove();
}
