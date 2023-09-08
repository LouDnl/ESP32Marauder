#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Array\\ArrayFunctions.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Collection/CollectionData.hpp>

namespace ARDUINOJSON_NAMESPACE {

inline VariantData* arrayAdd(CollectionData* arr, MemoryPool* pool) {
  return arr ? arr->addElement(pool) : 0;
}

}  // namespace ARDUINOJSON_NAMESPACE
