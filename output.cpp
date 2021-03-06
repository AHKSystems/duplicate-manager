#include <fstream>
#include <iostream>
#include <string>
#include "date.h"
#include "fs.h"
#include "output.h"

using std::ifstream;
using std::ofstream;
using std::ios;
using std::string;

using std::cout;
using std::endl;

int remove_files(string input_file, string output_file, bool generate_log)
{
    int regCount;
    bool writeOut;
    ifstream iStream;
    ofstream oStream;

    const char* MSG_DELETED = "  Eliminado    -> ";
    const char* MSG_NOT_DELETED = "  No eliminado -> ";

    // Revisa si existe el directorio de salida
    if (generate_log && directory_exists(output_file))
        writeOut = true;
    else if (generate_log && !directory_exists(output_file))
    {
        cout << "No se encontro el directorio del archivo de salida especificado" << endl;
        return 15;
    }
    else
        writeOut = false;

    // Abrir para lectura
    iStream.open(input_file.c_str(), ios::in);

    // Cuenta de registros
    regCount = 0;
    while (!iStream.eof())
    {
        string buffer;
        getline(iStream, buffer);
        if (buffer.length() > 0)
            regCount++;
    }
    iStream.close();

    string segID[regCount];
    string paths[regCount];

    iStream.open(input_file.c_str(), ios::in);

    for (int i = 0; i < regCount; i++)
    {
        string buffer;
        getline(iStream, buffer);
        segID[i] = buffer.substr(0, 19);
        paths[i] = buffer.substr(20, string::npos);
    }
    iStream.close();

    if (writeOut)
        oStream.open(output_file.c_str(), ios::app);

    for (int i = 1; i < regCount; i++)
        for (int j = i - 1; j < i; j++)
            if (segID[i] == segID[j])
            {
                string bufferLog = get_datetime();

                if (remove(paths[i].c_str()) == 0)
                    bufferLog.append(MSG_DELETED);
                else
                    bufferLog.append(MSG_NOT_DELETED);

                bufferLog.append(paths[i]);
                bufferLog.append("\n");

                if (writeOut)
                    oStream << bufferLog;
            }

    if (writeOut)
        oStream.close();

    return 1;
}

int write_batch_file(string input_file, string output_file)
{
    int regCount;
    ifstream iStream;
    ofstream oStream;

    // Revisa si existe el directorio de salida
    if (!directory_exists(output_file))
    {
        cout << "No se encontro el directorio del archivo de salida especificado" << endl;
        return 15;
    }

    // Abrir para lectura
    iStream.open(input_file.c_str(), ios::in);

    // Cuenta de registros
    regCount = 0;
    while (!iStream.eof())
    {
        string buffer;
        getline(iStream, buffer);
        if (buffer.length() > 0)
            regCount++;
    }
    iStream.close();

    iStream.open(input_file.c_str(), ios::in);

    string segID[regCount];
    string paths[regCount];

    for (int i = 0; i < regCount; i++)
    {
        string buffer;
        getline(iStream, buffer);
        segID[i] = buffer.substr(0, 19);
        paths[i] = buffer.substr(20, string::npos);
    }
    iStream.close();

    oStream.open(output_file.c_str(), ios::app);
    oStream << "pause\n" << endl;

    for (int i = 1; i < regCount; i++)
        for (int j = i - 1; j < i; j++)
            if (segID[i] == segID[j])
            {
                string line;
                line = "del \"";
                line.append(paths[i]);
                line.append("\"");

                oStream << line << endl;
            }
    oStream.close();

    return 1;
}
