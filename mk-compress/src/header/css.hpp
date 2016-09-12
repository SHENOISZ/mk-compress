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

    string* matrix[3];
    bool exist[3];

    string filter(string texto)
    {
        texto = tags(0, "/*", "*/", "{0{", "}0}", texto);
        texto = tags(1, "url(", ")", "{1{", "}1}", texto);

        // remove comments of very lines
        if (exist[0])
        {
            texto = delete_tags(0, "{0{", "}0}", texto);
            matrix[0] = NULL;
        }

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

        texto = no_repeat(texto);

        if (exist[1])
        {
            texto = add_tags(1, "{1{", "}1}", texto);

            matrix[1] = NULL;
        }

        texto = str.removeAll("\n", texto);

        return texto;
    }

    string inLine(string texto)
    {
        string regex[] = {"\n", "\n", "\n", "\r\n", "\n\r", "\t", "   ", "  ", "NULL"};
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

                texto = str.replace(content[i], key + str.toString(i) + key_, texto);
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
        int size = str.len(matrix[id]);

        for (int i = 0; i < size; i++)
        {
            texto = str.replace(key + str.toString(i) + key_, matrix[id][i], texto);
        }

        return texto;
    }

    string delete_tags(int id, string key, string key_, string texto)
    {
        int size = str.len(matrix[id]);

        for (int i = 0; i < size; i++)
        {
            texto = str.remove(key + str.toString(i) + key_, texto);
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