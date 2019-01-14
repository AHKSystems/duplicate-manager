#ifndef FS_H
#define FS_H

#include <string>

bool file_exists(std::string path);
bool directory_exists(std::string path);
void filter_path(std::string& path);

#endif    // FS_H
