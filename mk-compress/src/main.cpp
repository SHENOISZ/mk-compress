/*
*@AUTHOR SHENOISZ
*/
#include <iostream>
#include <fstream>
#include "header/html.hpp"

using namespace std;
using namespace shenoisz;


int main(int argc, const char* argv[])
{
    //string executable = argv[0];

    try
    {
        const char* path = argv[1];

        string tipo;
        string nome;
        string extension;
        string abs_path;
        string novo_nome;

        if (str.exists("/", path))
        {
            string *parts = str.split("/", path);
            nome = parts[str.len(parts)];
            abs_path = str.split("/" + nome, path)[0];

            parts = str.split(".", nome);
            nome = parts[str.len(parts) - 1];
            tipo = parts[str.len(parts)];
            extension = ".min." + tipo;

            novo_nome = abs_path + "/" + nome + extension;
        }
        else
        {
            string *parts = str.split(".", path);

            nome = parts[str.len(parts) - 1];
            tipo = parts[str.len(parts)];
            extension = ".min." + tipo;

            novo_nome = nome + extension;
        }

        const char* nome_mini = str.toConst(novo_nome);

        ifstream file;

        file.open(path);

        if (file.is_open())
        {
            string line;
            string lines;

            while (getline(file, line))
            {
                lines += line + "\n";
            }

            int tam =  lines.length();

            file.close();

            ofstream file;

            Html *html = new Html();

            if (tam >= 4)
            {
                if (tipo == "html")
                {
                    file.open(nome_mini);
                    file << html->htmlMinify(lines);

                } else if (tipo == "css")
                {
                    file.open(nome_mini);
                    file << html->cssMinify(lines);

                } else if (tipo == "js")
                {
                    file.open(nome_mini);
                    file << html->jsMinify(lines);
                }
            }
            else
            {
                file.open(nome_mini);
            }

            file.close();
        }
        else
        {
            cout << "Error reader file" << endl;
        }
    }
    catch(...)
    {
        cout << "mk-compress\nVersion: 1.0\nDeveloper: SHENOISZ" << endl;
    }

    return 0;
}