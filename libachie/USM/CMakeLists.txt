cmake_minimum_required(VERSION 3.23)
project(USM)

set(CMAKE_CXX_STANDARD 17)


#find_package(Boost 1.55.0 COMPONENTS system filesystem serialization REQUIRED)


add_executable(USM USM.cpp macro_config.h Section.cpp Section.h test.cpp config.h USM.h test.cpp)

#include_directories(${Boost_INCLUDE_DIRS})



#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

