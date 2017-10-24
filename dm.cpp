#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

ofstream oStream;

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        cout << "Parametros incorrectos!" << endl;
        cout << "Se esperaba: ejecutable.exe \"archivo_entrada\" \"archivo_log\"" << endl;
        return 0;
    }
    else
    {
        int registros, i, j;
        string results, line, logLine;
        ifstream iStream;

        // Abrir para lectura
        iStream.open(argv[1], ios::in);

        // Cuenta de registros
        registros = 0;
        while(!iStream.eof())
        {
            getline(iStream, line);
            if (line.length() > 0)
                registros++;
        }
        iStream.close();

        iStream.open(argv[1], ios::in);

        string segID[registros];
        string paths[registros];

        for(i = 0; i < registros; i++)
        {
            getline(iStream, line);
            segID[i] = line.substr(0, 19);
            paths[i] = line.substr(20, string::npos);
        }
        iStream.close();

        oStream.open(argv[2], ios::app);

        results = "";
        for(i = 1; i < registros; i++)
            for(j = i - 1; j < i; j++)
                if(segID[i] == segID[j])
                {
                    logLine = "";

                    if(remove(paths[i].c_str()) == 0)
                        logLine.append("Eliminado    -> ");
                    else
                        logLine.append("No eliminado -> ");

                    logLine.append(paths[i]);
                    logLine.append("\n");

                    oStream << logLine;
                }

        oStream.close();

        return 1;
    }
}
