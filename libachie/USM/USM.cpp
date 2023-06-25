//
// Created by smurf on 19.07.22.
//
// Universal Storage Manager
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "macro_config.h"
#include "config.h"

#include "USM.h"
#include "Section.h"

#include <iostream>
bool InTextMode = 1;

const std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> result;
    std::string buf;
    buf.clear();
    result.clear();
    int i = 0;
    for (const auto& c: str) {
        if (c == delim) {
            result.emplace_back(buf);
            buf.clear();
        } else {
            buf += c;
        }
    }
    result.emplace_back(buf);
    buf.clear();
    return result;
}

Stringlist::Stringlist (const char cc) {
    c = cc;
    next = NULL;
}
void Stringlist::operator= (const char cc) {
    c = cc;
}
void Stringlist::add (const char cc) {
    Stringlist *sl = this;
    while (sl->next) {
        sl = sl->next;
    }
    sl->next = new Stringlist(cc);
}
const std::string Stringlist::to_string(size_t beg, size_t end) {
    std::string str;
    Stringlist *sl = this;
    size_t counter = 0;
    while(sl && counter < end) {
        if (counter >= beg) {
            str += sl->c;
        }
        sl = sl->next;
        ++counter;
    }
    return str;
}
Stringlist* Stringlist::end() {
    Stringlist* sl = this;
    while(sl->next) {
        sl = sl->next;
    }
    return sl;
}
bool Stringlist::operator== (const char cc) {
    return c == cc;
}
bool Stringlist::operator== (const std::string& str) {
    Stringlist* sl = this;
    bool flag = true;
    //std::cout << str.size();
    for (int i = 0; i < str.size(); ++i) {
        //std::cout << i;
        if (*sl == str[i]) {
            if (sl->next == NULL) {
                std::cout << "String index out of range";
                return 0;
            }
        } else {
            flag = false;
            //return 0;
        }
        sl = sl->next;
    }
    return flag;
}

ProfileStorage::ProfileStorage(const std::string &name)
        : name_(name) {
    //file_.open("profiles/" + name_, std::fstream::in | std::fstream::out | std::fstream::app);
    system((std::string(MAKEDIR) + " profiles/res/" + name_).c_str());
    if (InTextMode) {
        std::ifstream file("profiles/" + name_ + ".uto");
        std::string buf;
        //std::cout << file.is_open();
        is_opened = file.is_open();
        if (is_opened) {
            //std::cout << '1';
            while (std::getline(file, buf)) {
                //std::cout << buf << '|';
                std::string sec_name;
                std::string object;
                bool first_in = true;
                bool first_out = true;
                bool continue_reading = false;
                int type = 0; //0 is string, 1 is int
                bool delim_opened = false;
                bool object_opened = true;
                bool name_entered = false;
                int cnt = 0;
                std::vector<int> ivec;
                std::vector<std::string> svec;
                std::string four_char;
                std::string obj_buff;
                short four_counter = 0;
                bool first_after_init_flag = true;
                Stringlist strlst('1');
                Stringlist *sl = &strlst;
                for (const auto &s: buf) {
                    //std::cout << s;
                    if (first_in && s == 'i') {
                        type = 1;
                    } else if (first_in && s == 's') {
                        type = 0;
                    }
                    if (s == '<' && first_in)
                        first_in = false;
                    else if (!first_in && !name_entered && s != '>') {
                        sec_name += s;
                        //std::cout << sec_name;
                    } else if (s == '>' && !first_in && !name_entered) {
                        name_entered = true;
                        continue_reading = true;
                        continue;
                    }
                    if (continue_reading) {
                        if (cnt < 4) {
                            sl->add(s);
                            if (first_after_init_flag) {
                                sl = sl->next;
                                first_after_init_flag = false;
                            }
                        } else {
                            sl->add(s);
                            if (!(sl->to_string(1, 5) == "<\\e>")) {
                                obj_buff += sl->c;
                            } else {
                                //std::cout << obj_buff << '\n';
                                switch (type) {
                                    case 0:
                                        svec.emplace_back(obj_buff);
                                        break;
                                    case 1:
                                        ivec.emplace_back(std::stoi(obj_buff));
                                        break;
                                }
                                obj_buff.clear();
                                sl = sl->end();
                                cnt = 0;
                                first_after_init_flag = true;
                                continue;
                            }
                            //std::cout << sl->to_string(1, 5) << " ";
                            //sl = &strlst;
                            sl = sl->next;
                            //cnt = 0;
                            //first_after_init_flag = true;
                        }
                        ++cnt;
                    }
                }
                switch (type) {
                    case 0:
                        ssecs_.emplace(sec_name, StringSection(sec_name, svec));
                        break;
                    case 1:
                        isecs_.emplace(sec_name, IntSection(sec_name, ivec));
                        break;
                }
                //file_.seekg();
                //file_.clear();
                //file_.seekg(0);
            }
        } else {
            system((std::string(CREATE_FILE) + "profiles/" + name_ + ".uto").c_str());
            std::ofstream profiles_list("profiles/profiles_list.txt", std::ios::app);
            profiles_list << name;
            profiles_list << '\n';
            //throw "Cannot open file";
        }
    }
}

const std::string& ProfileStorage::get_name() {
    return name_;
}

void ProfileStorage::to_file() {
    if (InTextMode) {
        std::string text_buf;
        for (auto &s: isecs_) {
            text_buf += "i<" + s.first + ">";
            for (auto &obj: s.second.get_objects()) {
                text_buf += std::to_string(obj) + "|<\\e>";
            }
            text_buf += "\n";
        }
        for (auto &s: ssecs_) {
            text_buf += "s<" + s.first + ">";
            for (auto &obj: s.second.get_objects()) {
                text_buf += obj + "|<\\e>";
            }
            text_buf += "\n";
        }
        std::ofstream file("profiles/" + name_ + ".uto");
        file << text_buf;
    }
}

std::vector<ProfileStorage> ProfileStorage::get_profiles(const std::string& program_name) {
    std::vector<ProfileStorage> profiles;
    std::string path("profiles" + std::string(SEPARATOR) + "profiles_list.txt");
    std::ifstream file(path);
    if (file) {
        std::string buf;
        while (std::getline(file, buf)) {
            std::vector<std::string> s1 = split(buf, ':');
            if (s1.size() > 0) {
                if (s1.size() == 1 || s1[1] == program_name) {
                    profiles.emplace_back(s1[0]);
                }
            }
        }
    } else {
        system((std::string(CREATE_FILE) + path).c_str());
    }
    return profiles;
}

IntSection& ProfileStorage::geti (const std::string& name) {
    return isecs_.at(name);
}

StringSection& ProfileStorage::gets (const std::string& name) {
    return ssecs_.at(name);
}


void ProfileStorage::create_isec(const std::string &sec_name) {
    isecs_.emplace(sec_name, IntSection(sec_name));
}

void ProfileStorage::create_ssec(const std::string &sec_name) {
    ssecs_.emplace(sec_name, StringSection(sec_name));
}

const bool ProfileStorage::opened() {
    return is_opened;
}