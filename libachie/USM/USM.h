//
// Created by smurf on 08.08.22.
//

#ifndef USM_USM_H
#define USM_USM_H

#include <map>

#include "macro_config.h"
#include "config.h"

#include "Section.h"

static const char * BuildDate = __DATE__;

#define USMVer() USM_VERSION
#define Built() BuildDate

struct Stringlist {
    char c;
    Stringlist* next;
    Stringlist (const char cc);
    void operator= (const char cc);
    void add (const char cc);
    const std::string to_string(size_t beg, size_t end);
    Stringlist* end();
    bool operator== (const char cc);
    bool operator== (const std::string& str);
};

class ProfileStorage {
    std::string name_;
    std::map<std::string, IntSection> isecs_;
    std::map<std::string, StringSection> ssecs_;
    //std::string text_buf_;
    bool is_opened;
public:
    ProfileStorage(const std::string &name);
    std::vector<ProfileStorage> static get_profiles(const std::string& program_name);
    const std::string& get_name();
    void to_file();

    IntSection &geti (const std::string& name);
    StringSection &gets (const std::string& name);
    void create_isec(const std::string &sec_name);
    void create_ssec(const std::string &sec_name);
    const bool opened();
};

#endif //USM_USM_H
