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
    int execution_result;

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
                    output o(argv[2], argv[4]);
                    execution_result = o.write_batch_file();
                    break;
                }
                catch (int e)
                {
                    cout << e << "\nNo se encontro el directorio del archivo de salida especificado." << endl;
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
                    output o(argv[2], "");
                    execution_result = o.remove_files(false);
                    break;
                }
                catch (int e)
                {
                    cout << e << "\nNo se encontro el directorio del archivo de salida especificado." << endl;
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
                    output o(argv[2], argv[5]);
                    execution_result = o.remove_files(true);
                    break;
                }
                catch (int e)
                {
                    cout << e << "\nNo se encontro el directorio del archivo de salida especificado." << endl;
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
