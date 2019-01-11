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
 * dm /i input_file [/b batch_file | /d [/l log_file]]
 *
 * Escenarios
 * dm /h
 * dm /i file /b file
 * dm /i file /d
 * dm /i file /d /l file
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
         *   dm /h
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
         *   dm /i file /b file
         */
            if (strcmp(argv[1], "/i") == 0 && strlen(argv[2]) > 2 &&
                strcmp(argv[3], "/b") == 0 && strlen(argv[4]) > 2)
            {
                /*f_i = true; f_b = true;*/
                f_input.assign(argv[2]); f_batch.assign(argv[4]);
                
                executionResult = write_batch_file(f_input, f_batch);
            }
        case 4:
        /*
         * Eliminación sin logs
         * Escenario:
         *   dm /i file /d
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

            executionResult = remove_files(f_input, "", false);
        case 6:
        /*
         * Eliminación con logs
         * Escenario:
         *   dm /i file /d /l file
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

            executionResult = remove_files(f_input, f_log, true);

falla:
        default:
            cout << "Parametros incorrectos.\n" << endl;
            cout << "Sintaxis:" << endl;
            cout << "  dm /i input_file [/b batch_file | /d [/l log_file]]" << endl;

            return 1;
    }

    return 0;
}
