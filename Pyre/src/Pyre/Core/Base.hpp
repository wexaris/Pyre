#pragma once

//////////////////////// PLATFORM ////////////////////////

#ifdef _WIN32
    #ifdef _WIN64
        #define PYRE_PLATFORM_WINDOWS
    #else
        #error "x86 is not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #define PYRE_PLATFORM_IOS
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #define PYRE_PLATFORM_MACOS
        #error "MacOS is not supported!"
    #else
        #error "Unknown platform!"
    #endif
#elif defined(__ANDROID__)
    #define PYRE_PLATFORM_ANDROID
    #error "Android is not supported!"
#elif defined(__linux__)
    #define PYRE_PLATFORM_LINUX
    #error "Linux is not supported!"
#else
   #error Unknown platform!
#endif


//////////////////////// BUILD TYPE ////////////////////////
// PYRE_DEBUG
// PYRE_RELEASE
// PYRE_DISTRIB

#ifndef PYRE_DISTRIB
    #ifdef _DEBUG
        #define PYRE_DEBUG
    #else
        #define PYRE_RELEASE
    #endif
#endif


//////////////////////// SETTINGS ////////////////////////

#define GLFW_INCLUDE_NONE // GLFW won't include its own OpenGL

#ifdef PYRE_DEBUG
    #define PYRE_ENABLE_ASSERTS
    #define PYRE_ENABLE_PROFILE

    #if defined PYRE_PLATFORM_WINDOWS
        #define PYRE_DEBUGBREAK() __debugbreak()
    #elif defined PYRE_PLATFORM_LINUX
        #include <signal.h>
        #define PYRE_DEBUGBREAK() raise(SIGTRAP)
    #endif
#endif

#ifndef PYRE_DISTRIB
    #define PYRE_ENABLE_IMGUI
#endif

#ifdef PYRE_ENABLE_ASSERTS
    #define PYRE_CORE_ASSERT(x, ...) { if (!(x)) { PYRE_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); PYRE_DEBUGBREAK(); } }
    #define PYRE_ASSERT(x, ...) { if (!(x)) { PYRE_ERROR("Assertion Failed: {}", __VA_ARGS__); PYRE_DEBUGBREAK(); } }
#else
    #define PYRE_CORE_ASSERT(x, ...)
    #define PYRE_ASSERT(x, ...)
#endif


//////////////////////// APPLICATION ////////////////////////

#define BIT(x) (1 << x)

#include <memory>

namespace Pyre {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr auto MakeScope(const Args&... args) {
        return std::make_unique<T>(args...);
    }

    template<typename T, typename... Args>
    constexpr auto MakeRef(const Args&... args) {
        return std::make_shared<T>(args...);
    }


    // FNV-1a 32bit hashing algorithm
    constexpr uint32_t Const_FNV1a_32 = 0x811c9dc5;
    constexpr uint32_t Prime_FNV1a_32 = 0x1000193;
    inline constexpr uint32_t Hash32_FNV1a(const char* const str, const uint32_t value = Const_FNV1a_32) noexcept {
        return (str[0] == '\0') ? value : Hash32_FNV1a(&str[1], (value ^ uint32_t(str[0])) * Prime_FNV1a_32);
    }

    // FNV-1a 64bit hashing algorithm
    constexpr uint64_t Const_FNV1a_64 = 0xcbf29ce484222325;
    constexpr uint64_t Prime_FNV1a_64 = 0x100000001b3;
    inline constexpr uint64_t Hash64_FNV1a(const char* const str, const uint64_t value = Const_FNV1a_64) noexcept {
        return (str[0] == '\0') ? value : Hash64_FNV1a(&str[1], (value ^ uint64_t(str[0])) * Prime_FNV1a_64);
    }

}