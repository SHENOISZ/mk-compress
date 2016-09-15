/*
*@AUTHOR SHENOISZ
*/

namespace std
{
namespace shenoisz
{


class Js
{
public:

    Js() {

    }

    ~Js() {

    }

    string jsMinify(string texto)
    {
        texto = filter(texto);

        return texto;
    }

protected:

    string jsMinify(int id, string key, string key_, string* matrix, string texto)
    {
        int size = str.len(matrix);

        for (int i = 0; i < size; i++)
        {
            texto = str.replace(key + str.toString(i) + key_, filter(matrix[i]), texto);
        }

        return texto;
    }

 private:

    string* matrix[1];

    string filter(string texto)
    {
        // remove comments of one line
        texto = rmcomments(texto);
        // remove comments of very line
        texto = rm_mult_comments(texto);
        // save the strings of the file
        texto = mapper(0, texto);
        // remove spaces and line break
        texto = inLine(texto);

        // lines final verify
        string atual[] = {" function", "{\n","{ ", " {", "; {", ") {", " (", "( ", ") ", " )", " {", "} ", "{ ", " }", "; ", " ;", " ; ", "; ", ": ", " :", " : ", ", ", " ,", " , ", " ?", "? ", " ? ", " <", "< ", " < ", "> ", " >", " > ", " =", "= "," = ", "! ", " !", " ! ", " || ", "|| ", " ||", " && ", "&& ", " &&", "NULL"};
        string novas[] = {"function", "{", "{", "{", ";{", "){", "(", "(", ")", ")", "{", "}", "{", "}", ";", ";", ";", ";", ":", ":", ":", ",", ",", ",", "?", "?", "?", "<", "<", "<", ">",  ">", ">", "=", "=", "=", "!", "!", "!", " || ", "||", "||", "&&", "&&", "&&", "NULL"};

        for (int i = 0; i <= str.len(atual); i++)
        {
            if (str.exists(atual[i], texto))
            {
                texto = str.replaceAll(atual[i], novas[i], texto);
            }
        }

        // add strings again in file
        texto = add_tags(0, "{s{", "}s}", texto);

        return texto;
    }

    string inLine(string texto)
    {
        texto = str.removeAll('\n', texto);
        texto = str.removeAll("\n\r", texto);
        texto = str.removeAll("\r\n", texto);
        texto = str.removeAll('\t', texto);
        texto = str.removeAll("    ", texto);
        texto = str.removeAll("  ", texto);
        texto = str.removeAll("  ", texto);
        return texto;
    }

    string add_tags(int id, string key, string key_, string texto)
    {
        int size = str.len(matrix[id]);

        for (int i = 0; i <= size; i++)
        {
            texto = str.replace(key + str.toString(i) + key_, matrix[id][i], texto);
        }

        return texto;
    }

    string mapper(int id, string texto)
    {
        string *fatias = str.split("\n", texto);
        int size = str.len(fatias);
        string *temp = new string[size + 2];
        int start = 0;

        bool virgula = false;
        bool virgula_ = true;
        bool add = true;

        int counter = 0;
        int pos = 0;

        for (int i = 0; i < size; i++)
        {
            for (int x = 0; x < fatias[i].length(); x++)
            {
                if (virgula_)
                {
                    if ('"' == fatias[i][x])
                    {
                        if (add)
                        {
                            start = x;
                        }

                        add = false;
                        counter++;

                        temp[pos] = str.substr(start, x + 1, fatias[i]);

                        start = x;

                        if (counter > 1)
                        {
                            counter = 0;
                            virgula = true;
                            texto = str.replace(temp[pos], "{s{" + str.toString(pos) + "}s}", texto);
                            pos++;
                        }
                        else
                        {
                            virgula = false;
                        }
                    }
                }

                if (virgula)
                {
                    if ('\'' == fatias[i][x])
                    {
                        if (add)
                        {
                            start = x;
                        }

                        add = false;
                        counter++;

                        temp[pos] = str.substr(start, x + 1, fatias[i]);

                        start = x;

                        if (counter > 1)
                        {
                            counter = 0;
                            virgula_ = true;
                            texto = str.replace(temp[pos], "{s{" + str.toString(pos) + "}s}", texto);
                            pos++;
                        }
                        else
                        {
                            virgula_ = false;
                        }

                    }
                }
            }
        }

        temp[pos] = "NULL";
        matrix[id] = temp;

        return texto;
    }

    string rmcomments(string texto)
    {
        string *parts = str.split("\n", texto);

        for (int i = 0; i < str.len(parts); i++)
        {
            string temp = "{{{" + parts[i] + "}}}";

            if (str.exists("//", temp))
            {
                string remover = str.substr(str.find("//", parts[i])->index(), temp.length(), parts[i]);
                texto = str.remove(remover, texto);
            }
        }
        return texto;
    }

    string rm_mult_comments(string texto)
    {
        int start, ended;
        string temp, comment;

        for (int i = 0; i < texto.length(); i++)
        {
            comment = texto[i];
            comment += texto[i + 1];

            if ("/*" == comment)
            {
                start = i;
            }

            if ("*/" == comment)
            {
                temp = str.substr(start, i + 2, texto);
                texto = str.remove(temp, texto);
            }
        }

        return texto;
    }
};

}
}