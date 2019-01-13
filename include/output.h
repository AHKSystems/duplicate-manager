#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <vector>

int get_lines(std::string filename, std::vector<std::string>& paths, std::vector<std::string>& segments);
int remove_files(std::string input_file, std::string output_file, bool generate_log);
int write_batch_file(std::string input_file, std::string output_file);

#endif    // OUTPUT_H
