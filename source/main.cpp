/*
 * Duplicate Manager (dupman)
 *  Buscador de SegmentIDs duplicados
 */

#include <cstring>
#include <iostream>
#include <string>
#include "output.h"

using std::string;
using std::cout;
using std::endl;

/*
 * Sintaxis
 * dupman /i input_file [ /b batch_file | /d [ /l log_file ] ]
 *
 * Usos
 * dupman /h
 * dupman /i file /b file
 * dupman /i file /d
 * dupman /i file /d /l file
 */
int main(int argc, char** argv)
{
    int executionResult;

    string f_input, f_batch, f_log;

    // Selección de parámetros
    switch (argc)
    {
        case 2:
        /*
         * Uso:
         *   dupman /h
         */
            if (strcmp(argv[1], "/h") == 0)
            {
                // ayuda();
                // break;
            }

        case 5:
        /*
         * Creación de batch
         * Uso:
         *   dupman /i file /b file
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 &&
                strcmp(argv[3], "/b") == 0 && strlen(argv[4]) > 2)
            {
                try
                {
                    f_input.assign(argv[2]); f_batch.assign(argv[4]);
                    executionResult = write_batch_file(f_input, f_batch);
                    break;
                }
                catch (int e)
                {
                    cout << "No se encontro el directorio del archivo de salida especificado." << endl;
                    return e;
                }
            }

        case 4:
        /*
         * Eliminación sin logs
         * Uso:
         *   dupman /i file /d
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 &&
                strcmp(argv[3], "/d") == 0)
            {
                try
                {
                    f_input.assign(argv[2]);
                    executionResult = remove_files(f_input, "", false);
                    break;
                }
                catch (int e)
                {
                    cout << "No se encontro el directorio del archivo de salida especificado." << endl;
                    return e;
                }
            }

        case 6:
        /*
         * Eliminación con logs
         * Uso:
         *   dupman /i file /d /l file
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 &&
                strcmp(argv[3], "/d") == 0 &&
                strcmp(argv[4], "/l") == 0 && strlen(argv[5]) > 2)
            {
                try
                {
                    f_input.assign(argv[2]); f_log.assign(argv[5]);
                    executionResult = remove_files(f_input, f_log, true);
                    break;
                }
                catch (int e)
                {
                    cout << "No se encontro el directorio del archivo de salida especificado." << endl;
                    return e;
                }
            }

        default:
            cout << "Parametros incorrectos.\n" << endl;
            cout << "Sintaxis:" << endl;
            cout << "  dupman /i input_file [ /b batch_file | /d ";
            cout << "[ /l log_file ] ]" << endl;

            return 1;
    }

    return 0;
}
