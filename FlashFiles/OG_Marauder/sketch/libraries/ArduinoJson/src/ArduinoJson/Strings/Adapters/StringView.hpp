#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Strings\\Adapters\\StringView.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Strings/Adapters/RamString.hpp>

#include <string_view>

namespace ARDUINOJSON_NAMESPACE {

template <>
struct StringAdapter<std::string_view, void> {
  typedef SizedRamString AdaptedString;

  static AdaptedString adapt(const std::string_view& s) {
    return AdaptedString(s.data(), s.size());
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
