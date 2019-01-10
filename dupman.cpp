/*
 * Duplicate Manager (dupman)
 */

//#include <cstdio>
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

            return write_batch_file(f_input, f_batch);
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

            return remove_files(f_input, "", false);
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

            return remove_files(f_input, f_log, true);

falla:
        default:
            cout << "Parametros incorrectos.\n" << endl;
            cout << "Sintaxis:" << endl;
            cout << "  dm /i input_file [/b batch_file | /d [/l log_file]]" << endl;

            return 1;
    }

    return 0;
}
