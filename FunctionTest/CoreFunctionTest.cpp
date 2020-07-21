#include <Core/Core.hpp>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace sge;

void ConverterTest() {
    cout << Converter::str_to_int("11") << endl;
    cout << Converter::str_to_long("134598755687") << endl;
    cout << Converter::str_to_float("11.3") << endl;
    cout << Converter::str_to_double("11.3") << endl;

    cout << "-----------------" << endl;

    string str;
    Converter::int_to_str(147, str); cout << str << endl;
    Converter::long_to_str(13245678313, str); cout << str << endl;
    Converter::float_to_str(123.41f, str); cout << str << endl;
    Converter::double_to_str(12.221354567, str); cout << str << endl;

    cout << "----------------" << endl;

    byte_n* bytes = Converter::itob(19);
    cout << Converter::btoi(bytes) << endl;

    bytes = Converter::ltob(17452456248);
    cout << Converter::btol(bytes) << endl;

    bytes = Converter::ftob(13.0);
    cout << Converter::btof(bytes) << endl;

    bytes = Converter::dtob(13.0);
    cout << Converter::btod(bytes) << endl;
}

void FileIOTest() {
    string file = "D:\\OneDrive\\Triangle\\README.md";
    string dir = "D:\\OneDrive\\Triangle";
    
    cout << "is exist:" << FileIO::is_exist(dir)
        << "\tis file:" << FileIO::is_file(file) 
        << "\tis dir:" << FileIO::isDir(file) << endl;

    // read and write file
    FileNode node = { 0 };
    FileIO::read(file, node);
    string str((const char*)node.data, node.length);
    FileIO::write("D:\\OneDrive\\Triangle\\output.txt", node);

    // read file size
    cout << "file size:" << FileIO::length(file) << endl;
    
    // search files
    vector<string> files = FileIO::search_files(dir);
    for (auto f : files) {
        cout << f << endl;
    }
}

void HashCodeTest() {
    string testmsg = "Mary has a little sheep, she loves the sheep very much.";

    cout << "SHA256: " << HashCode::sha256(testmsg.c_str(), testmsg.length()) << endl;
    cout << "SHA1: " << HashCode::sha1(testmsg.c_str(), testmsg.length()) << endl;
    cout << "MD5: " << HashCode::md5(testmsg.c_str(), testmsg.length()) << endl;
}

void StrUtilsTest() {
    vector<string> tokens;
    for (auto s : StringUtils::split("192.168.12.1", ".", tokens)) {
        cout << s << "\t";
    }
    cout << endl << "----------------" << endl;

    cout << StringUtils::format("hello %s ", "world") << endl;
    cout << "----------------" << endl;

    string test = "     test    ";
    cout << StringUtils::trim(test) << endl;
    cout << "----------------" << endl;
}

void TimerTest() {
    cout << "since1970:" << Timer::since1970() << endl;
    cout << "start timer\n";
    Timer t;
    t.start();
    Sleep(1000);
    cout << "end timer: " << t.stop() << endl;
}

void ValidatorTest() {
    cout << Validator::match_email("hello@px.com") << endl;
    cout << Validator::match_phone("abcdefg") << endl;
    cout << Validator::match_ipv4("137.1.2.3") << endl;
}

//int main() {
//
//    ConverterTest();
//    cout << "Converter test done" << endl;
//
//    FileIOTest();
//    cout << "FileIO test done" << endl;
//
//    HashCodeTest();
//    cout << "HashCode test done" << endl;
//    
//    StrUtilsTest();
//    cout << "StrUtils test done" << endl;
//
//    TimerTest();
//    cout << "Timer test done" << endl;
//
//    ValidatorTest();
//    cout << "Validator test done" << endl;
//    return 0;
//}
