#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\extras\\tests\\MsgPackDeserializer\\misc.cpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("deserializeMsgPack() returns EmptyInput") {
  StaticJsonDocument<100> doc;

  SECTION("from sized buffer") {
    DeserializationError err = deserializeMsgPack(doc, "", 0);

    REQUIRE(err == DeserializationError::EmptyInput);
  }

  SECTION("from stream") {
    std::istringstream input("");

    DeserializationError err = deserializeMsgPack(doc, input);

    REQUIRE(err == DeserializationError::EmptyInput);
  }
}
