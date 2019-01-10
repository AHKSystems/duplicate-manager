/*
 * Duplicate Manager
 */

#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

// Espacios de nombres
using namespace std;

// Declaración de funciones
int batch(const string, const string);
int borrado(const string, const string, const bool);
bool directoryExists(const string);
bool dirCheck(const string&);
const string getDateTime();

// Variables globales

/*
 * Sintaxis
 * dm /i input_file [/b batch_file | /d [/l log_file]]
 *
 * Escenarios
 * dm /h
 * dm /i file /b file
 * dm /i file /d
 * dm /i file /d /l file
 */
int main(int argc, const char* argv[])
{
    // Flags
    /*bool f_h = false,
        f_i = false,
        f_b = false,
        f_d = false,
        f_l = false;*/
    string f_input, f_batch, f_log;

    // Selección de parámetros
    switch (argc)
    {
        case 2:
        /*
         * Escenario:
         *   dm /h
         */
            // ayuda();
            goto falla;
            break;
        case 5:
        /*
         * Creación de batch
         * Escenarios:
         *   dm /i file /b file
         *   dm /b file /i file
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 && strcmp(argv[3], "/b") == 0 && strlen(argv[4]) > 2)
            {
                /*f_i = true; f_b = true;*/
                f_input.assign(argv[2]); f_batch.assign(argv[4]);
            }
            else if (strcmp(argv[1], "/b") == 0 && strlen(argv[2]) > 2 && strcmp(argv[3], "/i") == 0 && strlen(argv[4]) > 2)
            {
                /*f_i = true; f_b = true;*/
                f_input.assign(argv[4]); f_batch.assign(argv[2]);
            }
            else
                goto falla;

            return batch(f_input, f_batch);
        case 4:
        /*
         * Eliminación sin logs
         * Escenarios:
         *   dm /i file /d
         *   dm /d /i file
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 && strcmp(argv[3], "/d") == 0)
            {
                /*f_i = true; f_d = true;*/
                f_input.assign(argv[2]);
            }
            else if (strcmp(argv[1], "/d") == 0 && strcmp(argv[2], "/i") == 0 && strlen(argv[3]) > 2)
            {
                /*f_i = true; f_d = true;*/
                f_input.assign(argv[3]);
            }
            else
                goto falla;

            return borrado(f_input, "", false);
        case 6:
        /*
         * Eliminación con logs
         * Escenarios:
         *   dm /i file /d /l file
         *   dm /i file /l file /d
         *   dm /d /i file /l file
         *   dm /d /l file /i file
         *   dm /l file /d /i file
         *   dm /l file /i file /d
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 && strcmp(argv[3], "/d") == 0 && strcmp(argv[4], "/l") == 0 && strlen(argv[5]) > 2)
            {
                /*f_i = true; f_d = true; f_l = true;*/
                f_input.assign(argv[2]); f_log.assign(argv[5]);
            }
            else if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 && strcmp(argv[3], "/l") == 0 && strlen(argv[4]) > 2 && strcmp(argv[5], "/d") == 0)
            {
                /*f_i = true; f_d = true; f_l = true;*/
                f_input.assign(argv[2]); f_log.assign(argv[4]);
            }
            else if (strcmp(argv[1], "/d") == 0 && strcmp(argv[2], "/i") == 0 && strlen(argv[3]) > 2 && strcmp(argv[4], "/l") == 0 && strlen(argv[5]) > 2)
            {
                /*f_i = true; f_d = true; f_l = true;*/
                f_input.assign(argv[3]); f_log.assign(argv[5]);
            }
            else if (strcmp(argv[1], "/d") == 0 && strcmp(argv[2], "/l") == 0 && strlen(argv[3]) > 2 && strcmp(argv[4], "/i") == 0 && strlen(argv[5]) > 2)
            {
                /*f_i = true; f_d = true; f_l = true;*/
                f_input.assign(argv[5]); f_log.assign(argv[3]);
            }
            else if (strcmp(argv[1], "/l") == 0 && strlen(argv[2]) > 2 && strcmp(argv[3], "/d") == 0 && strcmp(argv[4], "/i") == 0 && strlen(argv[5]) > 2)
            {
                /*f_i = true; f_d = true; f_l = true;*/
                f_input.assign(argv[5]); f_log.assign(argv[2]);
            }
            else if (strcmp(argv[1], "/l") == 0 && strlen(argv[2]) > 2 && strcmp(argv[3], "/i") == 0 && strlen(argv[4]) > 2 && strcmp(argv[5], "/d") == 0)
            {
                /*f_i = true; f_d = true; f_l = true;*/
                f_input.assign(argv[4]); f_log.assign(argv[2]);
            }
            else
                goto falla;

            return borrado(f_input, f_log, true);

falla:
        default:
            cout << "Parametros incorrectos.\n" << endl;
            cout << "Sintaxis:" << endl;
            cout << "  dm /i input_file [/b batch_file | /d [/l log_file]]" << endl;

            return 0;
    }

    return 1;
}

int borrado(const string input_file, const string output_file, const bool isOut)
{
    int regCount, i, j;
    bool writeOut;
    string inLine, outLine;
    ifstream iStream;
    ofstream oStream;

    // Revisa si existe el directorio de salida
    if (isOut && directoryExists(output_file))
        writeOut = true;
    else if (isOut && !directoryExists(output_file))
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
                outLine.assign(getDateTime());

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

int batch(const string input_file, const string output_file)
{
    int regCount, i, j;
    string inLine, outLine;
    ifstream iStream;
    ofstream oStream;

    // Revisa si existe el directorio de salida
    if (!directoryExists(output_file))
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

bool directoryExists(const string pse_dir)
{
    string dir;

    if (dirCheck(pse_dir))
        return true;
    else
    {
        dir = pse_dir.substr(0, pse_dir.find_last_of("\\"));

        if (dirCheck(dir))
            return true;
        else
            return false;
    }
}

bool dirCheck(const string& dirName_in)
{
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!
}

const string getDateTime()
{
    try
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        char strDT[20];
        string str = "";

        sprintf(strDT, "%04u-%02u-%02u %02u:%02u:%02u",
            1900 + ltm->tm_year,
            1 + ltm->tm_mon,
            ltm->tm_mday,
            ltm->tm_hour,
            ltm->tm_min,
            ltm->tm_sec
        );
        str.append(strDT);

        return (str);
    }
    catch (exception e)
    {
        return "Error getting date";
    }
}
