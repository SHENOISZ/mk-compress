/*
*@AUTHOR SHENOISZ
*/

#include "../libs/stringer.hpp"
#include "css.hpp"
#include "js.hpp"

namespace std
{
namespace shenoisz
{

class Html : public Css, public Js
{

 public:

    Html() {
        // constructor
    }

    ~Html() {
        // destructor
    }

    string htmlMinify(string texto)
    {
        // tags and atributes for scape
        string attr_start[] = {"<!--", "<style>", "style=\"", "style=\'", "<script", "<pre>", "= \"", " =\"", " = \"", "= '", " ='", " = '", "NULL"};
        string attr_end[] = {"-->", "</style>", "\"", "\'", "</script>", "</pre>", "\"", "\"", "\"", "'", "'", "'", "NULL"};

        for (int i = 0; i <= String::len(attr_start); i++)
        {
            string t = String::toString(i);
            texto = tags(i, attr_start[i], attr_end[i], "{" + t + "{", "}"+ t +"}", texto);
        }

        texto = inLine(texto);

        // remove comments in html
        if (exist[0])
        {
            texto = delete_tags(0, "{0{", "}0}", texto);
            matrix[0] = NULL;
        }

        //verify
        string atual[] = {">\n", "\n<", "  ", "> <", "NULL"};
        string novas[] = {">", "<", " ", "><", "NULL"};

        for (int i = 0; i <= String::len(atual); i++)
        {
            if (str.exists(atual[i], texto))
            {
                texto = str.replaceAll(atual[i], novas[i], texto);
            }
        }

        // tags normals
        for (int i = 0; i <= String::len(attr_start); i++)
        {
            if (exist[i])
            {
                string t = String::toString(i);

                if (str.exists(" {" + t + "{" + t + "}" + t + "} ", texto))
                {
                    texto = str.replace(" {" + t + "{" + t + "}" + t + "} ", "{" + t + "{" + t + "}" + t + "}", texto);
                }

                if (i > 4)
                {
                    texto = add_tags(i, "{" + t + "{", "}" + t + "}", texto);

                    matrix[i] = NULL;
                }
            }
        }

        // css minify
        for (int i = 1; i <= String::len(attr_start); i++)
        {
            if (i > 3) break;

            if (exist[i])
            {
                string t = String::toString(i);

                texto = cssMinify(i, "{" + t + "{", "}" + t + "}", matrix[i], texto);
                matrix[i] = NULL;
            }
        }

        // js minify
        if (exist[4])
        {
            texto = jsMinify(4, "{4{", "}4}", matrix[4], texto);
            matrix[4] = NULL;
        }

        //final verify
        string atual_[] = {">\n", "\n<", "> <", " >", "< ", "> ", " <", "> <script", "> <pre>","NULL"};
        string novas_[] = {">", "<", "><", ">", "<", ">", "<", "><script", "><pre>", "NULL"};

        for (int i = 0; i <= String::len(atual_); i++)
        {
            if (str.exists(atual_[i], texto))
            {
                texto = str.replaceAll(atual_[i], novas_[i], texto);
            }
        }

        return texto;
    }

 private:

    string* matrix[25];
    bool exist[25];

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

    string tags(int id, string start, string end, string key, string key_, string texto)
    {
        // test tags exists
        if (str.exists(start,  texto))
        {
            string* fatias = str.split(start, texto);
            int size = String::len(fatias), get = 1;
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
        string tests[] = {"src = \"", "src= \"", "src =\"", "href = \"", "href= \"", "href =\"", "data-src = \"", "data-src= \"", "data-src =\"", "NULL"};
        string start[] = {"src", "src", "src", "href", "href", "href", "data-src", "data-src", "data-src", "NULL"};
        string end[] = {"\"", "\"", "\"", "\"", "\"", "\"", "\"", "\"", "\"", "NULL"};

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