#include <fstream>
#include <string>
#include <windows.h>
#include "fs.h"

using std::string;

bool file_exists(string path)
{
    if (path.length() == 0)
        return false;

    std::ifstream ifs(path.c_str());

    return ifs.good();
}

bool directory_exists(string path)
{
    if (path.length() == 0)
        return false;

    filter_path(path);

    DWORD dirAttr = GetFileAttributesA(path.c_str());

    if (dirAttr == INVALID_FILE_ATTRIBUTES)
        return false;

    if (dirAttr & FILE_ATTRIBUTE_DIRECTORY)
        return true;

    return false;
}

void filter_path(string& path)
{
    path = path.substr(0, path.find_last_of('\\'));
}
