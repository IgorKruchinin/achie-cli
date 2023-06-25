//
// Created by smurf on 20.07.22.
//

#ifndef USM_MACRO_CONFIG_H
#define USM_MACRO_CONFIG_H
#define USM_VERSION 1
#define IN_TEXT_MODE 1

#if defined(__unix__) || defined(__unix) || defined(unix) // if OS is UNIX-Like

#define SEPARATOR "/"
#define MAKEDIR "mkdir -p "
#define CREATE_FILE "touch "

#endif // OS is defined

#endif //USM_MACRO_CONFIG_H
