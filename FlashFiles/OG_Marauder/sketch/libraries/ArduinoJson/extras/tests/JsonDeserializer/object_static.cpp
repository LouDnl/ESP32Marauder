#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\extras\\tests\\JsonDeserializer\\object_static.cpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("deserialize JSON object with StaticJsonDocument") {
  SECTION("BufferOfTheRightSizeForEmptyObject") {
    StaticJsonDocument<JSON_OBJECT_SIZE(0)> doc;
    char input[] = "{}";

    DeserializationError err = deserializeJson(doc, input);

    REQUIRE(err == DeserializationError::Ok);
  }

  SECTION("TooSmallBufferForObjectWithOneValue") {
    StaticJsonDocument<JSON_OBJECT_SIZE(0)> doc;
    char input[] = "{\"a\":1}";

    DeserializationError err = deserializeJson(doc, input);

    REQUIRE(err == DeserializationError::NoMemory);
  }

  SECTION("BufferOfTheRightSizeForObjectWithOneValue") {
    StaticJsonDocument<JSON_OBJECT_SIZE(1)> doc;
    char input[] = "{\"a\":1}";

    DeserializationError err = deserializeJson(doc, input);

    REQUIRE(err == DeserializationError::Ok);
  }

  SECTION("TooSmallBufferForObjectWithNestedObject") {
    StaticJsonDocument<JSON_OBJECT_SIZE(0) + JSON_ARRAY_SIZE(0)> doc;
    char input[] = "{\"a\":[]}";

    DeserializationError err = deserializeJson(doc, input);

    REQUIRE(err == DeserializationError::NoMemory);
  }

  SECTION("BufferOfTheRightSizeForObjectWithNestedObject") {
    StaticJsonDocument<JSON_OBJECT_SIZE(1) + JSON_ARRAY_SIZE(0)> doc;
    char input[] = "{\"a\":[]}";

    DeserializationError err = deserializeJson(doc, input);

    REQUIRE(err == DeserializationError::Ok);
  }

  SECTION("Should clear the JsonObject") {
    StaticJsonDocument<JSON_OBJECT_SIZE(1)> doc;
    char input[] = "{\"hello\":\"world\"}";

    deserializeJson(doc, input);
    deserializeJson(doc, "{}");

    REQUIRE(doc.as<JsonObject>().size() == 0);
    REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(0));
  }
}
