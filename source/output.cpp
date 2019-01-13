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

int remove_files(string input_file, string output_file, bool generate_log)
{
    const char* MSG_DELETED = "  Eliminado    -> ";
    const char* MSG_NOT_DELETED = "  No eliminado -> ";

    bool writeOut;

    // Revisa si existe el directorio de salida
    if (generate_log && directory_exists(output_file))
        writeOut = true;
    else if (generate_log && !directory_exists(output_file))
        throw 15;
    else
        writeOut = false;

    vector<string> segment_ids;
    vector<string> paths;

    int read_result = get_lines(input_file, paths, segment_ids);

    if (read_result == 0)
    {
        ofstream ofs;

        if (writeOut)
            ofs.open(output_file, ios::app);

        for (int i = 1; i < paths.size(); i++)
            for (int j = i - 1; j < i; j++)
                if (segment_ids[i] == segment_ids[j])
                {
                    string bufferLog = get_datetime();

                    if (remove(paths[i].c_str()) == 0)
                        bufferLog.append(MSG_DELETED);
                    else
                        bufferLog.append(MSG_NOT_DELETED);

                    bufferLog.append(paths[i]);
                    bufferLog.append("\n");

                    if (writeOut)
                        ofs << bufferLog;
                }

        if (writeOut)
            ofs.close();
    }

    return read_result;
}

int write_batch_file(string input_file, string output_file)
{
    // Revisa si existe el directorio de salida
    if (!directory_exists(output_file))
        throw 15;

    vector<string> segment_ids;
    vector<string> paths;

    int read_result = get_lines(input_file, paths, segment_ids);

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

int get_lines(string filename, vector<string>& paths, vector<string>& segments)
{
    ifstream ifs(filename, ios::in);
    if (!ifs.is_open())
        return 10;

    while (ifs.good())
    {
        string buffer;
        getline(ifs, buffer);

        segments.push_back(buffer.substr(0, 19));
        paths.push_back(buffer.substr(20, string::npos));
    }
    ifs.close();

    return 0;
}
