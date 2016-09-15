/*
*@AUTHOR SHENOISZ
*/

namespace std
{
namespace shenoisz
{

class Css
{

 public:

    Css() {

    }

    ~Css() {

    }

    string cssMinify(string texto)
    {
        texto = filter(texto);

        return texto;
    }

 protected:

    string cssMinify(int id, string key, string key_, string* matrix, string texto)
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
        // remove comments of very line
        texto = rm_mult_comments(texto);
        // save the strings of the file
        texto = mapper(0, texto);
        // remove spaces and line break
        texto = inLine(texto);

        // final verify
        string atual[] = {" {", "} ", "{ ", " }", " )", "( ", ") ", " (", "( ", " .", ": ", " :", " : ", "; ", " ;", " ; ",", ", " ,", " , ", "0.", "NULL"};
        string novas[] = {"{", "}", "{", "}", ")", "( ", ")", "(", "(", ".", ":", ":", ":", ";", ";", ";", ",", ",",",", ".", "NULL"};

        for (int i = 0; i <= str.len(atual); i++)
        {
            if (str.exists(atual[i], texto))
            {
                texto = str.replaceAll(atual[i], novas[i], texto);
            }
        }
        // remove color repeat ex: #333333 -> #333
        texto = no_repeat(texto);

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

    string no_repeat(string texto)
    {
        string *fatias = str.split("#", texto);
        int size = str.len(fatias);

        string start;
        string end;

        for (int i = 1; i <= size; i++)
        {
            start = str.substr(0, 3, fatias[i]);
            end = str.substr(3, 6, fatias[i]);

            if (start == end)
            {
                texto = str.replace("#" + start + end, "#" + start, texto);
            }
        }

        return texto;
    }

};

}
}