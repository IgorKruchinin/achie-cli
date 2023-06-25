//
// Created by smurf on 30.08.22.
//
#include <iostream>

#include "USM.h"

int main() {
    for (auto prof: ProfileStorage::get_profiles("Test")) {
        std::cout << prof.get_name();
    }
    return 0;
}