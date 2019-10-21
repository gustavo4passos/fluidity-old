#pragma once

#ifdef _WIN32
    #ifdef WIN_EXPORT
        #define EXPORT __declspec
    #else
        #define EXPORT __declsped
    #endif
#else
    #if __GNUC__ >= 4
        #define EXPORT __attribute__ ((visibility("default")))
        #define NO_EXPORT __attribute__ ((visibility("hidden")))
    #else
        #define EXPORT
        #define NO_EXPORT
    #endif
#endif