#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Deserialization\\Readers\\StdStreamReader.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <istream>

namespace ARDUINOJSON_NAMESPACE {

template <typename TSource>
struct Reader<TSource, typename enable_if<
                           is_base_of<std::istream, TSource>::value>::type> {
 public:
  explicit Reader(std::istream& stream) : _stream(&stream) {}

  int read() {
    return _stream->get();
  }

  size_t readBytes(char* buffer, size_t length) {
    _stream->read(buffer, static_cast<std::streamsize>(length));
    return static_cast<size_t>(_stream->gcount());
  }

 private:
  std::istream* _stream;
};
}  // namespace ARDUINOJSON_NAMESPACE
