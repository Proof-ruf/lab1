// Copyright 2018 Ivan <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>
#include <fstream>

using std::string;
using std::map;
using std::vector;
using std::any;
using std::pair;
using std::cout;
using std::ifstream;

class Json {
public:
    explicit Json(const string& s);
    Json();


    bool is_array() const;

    bool is_object() const;

    std::any& operator[](const std::string& key)
    {
        if (my_vector.empty())
            return my_map.find(key)->second;
        else
        {
            throw "Error: exemplar is array";
        }
    }


    std::any& operator[](int index)
    {
        if (my_vector.empty())
        {
            throw "Error: exemplar is object";
        } else {
            return my_vector[index];
        }
    }

    static Json parse(const std::string& s);

    static Json parseFile(const std::string& path_to_file);


    map<string, any> my_map;
    vector <any> my_vector;

private:
    void parse(const std::string &s, unsigned i);
};
#endif // INCLUDE_HEADER_HPP_

