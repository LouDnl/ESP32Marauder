#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\extras\\tests\\Cpp11\\use_long_long_1.cpp"
#define ARDUINOJSON_USE_LONG_LONG 1
#include <ArduinoJson.h>

#include <catch.hpp>

TEST_CASE("ARDUINOJSON_USE_LONG_LONG == 1") {
  DynamicJsonDocument doc(4096);
  JsonObject root = doc.to<JsonObject>();

  root["A"] = 123456789123456789;
  root["B"] = 987654321987654321;

  std::string json;
  serializeJson(doc, json);

  REQUIRE(json == "{\"A\":123456789123456789,\"B\":987654321987654321}");
}
