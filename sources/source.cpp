// Copyright 2018 Ivan <your_email>
//hello, xia
#include <header.hpp>

unsigned ind_of_next_sym(const string& s, unsigned int i)
{
    while ((s[i] == ' ') || (s[i] == '\n') || (s[i] == '\t') ||
           (s[i] == ',') || (s[i] == ':'))
        i++;
    return i;
}

unsigned end_of_string(const string& s, unsigned int i)
{
    i++;
    while (s[i] != 34)
        i++;
    i++;
    return i;
}

unsigned ind_of_next_space(const string& s, unsigned int i)
{
    while ((s[i] != ' ') && (s[i] != '\n') && (s[i] != '\t') &&
           (s[i] != ',') && (s[i] != ':') && (s[i] != '}') &&
           (s[i] != ']'))
        i++;
    return i;
}

string word_to_string(const string& s, unsigned int i)
{
    i++;
    unsigned tmp = i;
    while (s[tmp] != '"')
        tmp++;
    return string(s, i, tmp-i);
}

string word_to_sth(const string& s, unsigned int i)
{
    unsigned tmp = i;
    while ((s[tmp] != ',') && (s[tmp] != ' ') && (s[tmp] != '\n'))
        tmp++;
    return string(s, i, tmp-i);
}

int it_is_true(const string& s, unsigned int i)
{
    int flag = 1;
    string a = "true";
    for (int tmp = 0; tmp <= 3; tmp++)
    {
        if (a[tmp] == s[i])
        {
            i++;
            tmp++;
        } else {
            flag = 0;
            break;
        }
    }
    return flag;
}

int it_is_false(const string& s, unsigned int i)
{
    int flag = 1;
    string a = "false";
    for (int tmp = 0; tmp <= 4; tmp++)
    {
        if (a[tmp] == s[i])
        {
            i++;
        } else {
            flag = 0;
            break;
        }
    }
    return flag;
}

Json::Json(const string& s)
{
    parse(s, 0);
}

Json::Json() = default;

bool Json::is_array() const
{
    bool flag = true;
    if (this->my_vector.empty())
        flag = false;
    return flag;
}

bool Json::is_object() const
{
    bool flag = true;
    if (this->my_map.empty())
        flag = false;
    return flag;
}

void Json::parse(const std::string &s, unsigned i)
{
    if (s[i] == '{')
    {
        i++;
        while (s[i] != '\0')
        {
            i = ind_of_next_sym(s, i);

            if (s[i] == '}')
                break;

            string key = word_to_string(s, i);

            i = end_of_string(s, i);
            i = ind_of_next_sym(s, i);

            if (s[i] == '"')
            {
                string value = word_to_string(s, i);
                this->my_map.insert(pair<string, any>(key, value));
                i = end_of_string(s, i);
            } else if ((s[i] >= '0') && (s[i] <= '9')) {
                int value = stoi(word_to_sth(s, i));
                this->my_map.insert(pair<string, any>(key, value));
                i = ind_of_next_space(s, i);
            } else if ((s[i] == 't') || s[i] == 'f') {
                if (it_is_true(s, i))
                {
                    bool value = true;
                    this->my_map.insert(pair<string, any>(key, value));
                } else if (it_is_false(s, i)) {
                    bool value = false;
                    this->my_map.insert(pair<string, any>(key, value));
                }
                i = ind_of_next_space(s, i);
            } else if ((s[i] == '{') || (s[i] == '[')) {
                Json value;
                value.parse(s, i);
                this->my_map.insert(pair<string, any>(key, value));
                int tmp = 1;
                do
                {
                    i++;
                    if ((s[i] == '}') || (s[i] == ']'))
                        --tmp;
                    if ((s[i] == '{') || (s[i] == '['))
                        ++tmp;
                } while (tmp != 0);
                i++;
                i = ind_of_next_sym(s, i);
            }
        }
    } else if (s[i] == '[') {
        i++;
        while (s[i] != '\0')
        {
            i = ind_of_next_sym(s, i);
            if (s[i] == ']')
                break;
            if (s[i] == '"')
            {
                string value = word_to_string(s, i);
                this->my_vector.push_back(value);
                i = end_of_string(s, i);
            } else if ((s[i] >= '0') && (s[i] <= '9')) {
                int value = stoi(word_to_sth(s, i));
                this->my_vector.push_back(value);
                i = ind_of_next_space(s, i);
            } else if ((s[i] == 't') || s[i] == 'f') {
                if (it_is_true(s, i))
                {
                    bool value = true;
                    this->my_vector.push_back(value);
                } else if (it_is_false(s, i)) {
                    bool value = false;
                    this->my_vector.push_back(value);
                }
                i = ind_of_next_space(s, i);
            } else if ((s[i] == '{') || (s[i] == '[')) {
                Json value;
                value.parse(s, i);
                this->my_vector.push_back(value);
                int tmp = 1;
                do
                {
                    i++;
                    if ((s[i] == '}') || (s[i] == ']'))
                        --tmp;
                    if ((s[i] == '{') || (s[i] == '['))
                        ++tmp;
                } while (tmp != 0);
                i++;
                i = ind_of_next_sym(s, i);
            }
        }
    }
}


Json Json::parse(const std::string &s)
{
    return Json(s);
}

Json Json::parseFile(const std::string& path_to_file)
{
    string tmp, str;
    ifstream in(path_to_file);
    if (!in)
    {
        cout <<"gg";
        return Json();
    } else {
        while (getline(in, tmp))
        {
            str = str+tmp+'\n';
        }
    }
    return Json(str);
}

