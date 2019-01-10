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

int remove_files(string input_file, string output_file, bool isOut)
{
    int regCount, i, j;
    bool writeOut;
    string inLine, outLine;
    ifstream iStream;
    ofstream oStream;

    // Revisa si existe el directorio de salida
    if (isOut && directory_exists(output_file))
        writeOut = true;
    else if (isOut && !directory_exists(output_file))
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
        getline(iStream, inLine);
        if (inLine.length() > 0)
            regCount++;
    }
    iStream.close();

    iStream.open(input_file.c_str(), ios::in);

    string segID[regCount];
    string paths[regCount];

    for (i = 0; i < regCount; i++)
    {
        getline(iStream, inLine);
        segID[i] = inLine.substr(0, 19);
        paths[i] = inLine.substr(20, string::npos);
    }
    iStream.close();

    if (writeOut)
        oStream.open(output_file.c_str(), ios::app);

    for (i = 1; i < regCount; i++)
        for (j = i - 1; j < i; j++)
            if (segID[i] == segID[j])
            {
                outLine.assign(get_datetime());

                if (remove(paths[i].c_str()) == 0)
                    outLine.append("  Eliminado    -> ");
                else
                    outLine.append("  No eliminado -> ");

                outLine.append(paths[i]);
                outLine.append("\n");

                if (writeOut)
                    oStream << outLine;
            }

    if (writeOut)
        oStream.close();

    return 1;
}

int write_batch_file(string input_file, string output_file)
{
    int regCount, i, j;
    string inLine, outLine;
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
        getline(iStream, inLine);
        if (inLine.length() > 0)
            regCount++;
    }
    iStream.close();

    iStream.open(input_file.c_str(), ios::in);

    string segID[regCount];
    string paths[regCount];

    for (i = 0; i < regCount; i++)
    {
        getline(iStream, inLine);
        segID[i] = inLine.substr(0, 19);
        paths[i] = inLine.substr(20, string::npos);
    }
    iStream.close();

    oStream.open(output_file.c_str(), ios::app);
    oStream << "pause\n" << endl;

    for (i = 1; i < regCount; i++)
        for (j = i - 1; j < i; j++)
            if (segID[i] == segID[j])
            {
                outLine = "del \"";
                outLine.append(paths[i]);
                outLine.append("\"");

                oStream << outLine << endl;
            }
    oStream.close();

    return 1;
}
