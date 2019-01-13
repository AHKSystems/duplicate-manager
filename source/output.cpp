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

int write_batch_file(string input_file, string output_file)
{
    // Revisa si existe el directorio de salida
    if (!directory_exists(output_file))
        throw 15;

    vector<string> paths;

    ifstream ifs(input_file, ios::in);
    if (!ifs.is_open())
        return 10;

    while (ifs.good())
    {
        string buffer;
        getline(ifs, buffer);

        paths.push_back(buffer.substr(20, string::npos));
    }
    ifs.close();

    ofstream ofs(output_file, ios::app);
    if (!ofs.is_open())
        return 11;

    ofs << "pause" << endl << endl;

    for (int i = 1; i < paths.size(); i++)
        for (int j = i - 1; j < i; j++)
            if (segID[i] == segID[j])
            {
                string line;
                line.assign("del \"");
                line.append(paths[i]);
                line.append("\"");

                ofs << line << endl;
            }
    ofs.close();

    return 0;
}
