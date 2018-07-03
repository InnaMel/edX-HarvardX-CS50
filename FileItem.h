#pragma once

#include <fstream>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <tchar.h>
#include <vector>

using namespace std;

// class for creating an object each file
class FileItem
{

// properties
public:
    wstring name;
    wstring path;
    bool marked = false;

// metod
    wstring fullPath();

// constructor for initialize property
    FileItem();

// destructor for clear memory
    ~FileItem();
};
typedef vector<FileItem *> filesList;
