#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\extras\\tests\\JsonObject\\isNull.cpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("JsonObject::isNull()") {
  SECTION("returns true") {
    JsonObject obj;
    REQUIRE(obj.isNull() == true);
  }

  SECTION("returns false") {
    DynamicJsonDocument doc(4096);
    JsonObject obj = doc.to<JsonObject>();
    REQUIRE(obj.isNull() == false);
  }
}

TEST_CASE("JsonObjectConst::isNull()") {
  SECTION("returns true") {
    JsonObjectConst obj;
    REQUIRE(obj.isNull() == true);
  }

  SECTION("returns false") {
    DynamicJsonDocument doc(4096);
    JsonObjectConst obj = doc.to<JsonObject>();
    REQUIRE(obj.isNull() == false);
  }
}

TEST_CASE("JsonObject::operator bool()") {
  SECTION("returns false") {
    JsonObject obj;
    REQUIRE(static_cast<bool>(obj) == false);
  }

  SECTION("returns true") {
    DynamicJsonDocument doc(4096);
    JsonObject obj = doc.to<JsonObject>();
    REQUIRE(static_cast<bool>(obj) == true);
  }
}

TEST_CASE("JsonObjectConst::operator bool()") {
  SECTION("returns false") {
    JsonObjectConst obj;
    REQUIRE(static_cast<bool>(obj) == false);
  }

  SECTION("returns true") {
    DynamicJsonDocument doc(4096);
    JsonObjectConst obj = doc.to<JsonObject>();
    REQUIRE(static_cast<bool>(obj) == true);
  }
}
