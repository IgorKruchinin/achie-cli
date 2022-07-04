//
// Created by tablet on 19.06.22.
//

#include "Achie.h"

Achie::Achie(const std::string &date, const std::string &object, const std::string &type, int value)
    :date(date), object(object), type(type), value(value){}


std::string &Achie::get_date() {return this->date;}


std::string &Achie::get_object() {return this->object;}

std::string &Achie::get_type() {return this->type;}

int &Achie::get_value() {
    return this->value;
}
