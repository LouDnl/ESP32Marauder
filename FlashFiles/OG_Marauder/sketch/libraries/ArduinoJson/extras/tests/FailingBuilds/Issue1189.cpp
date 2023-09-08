#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\extras\\tests\\FailingBuilds\\Issue1189.cpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#include <ArduinoJson.h>

// a function should not be able to get a JsonDocument by value
void f(JsonDocument) {}

int main() {
  DynamicJsonDocument doc(1024);
  f(doc);
}
