//
// Created by tablet on 19.06.22.
//

#ifndef LIBACHIE_FILE_H
#define LIBACHIE_FILE_H
#include "Profile.h"


class File {
    const char * path;
    Profile *profile;
public:
    File(Profile *profile, const char * path);
    File(const char *path);
    int save();
    Profile * get_profile();
    int setpath();
    const char * getpath();
    Profile & get_data();
    int set_data();
};


#endif //LIBACHIE_FILE_H
