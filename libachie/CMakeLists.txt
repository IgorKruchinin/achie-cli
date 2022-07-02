cmake_minimum_required(VERSION 3.22)
project(libachie)

set(CMAKE_CXX_STANDARD 14)

add_library(libachie SHARED library.cpp Profile.cpp Profile.h Achie.cpp Achie.h)
