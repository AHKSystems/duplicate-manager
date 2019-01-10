#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>

int remove_files(std::string input_file, std::string output_file, bool isOut);
int write_batch_file(std::string input_file, std::string output_file);

#endif    // OUTPUT_H
