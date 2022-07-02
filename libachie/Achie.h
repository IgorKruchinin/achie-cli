//
// Created by tablet on 19.06.22.
//

#ifndef LIBACHIE_ACHIE_H
#define LIBACHIE_ACHIE_H
#include <string>

class Achie {
    std::string date;
    std::string type;
    std::string object;
    int value;
public:
    Achie(const std::string &date,  const std::string &type, const std::string &object, int value);
    Achie() = default;
    std::string &get_date();
    std::string &get_type();
    std::string &get_object();
    int &get_value();
};


#endif //LIBACHIE_ACHIE_H
