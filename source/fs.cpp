#include <string>
#include <windows.h>
#include "fs.h"

using std::string;

bool file_exists(string path)
{
    if (path == NULL || path.legth() == 0)
        return false;

    ifstream f(path.c_str());
    return f.good();
}

bool directory_exists(string path)
{
    if (!filter_path(path))
        return false;

    DWORD dirAttr = GetFileAttributesA(path.c_str());

    if (dirAttr == INVALID_FILE_ATTRIBUTES)
        return false;

    if (dirAttr & FILE_ATTRIBUTE_DIRECTORY)
        return true;

    return false;
}

bool filter_path(string& path)
{
    if (path.length() == 0)
        return false;

    size_t backslash = path.find_last_of('\\');

    if (path.length() - 1 == backslash)
        path = path.substr(0, backslash);

    return true;
}
