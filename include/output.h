#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>

unsigned int get_file_numlines(std::string& filename);
int remove_files(std::string input_file, std::string output_file, bool isOut);
int write_batch_file(std::string input_file, std::string output_file);

#endif    // OUTPUT_H
