#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "date.h"
#include "fs.h"
#include "output.h"

using std::endl;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;
using std::vector;

output::output(string input_file, string output_file)
{
    this->input_file = input_file;
    this->output_file = output_file;
}

output::~output() { }

int output::get_lines()
{
    ifstream ifs(input_file, ios::in);
    if (!ifs.is_open())
        return 10;

    while (ifs.good())
    {
        string buffer;
        getline(ifs, buffer);

        segment_ids.push_back(buffer.substr(0, 19));
        paths.push_back(buffer.substr(20, string::npos));
    }
    ifs.close();

    return 0;
}

int output::write_batch_file()
{
    // Revisa si existe el directorio de salida
    if (!directory_exists(output_file))
        return 15;

    int read_result = get_lines();

    if (read_result == 0)
    {
        ofstream ofs(output_file, ios::app);
        if (!ofs.is_open())
            return 11;

        ofs << "pause" << endl << endl;

        for (int i = 1; i < paths.size(); i++)
            for (int j = i - 1; j < i; j++)
                if (segment_ids[i] == segment_ids[j])
                {
                    string line;
                    line.assign("del \"");
                    line.append(paths[i]);
                    line.append("\"");

                    ofs << line << endl;
                }
        ofs.close();
    }

    return read_result;
}

int output::remove_files(bool generate_log)
{
    return 0;
}
