/**
 * test_RW.cpp - test the File_reader and File_writer class
 *
 * Created by Haoyuan Li on 2021/08/21
 * Last Modified: 2021/08/22 23:38:53
 */

#include "File.hpp"
#include "File_reader.hpp"
#include "File_writer.hpp"

#include <assert.h>
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
        assert(fw.ready());

        for (const auto &c : fname)
                fw.write(c);
        fw.write('\n');
        assert(fw.flush());
        assert(fw.close());

        File_reader fr(f);
        assert(fr.ready());
        cout << "Expect output: " << fname << endl << "Actual output: ";
        for (long unsigned int i = 0; i < fname.size(); ++i)
                printf("%c", fr.read());
        cout << endl;

        assert(fw.open(f));
        assert(fw.clear());
        fw.write(txt, 6);
        fw.close();
        fw.open(f);
        fw.append(' ');
        fw.append(' ');
        fw.append(fname, 2);
        fw.write(fname);
        fw.flush();

        fr.reset_pos();
        string s;
        fr.read(s, txt.substr(6).length() + fname.length());
        cout << "Expect output: " << txt.substr(6) << "  ";
        cout << fname.substr(2) << endl << "Actual output: ";
        cout << s << endl;
        fr.read(s, 6, fname.length());
        cout << "Expect output: " << txt.substr(6) << " ";
        cout << fname << endl << "Actual output: ";
        cout << s << endl;

        fw.close();
        fr.close();
        f.remove();
}
