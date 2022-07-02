//
// Created by tablet on 19.06.22.
//

#include "Profile.h"
#include <fstream>

#include <iostream>

#include <sstream>
#include <vector>

#include "json.hpp"

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        //elems.push_back(item);
        elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}


/*void readline(std::ifstream &file, char * buf) {
    int i = 0;
    char *c = new char[1];
    do {
        file.getline(c, 1);
        buf[i] = c[0];
        ++i;
    } while(c[0] != '\n');
    buf[i] = '\0';
    delete []c;
}*/

/*std::string *parse_csv(const std::string &line) {
    std::string *buf = new std::string[5];
    int i = 0;
    int j = 0;
    int k = 0;
    for (wchar_t c: line) {
        std::cout << c << '\n';
        buf[j][k] = c;
        ++i;
        ++k;
        if (c == wchar_t(',')) {
            std::cout << j << " parsed";
            ++j;
            k = 0;
        }
        if (i == 5)
            break;
    }
    return buf;
}*/

Profile load_profile(const std::string & name) {
    using Json = nlohmann::json;
    std::string text_profile;
    std::ifstream file;
    file.open(name);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            text_profile += line;
            line.clear();
        }
        file.close();
    }
    Json response = Json::parse(text_profile);
    Profile in_profile(response["Profile"]);
    for (auto a: response["Achies"]) {
        in_profile.add_achie(a["date"], a["object"], a["type"], a["value"]);
    }
    return in_profile;
}

void Profile::save_profile() {
    std::ofstream file;
    std::string path = "profiles/" + this->get_name() + ".json";
    file.open(path);
    std::string text_profile;
    text_profile += "{\n";
    text_profile += "\"Profile\" : \"" + this->get_name() + "\",\n";
    text_profile += "\"Achies\" : [\n";
    int i = 0;
    for (auto &achie: this->get_achies()) {
        text_profile += "   {\n";
        text_profile += "       \"date\" : \"" +  achie.get_date() + "\"," + "\n";
        text_profile += "       \"object\" : \"" + achie.get_object() + "\"," + "\n";
        text_profile += "       \"type\" : \"" + achie.get_type() + "\"," + "\n";
        text_profile += "       \"value\" : " + std::to_string(achie.get_value()) + "\n";
        ++i;
        if (i < this->get_achies().size())
            text_profile += "   },\n";
        else
            text_profile += "   }\n";

    }
    text_profile += "  ]\n";
    text_profile += "}\n";
    file << text_profile;
    file.close();
}

Profile::Profile(const std::string &name)
    :name(name){}


int Profile::load_csv(const std::string &filename) {
    //std::cout << "Entering to load_csv";
    //std::string filename;
    //filename = this->name;
    //filename += ".csv";
    std::ifstream csv(filename);
    if (csv) {
        //std::cout << "CSV file is opened";
        std::string str;
        std::vector<std::string> csv_str;
        //std::cout << "Ready to read lines";
        //csv.getline(str, sizeof(str));
        //std::cout << "line 0 readed";
        //memset(str, 0, strlen(str));
        std::getline(csv, str);
        str.clear();
        csv_str.clear();
        while (std::getline(csv, str)) {
            //std::cout <<  "Line readed: " << str << "\n";
            csv_str = split(str, ',');
            //std::cout << "CSV was parsed: " << csv_str[3] << "\n";
            //std::string date = csv_str[0];
            //std::string type = csv_str[1];
            //std::string object = csv_str[2];
            //int value = std::stof(csv_str[3]);
            //this->achies.emplace_back(std::move(csv_str[0]), std::move(csv_str[1]), std::move(csv_str[2]), std::stoi(csv_str[3]));
            this->add_achie(std::forward<const std::string &&>(csv_str[0]),  std::forward<const std::string &&>(csv_str[1]), std::forward<const std::string &&>(csv_str[2]), std::stoi(csv_str[3]));
            str.clear();
            csv_str.clear();
        }
        return 0;
    }  else {
        return 1;
    }
}

std::string &Profile::get_name() {
    return this->name;
}

void Profile::set_name(std::string& name) {
    this->name = name;
}

void Profile::add_achie(const std::string &date,  const std::string &type, const std::string &object, int value) {
    this->achies.emplace_back(std::forward<const std::string &&>(date),  std::forward<const std::string &&>(type), std::forward<const std::string &&>(object), value);
    this->save_profile();
}

std::vector<Achie> &Profile::get_achies() {
    return this->achies;
}