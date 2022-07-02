//
// Created by tablet on 19.06.22.
//

#include "File.h"
#include <fstream>

File::File(Achie *achie, const char *path)
        :achie(achie), path(path) {}

File::File(const char *path)
    :path(path) {
    Profile inprofile;
    std::ifstream file;
    file.open(path, std::ios::binary);
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char *> (&inprofile), sizeof(inprofile))) {}
        this->profile = &inprofile;
    }
}

Achie *File::get_achie() {
    return this->achie;
}

int File::save() {
    std::ofstream file;
    file.open(this->path, std::ios::binary|std::ios::app);
    file.write(reinterpret_cast<char *> (this->achie), sizeof(*achie));
    file.close();
    return 0;
}