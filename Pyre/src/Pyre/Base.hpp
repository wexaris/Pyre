#pragma once

#ifndef PYRE_PLATFORM_WINDOWS
    #error Unsupported platform!
#endif

#ifdef _DEBUG
    #define PYRE_ENABLE_ASSERTS
#endif

#ifdef PYRE_ENABLE_ASSERTS
    #define PYRE_CORE_ASSERT(x, ...) { if (!(x)) { PYRE_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); __debugbreak(); } }
    #define PYRE_ASSERT(x, ...) { if (!(x)) { PYRE_ERROR("Assertion Failed: {}", __VA_ARGS__); __debugbreak(); } }
#else
    #define PYRE_CORE_ASSERT(x, ...)
    #define PYRE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)