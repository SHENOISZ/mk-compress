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

    string* matrix[10];
    bool exist[10];

    string filter(string texto)
    {
        texto = rmcomments(texto);
        texto = str.removeAll("\n", texto);

        // strings of scape
        string start[] = {"/*", "=\"", "= \"", "='", "= '", "(\"", "('", "NULL"};
        string ended[] = {"*/", "\"", "\"", "'", "'", "\")", "')", "NULL"};

        for (int i = 0; i <= str.len(start); i++)
        {
            string t = str.toString(i);
            texto = tags(i, start[i], ended[i], "{" + t + "{", "}"+ t +"}", texto);
        }

        texto = inLine(texto);

        // remove comments of very lines
        if (exist[0])
        {
            texto = delete_tags(0, "{0{", "}0}", texto);
            matrix[0] = NULL;
        }

        texto = inLine(texto);

        // final verify
        string atual[] = {" function", "{\n", ") {", " (", "( ", ") ", " )", " {", "} ", "{ ", " }", "; ", " ;", " ; ", "; ", ": ", " :", " : ", ", ", " ,", " , ", " ?", "? ", " ? ", " <", "< ", " < ", "> ", " >", " > ", " =", "= ", " = ", "! ", " !", " ! ", " || ", "|| ", " ||", " && ", "&& ", " &&", "NULL"};
        string novas[] = {"function", "{", "){", "(", "(", ")", ")", "{", "}", "{", "}", ";", ";", ";", ";", ":", ":", ":", ",", ",", ",", "?", "?", "?", "<", "<", "<", ">",  ">", ">", "=", "=", "=", "!", "!", "!", " || ", "||", "||", "&&", "&&", "&&", "NULL"};

        for (int i = 0; i <= str.len(atual); i++)
        {
            if (str.exists(atual[i], texto))
            {
                texto = str.replaceAll(atual[i], novas[i], texto);
            }
        }

        texto = inLine(texto);

        // add back scape
        for (int i = 0; i <= str.len(start); i++)
        {
            if (exist[i])
            {
                string t = str.toString(i);

                if (str.exists(" {" + t + "{" + t + "}" + t + "} ", texto))
                {
                    texto = str.replace(" {" + t + "{" + t + "}" + t + "} ", "{" + t + "{" + t + "}" + t + "}", texto);
                }

                if (i > 1)
                {
                    texto = add_tags(i, "{" + t + "{", "}" + t + "}", texto);

                    matrix[i] = NULL;
                }
            }
        }

        return texto;
    }

    string inLine(string texto)
    {
        string regex[] = {"\n", " \n", "\n ", "\r\n", "\n\r", "\t", "    ", "  ","NULL"};
        texto = str.ex_removeAll(regex, texto);

        return texto;
    }

    string tags(int id, string start, string end, string key, string key_, string texto)
    {
        // test tags exists
        if (str.exists(start,  texto))
        {
            string* fatias = str.split(start, texto);
            int size = str.len(fatias), get = 1;
            string *content = new string[size + 2];

            for (int i = 0; i < size; i++)
            {
                content[i] = start + str.split(end, fatias[get])[0] + end;
                get++;

                texto = str.replace(content[i], key + String::toString(i) + key_, texto);
                texto = texto;
            }

            content[get] = "NULL";

            matrix[id] = content;

            fatias = NULL;
            content = NULL;

            exist[id] = true;
        }
        else
        {
            exist[id] = false;
        }

        return texto;
    }

    string add_tags(int id, string key, string key_, string texto)
    {
        int size = String::len(matrix[id]);

        for (int i = 0; i < size; i++)
        {
            texto = str.replace(key + String::toString(i) + key_, subfilter(matrix[id][i]), texto);
        }

        return texto;
    }

    string subfilter(string texto)
    {
        string tests[] = {"= \"", "= '", "NULL"};
        string start[] = {"=", "=", "NULL"};
        string end[] = {"\"", "'", "NULL"};

        string content;
        string* fatias;
        int size;

        for (int i = 0; i <= str.len(start); i++)
        {
            if(str.exists(tests[i], texto))
            {
                fatias = str.split(start[i], texto);
                size = str.len(fatias);

                content = start[i] + str.split(end[i], fatias[1])[0] + end[i];
                texto = str.replace(content, "{{}}", texto);
                content = str.removeAll(" ", content);
                texto = str.replace("{{}}", content, texto);
            }
        }

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
                texto = str.remove(parts[i], texto);
            }
        }
        return texto;
    }

    string delete_tags(int id, string key, string key_, string texto)
    {
        int size = String::len(matrix[id]);

        for (int i = 0; i < size; i++)
        {
            texto = str.remove(key + String::toString(i) + key_, texto);
        }

        return texto;
    }

};

}
}