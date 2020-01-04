#pragma once

#ifdef PYRE_PLATFORM_WINDOWS
    #ifdef PYRE_BUILD_LIB
        #define PYRE_API __declspec(dllexport)
    #else
        #define PYRE_API __declspec(dllimport)
    #endif
#elif defined(PYRE_PLATFORM_LINUX)
    #define PYRE_API
#else
    #error Unsupported platform!
#endif

#define BIT(x) (1 << x)