#include "myString2.h"
#include <iostream>

using namespace std;

int main() {
    String s1("hello");
    String s2("world");

    String s3(s2);
    cout << s3 << endl;

    s3 = s1;
    cout << s3 << endl;
    cout << s2 << endl;
    cout << s1 << endl;
    String s4 = GetString(s1);
    cout << s4 << endl;

    // String -> char*
    char buf[1024] = {0};
    strcpy_s(buf, s4.get_c_ctr());

    const String s5("HELLO");
    cout << s5[2] << endl;

    const String s6 = "HELLO";

    cout << s6[2] << endl;
    cout << "buf: " << buf << endl;

    String s7 = s5 + s6;
    cout << s7 << endl;

    cout << "s7.length(): " << s7.length() << endl;
    return 0;
}
