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
    if (!file_exists(input_file)) throw 14;
    if (!directory_exists(output_file)) throw 15;

    this->input_file = input_file;
    this->output_file = output_file;
}

output::~output() { }

int output::get_lines()
{
    ifstream ifs(input_file, ios::in);
    if (!ifs.is_open())
        return -1;

    while (ifs.good())
    {
        string buffer;
        getline(ifs, buffer);

        segment_ids.push_back(buffer.substr(0, 19));
        paths.push_back(buffer.substr(20, string::npos));
    }
    ifs.close();

    return segment_ids.size();
}

int output::remove_files(bool generate_log)
{
    const char* MSG_DELETED = "  Eliminado    -> ";
    const char* MSG_NOT_DELETED = "  No eliminado -> ";

    int item_count = get_lines();
    int read_result;

    if (item_count > 0)
    {
        vector<string> log;

        if (generate_log)
        {
            ofstream ofs(output_file, ios::app)
            if (!ofs.is_open()) throw 12;
        }

        for (int i = 1; i < item_count; i++)
            for (int j = i - 1; j < i; j++)
                if (segment_ids[i] == segment_ids[j])
                {
                    string buffer_log = get_datetime();

                    if (remove(paths[i].c_str()) == 0)
                        buffer_log.append(MSG_DELETED);
                    else
                        buffer_log.append(MSG_NOT_DELETED);

                    buffer_log.append(paths[i]);
                    //buffer_log.append("\n");

                    log.push_back(buffer_log);
                }

        if (generate_log)
        {
            ofstream ofs(output_file, ios::app)

            for (int i = 0; i < item_count; i++)
                ofs << log[i] << endl;

            ofs.close();
        }
    }
    else if (item_count == 0) read_result = 1;
    else read_result = 2;

    return read_result;
}

int output::write_batch_file()
{
    int item_count = get_lines();
    int read_result;

    if (item_count > 0)
    {
        ofstream ofs(output_file, ios::app);
        if (!ofs.is_open()) throw 11;

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

        read_result = 0;
    }
    else if (item_count == 0) read_result = 1;
    else read_result = 2;

    return read_result;
}
