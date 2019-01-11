/*
 * Duplicate Manager (dupman)
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
 * dupman /i input_file [/b batch_file | /d [/l log_file]]
 *
 * Escenarios
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
         * Escenario:
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
         * Escenario:
         *   dupman /i file /b file
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 &&
                strcmp(argv[3], "/b") == 0 && strlen(argv[4]) > 2)
            {
                f_input.assign(argv[2]); f_batch.assign(argv[4]);
                executionResult = write_batch_file(f_input, f_batch);
                break;
            }

        case 4:
        /*
         * Eliminación sin logs
         * Escenario:
         *   dupman /i file /d
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 &&
                strcmp(argv[3], "/d") == 0)
            {
                f_input.assign(argv[2]);
                executionResult = remove_files(f_input, "", false);
                break;
            }

        case 6:
        /*
         * Eliminación con logs
         * Escenario:
         *   dupman /i file /d /l file
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 &&
                strcmp(argv[3], "/d") == 0 &&
                strcmp(argv[4], "/l") == 0 && strlen(argv[5]) > 2)
            {
                f_input.assign(argv[2]); f_log.assign(argv[5]);
                executionResult = remove_files(f_input, f_log, true);
                break;
            }

        default:
            cout << "Parametros incorrectos.\n" << endl;
            cout << "Sintaxis:" << endl;
            cout << "  dupman /i input_file [/b batch_file | /d ";
            cout << "[/l log_file]]" << endl;

            return 1;
    }

    return 0;
}
