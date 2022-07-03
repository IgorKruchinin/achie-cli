cmake_minimum_required(VERSION 3.22)
project(achie)

set(CMAKE_CXX_STANDARD 17)

add_custom_target(build-time-make-directory ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${directory})

add_executable(achie main.cpp libachie/Profile.cpp libachie/Profile.h libachie/Achie.cpp libachie/Achie.h)
