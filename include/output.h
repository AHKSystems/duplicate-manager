#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <vector>

class output
{
private:
    std::string input_file;
    std::string output_file;
    std::vector<std::string> paths;
    std::vector<std::string> segment_ids;
    int get_lines();

public:
    output(std::string input_file, std::string output_file);
    ~output();
    int write_batch_file();
    int remove_files(bool generate_log);

};

#endif    // OUTPUT_H
