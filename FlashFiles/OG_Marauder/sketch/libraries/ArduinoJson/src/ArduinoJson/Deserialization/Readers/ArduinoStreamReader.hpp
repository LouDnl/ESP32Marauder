#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Deserialization\\Readers\\ArduinoStreamReader.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <Arduino.h>

namespace ARDUINOJSON_NAMESPACE {

template <typename TSource>
struct Reader<TSource,
              typename enable_if<is_base_of<Stream, TSource>::value>::type> {
 public:
  explicit Reader(Stream& stream) : _stream(&stream) {}

  int read() {
    // don't use _stream.read() as it ignores the timeout
    char c;
    return _stream->readBytes(&c, 1) ? static_cast<unsigned char>(c) : -1;
  }

  size_t readBytes(char* buffer, size_t length) {
    return _stream->readBytes(buffer, length);
  }

 private:
  Stream* _stream;
};

}  // namespace ARDUINOJSON_NAMESPACE
