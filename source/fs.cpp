#include <string>
#include <windows.h>
#include "fs.h"

bool directory_exists(std::string path)
{
    if (!filter_path(path))
        return false;

    DWORD fileAttr = GetFileAttributesA(path.c_str());

    if (fileAttr == INVALID_FILE_ATTRIBUTES)
        return false;

    if (fileAttr & FILE_ATTRIBUTE_DIRECTORY)
        return true;

    return false;
}

bool filter_path(std::string& path)
{
    if (path.length() == 0)
        return false;

    size_t backslash = path.find_last_of('\\');

    if (path.length() - 1 == backslash)
        path = path.substr(0, backslash);

    return true;
}
