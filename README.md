# README

Triangle is a portable, easy to use library, which are common tools or pieces of code adopted from my other projects. You are welcome to use this project to help you quickly develop a portable C++ project, able to run on both Windows, Mac OSX, and Linux system.

What features are Triangle currently available:
* data container, list (array), dictionary map (also known as hash map), binary trees etc.
* encapsulated TCP/UDP APIs.
* system file IOs, to find, search, write and read data.
* HASH coding, supports MD5, SHA-1.
* host information.

# Prerequire

* C++14;
* boost 1.7; 
* libuv;

# Examples

## Converter

```cpp
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

    byte_n *bytes = Converter::itob(19);
    cout << Converter::btoi(bytes) << endl;

    bytes = Converter::ltob(17452456248);
    cout << Converter::btol(bytes) << endl;

    bytes = Converter::ftob(13.0);
    cout << Converter::btof(bytes) << endl;

    bytes = Converter::dtob(13.0);
    cout << Converter::btod(bytes) << endl;

```

## StrUtils

```cpp
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
```

## HashCode

```cpp
    string testmsg = "Mary has a little sheep, she loves the sheep very much.";

    cout << "SHA256: " << HashCode::sha256(testmsg.c_str(), testmsg.length()) << endl;
    cout << "SHA1: " << HashCode::sha1(testmsg.c_str(), testmsg.length()) << endl;
    cout << "MD5: " << HashCode::md5(testmsg.c_str(), testmsg.length()) << endl;
```

## FileIO
```cpp
    string file = ".\\Triangle\\README.md";
    string dir = ".\\OneDrive\\Triangle";
    
    // detect pathes
    cout << "is exist:" << FileIO::isExist(dir)
        << "\tis file:" << FileIO::isFile(file) 
        << "\tis dir:" << FileIO::isDir(file) << endl;

    // read and write file
    FileNode node = { 0 };
    FileIO::read(file, node);
    string str((const char*)node.data, node.length);
    FileIO::write(".\\Triangle\\output.txt", node);

    // read file size
    cout << "file size:" << FileIO::length(file) << endl;
    
    // search files
    vector<string> files = FileIO::searchFiles(dir);
    for (auto f : files) {
        cout << f << endl;
    }
```

## Timer
```cpp
    cout << "since1970:" << Timer::since1970() << endl;
    cout << "start timer\n";
    Timer t;
    t.start();
    Sleep(1000);
    cout << "end timer: " << t.stop() << endl;
```

## Validator
```cpp
    cout << Validator::match_email("hello@px.com") << endl;
    cout << Validator::match_phone("abcdefg") << endl;
    cout << Validator::match_ipv4("137.1.2.3") << endl;
    ...
```