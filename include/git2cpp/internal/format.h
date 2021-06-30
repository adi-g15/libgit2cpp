#pragma once

#include <cstdio>
#include <string>

namespace git {
namespace internal
{
    template<typename... Args>
    std::string format(const char * fmt, Args&& ... args)
    {
        /*
        #if std::format defined, use it
        */
        auto size = std::snprintf(nullptr, 0, fmt, args...);
        std::string result(size, 0);
        std::snprintf(&result[0], size + 1, fmt, args...);
        return result;
    }
}}
