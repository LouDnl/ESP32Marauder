#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Numbers\\Integer.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Configuration.hpp>
#include <ArduinoJson/Namespace.hpp>

#include <stdint.h>  // int64_t

namespace ARDUINOJSON_NAMESPACE {

#if ARDUINOJSON_USE_LONG_LONG
typedef int64_t Integer;
typedef uint64_t UInt;
#else
typedef long Integer;
typedef unsigned long UInt;
#endif

}  // namespace ARDUINOJSON_NAMESPACE

#if ARDUINOJSON_HAS_LONG_LONG && !ARDUINOJSON_USE_LONG_LONG
#  define ARDUINOJSON_ASSERT_INTEGER_TYPE_IS_SUPPORTED(T)                  \
    static_assert(sizeof(T) <= sizeof(ARDUINOJSON_NAMESPACE::Integer),     \
                  "To use 64-bit integers with ArduinoJson, you must set " \
                  "ARDUINOJSON_USE_LONG_LONG to 1. See "                   \
                  "https://arduinojson.org/v6/api/config/use_long_long/");
#else
#  define ARDUINOJSON_ASSERT_INTEGER_TYPE_IS_SUPPORTED(T)
#endif
