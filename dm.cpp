#include <fstream>
#include <iostream>
#include <stdio.h>

std::ofstream oStream;

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Parametros incorrectos!" << std::endl;
        std::cout << "Se esperaba: ejecutable.exe \"archivo_entrada\" \"archivo_log\"" << std::endl;
        return 0;
    }
    else
    {
        int registros, i, j;
        std::string results, line, logLine;
        std::ifstream iStream;

        // Abrir para lectura
        iStream.open(argv[1], std::ios::in);

        // Cuenta de registros
        registros = 0;
        while(!iStream.eof())
        {
            getline(iStream, line);
            if (line.length() > 0)
                registros++;
        }
        iStream.close();

        iStream.open(argv[1], std::ios::in);

        std::string segID[registros];
        std::string paths[registros];

        for(i = 0; i < registros; i++)
        {
            getline(iStream, line);
            segID[i] = line.substr(0, 19);
            paths[i] = line.substr(20, std::string::npos);
        }
        iStream.close();

        oStream.open(argv[2], std::ios::app);

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
