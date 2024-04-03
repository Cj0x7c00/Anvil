#pragma once
#include <mutex>

/* TODO: add support for shared lib exports/imports on mac */
#ifdef __APPLE__
# define PLATFORM_APPLE 
#endif

#ifdef _WIN32
# define PLATFORM_WIN32
# ifdef ANV_BUILD_SHARED
#  define ANV_API _declspec(dllexport)
# else
#  define ANV_API _declspec(dllimport)
# endif
#endif

// takes in a lambda that will only ever be called once
#define ANV_CALL_ONCE(Lambda) \
static std::once_flag flag; \
std::call_once(flag, Lambda);