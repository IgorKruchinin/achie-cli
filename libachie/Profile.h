//
// Created by tablet on 19.06.22.
//

#ifndef LIBACHIE_PROFILE_H
#define LIBACHIE_PROFILE_H
#include "Achie.h"
#include <vector>
#include <cstring>
#include <fstream>

class Profile {
    std::vector<Achie> achies;
    std::string name;
public:
    Profile(const std::string &name);
    //Profile(char const *name);
    //template <class Val>
    void add_achie(const std::string &date, const std::string &object, const std::string &type, int value);
    std::string &get_name();
    int to_csv(const std::string& path);
    void set_name(std::string & name);
    int load_csv(const std::string &filename);
    void save_profile();
    std::vector<Achie> &get_achies();
};


Profile load_profile(const std::string &name);

#endif //LIBACHIE_PROFILE_H
