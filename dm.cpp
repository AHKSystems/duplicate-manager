#include <iostream>
#include <fstream>

void escribir(std::string, const char*);

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Parametros incorrectos!" << std::endl;
        std::cout << "Se esperaba: ejecutable.exe \"archivo_entrada\" \"archivo_salida\"" << std::endl;
        return 0;
    }
    else
    {
        int registros = 0, i, j;
        std::string resultados = "pause\n\n";

        std::string linea;
        std::ifstream doc;
        doc.open(argv[1], std::ios::in);

        // Cuenta de registros
        while(!doc.eof())
        {
            getline(doc, linea);
            if (linea.length() > 0)
                registros++;
        }

        doc.close();
        doc.open(argv[1], std::ios::in);

        std::string segID[registros];
        std::string rutas[registros];

        for(i = 0; i < registros; i++)
        {
            getline(doc, linea);
            segID[i] = linea.substr(0, 19);
            rutas[i] = linea.substr(20, std::string::npos);
        }
        doc.close();

        for(i = 1; i < registros; i++)
            for(j = i - 1; j < i; j++)
                if(segID[i] == segID[j])
                {
                    resultados.append("del ");
                    resultados.append(rutas[i]);
                    resultados.append("\n");
                }

        escribir(resultados, argv[2]);

        return 1;
    }
}

void escribir(std::string datos, const char* fileName)
{
    std::ofstream salida;
    salida.open(fileName, std::ios::out);

    salida << datos;
    salida.close();
}
