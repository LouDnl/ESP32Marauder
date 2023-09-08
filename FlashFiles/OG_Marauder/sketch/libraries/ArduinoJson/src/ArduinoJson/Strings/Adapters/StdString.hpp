#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Strings\\Adapters\\StdString.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Strings/Adapters/RamString.hpp>

#include <string>

namespace ARDUINOJSON_NAMESPACE {

template <typename TCharTraits, typename TAllocator>
struct StringAdapter<std::basic_string<char, TCharTraits, TAllocator>, void> {
  typedef SizedRamString AdaptedString;

  static AdaptedString adapt(
      const std::basic_string<char, TCharTraits, TAllocator>& s) {
    return AdaptedString(s.c_str(), s.size());
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
