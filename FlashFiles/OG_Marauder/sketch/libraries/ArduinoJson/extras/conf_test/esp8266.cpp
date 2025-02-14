#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\extras\\conf_test\\esp8266.cpp"
#include <ArduinoJson.h>

static_assert(ARDUINOJSON_USE_LONG_LONG == 1, "ARDUINOJSON_USE_LONG_LONG");

static_assert(ARDUINOJSON_SLOT_OFFSET_SIZE == 2,
              "ARDUINOJSON_SLOT_OFFSET_SIZE");

static_assert(ARDUINOJSON_LITTLE_ENDIAN == 1, "ARDUINOJSON_LITTLE_ENDIAN");

static_assert(ARDUINOJSON_USE_DOUBLE == 1, "ARDUINOJSON_USE_DOUBLE");

static_assert(sizeof(ARDUINOJSON_NAMESPACE::VariantSlot) == 16,
              "sizeof(VariantSlot)");

void setup() {}
void loop() {}
