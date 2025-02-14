#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Document\\StaticJsonDocument.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Document/JsonDocument.hpp>

namespace ARDUINOJSON_NAMESPACE {

template <size_t desiredCapacity>
class StaticJsonDocument : public JsonDocument {
  static const size_t _capacity =
      AddPadding<Max<1, desiredCapacity>::value>::value;

 public:
  StaticJsonDocument() : JsonDocument(_buffer, _capacity) {}

  StaticJsonDocument(const StaticJsonDocument& src)
      : JsonDocument(_buffer, _capacity) {
    set(src);
  }

  template <typename T>
  StaticJsonDocument(
      const T& src,
      typename enable_if<is_convertible<T, VariantConstRef>::value>::type* = 0)
      : JsonDocument(_buffer, _capacity) {
    set(src);
  }

  // disambiguate
  StaticJsonDocument(VariantRef src) : JsonDocument(_buffer, _capacity) {
    set(src);
  }

  StaticJsonDocument& operator=(const StaticJsonDocument& src) {
    set(src);
    return *this;
  }

  template <typename T>
  StaticJsonDocument& operator=(const T& src) {
    set(src);
    return *this;
  }

  void garbageCollect() {
    StaticJsonDocument tmp(*this);
    set(tmp);
  }

 private:
  char _buffer[_capacity];
};

}  // namespace ARDUINOJSON_NAMESPACE
