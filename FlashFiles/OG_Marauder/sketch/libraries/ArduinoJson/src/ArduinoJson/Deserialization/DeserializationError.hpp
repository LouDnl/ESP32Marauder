#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Deserialization\\DeserializationError.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Misc/SafeBoolIdiom.hpp>
#include <ArduinoJson/Namespace.hpp>
#include <ArduinoJson/Polyfills/preprocessor.hpp>
#include <ArduinoJson/Polyfills/static_array.hpp>

#if ARDUINOJSON_ENABLE_STD_STREAM
#  include <ostream>
#endif

namespace ARDUINOJSON_NAMESPACE {

class DeserializationError : public SafeBoolIdom<DeserializationError> {
 public:
  enum Code {
    Ok,
    EmptyInput,
    IncompleteInput,
    InvalidInput,
    NoMemory,
    TooDeep
  };

  DeserializationError() {}
  DeserializationError(Code c) : _code(c) {}

  // Compare with DeserializationError
  friend bool operator==(const DeserializationError& lhs,
                         const DeserializationError& rhs) {
    return lhs._code == rhs._code;
  }
  friend bool operator!=(const DeserializationError& lhs,
                         const DeserializationError& rhs) {
    return lhs._code != rhs._code;
  }

  // Compare with Code
  friend bool operator==(const DeserializationError& lhs, Code rhs) {
    return lhs._code == rhs;
  }
  friend bool operator==(Code lhs, const DeserializationError& rhs) {
    return lhs == rhs._code;
  }
  friend bool operator!=(const DeserializationError& lhs, Code rhs) {
    return lhs._code != rhs;
  }
  friend bool operator!=(Code lhs, const DeserializationError& rhs) {
    return lhs != rhs._code;
  }

  // Behaves like a bool
  operator bool_type() const {
    return _code != Ok ? safe_true() : safe_false();
  }

  // Returns internal enum, useful for switch statement
  Code code() const {
    return _code;
  }

  const char* c_str() const {
    static const char* messages[] = {
        "Ok",           "EmptyInput", "IncompleteInput",
        "InvalidInput", "NoMemory",   "TooDeep"};
    ARDUINOJSON_ASSERT(static_cast<size_t>(_code) <
                       sizeof(messages) / sizeof(messages[0]));
    return messages[_code];
  }

#if ARDUINOJSON_ENABLE_PROGMEM
  const __FlashStringHelper* f_str() const {
    ARDUINOJSON_DEFINE_STATIC_ARRAY(char, s0, "Ok");
    ARDUINOJSON_DEFINE_STATIC_ARRAY(char, s1, "EmptyInput");
    ARDUINOJSON_DEFINE_STATIC_ARRAY(char, s2, "IncompleteInput");
    ARDUINOJSON_DEFINE_STATIC_ARRAY(char, s3, "InvalidInput");
    ARDUINOJSON_DEFINE_STATIC_ARRAY(char, s4, "NoMemory");
    ARDUINOJSON_DEFINE_STATIC_ARRAY(char, s5, "TooDeep");
    ARDUINOJSON_DEFINE_STATIC_ARRAY(
        const char*, messages, ARDUINOJSON_EXPAND6({s0, s1, s2, s3, s4, s5}));
    return ARDUINOJSON_READ_STATIC_ARRAY(const __FlashStringHelper*, messages,
                                         _code);
  }
#endif

 private:
  Code _code;
};

#if ARDUINOJSON_ENABLE_STD_STREAM
inline std::ostream& operator<<(std::ostream& s,
                                const DeserializationError& e) {
  s << e.c_str();
  return s;
}

inline std::ostream& operator<<(std::ostream& s, DeserializationError::Code c) {
  s << DeserializationError(c).c_str();
  return s;
}
#endif

}  // namespace ARDUINOJSON_NAMESPACE
