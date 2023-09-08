#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\extras\\tests\\FailingBuilds\\assign_char.cpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#include <ArduinoJson.h>

// See issue #1498

int main() {
  DynamicJsonDocument doc(1024);
  doc["dummy"] = 'A';
}
