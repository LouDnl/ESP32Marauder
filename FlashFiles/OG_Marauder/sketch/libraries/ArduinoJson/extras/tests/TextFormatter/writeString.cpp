#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\extras\\tests\\TextFormatter\\writeString.cpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#include <catch.hpp>

#include <ArduinoJson/Json/TextFormatter.hpp>
#include <ArduinoJson/Serialization/Writers/StaticStringWriter.hpp>

using namespace ARDUINOJSON_NAMESPACE;

void check(const char* input, std::string expected) {
  char output[64] = {0};
  StaticStringWriter sb(output, sizeof(output));
  TextFormatter<StaticStringWriter> writer(sb);
  writer.writeString(input);
  REQUIRE(expected == output);
  REQUIRE(writer.bytesWritten() == expected.size());
}

TEST_CASE("TextFormatter::writeString()") {
  SECTION("EmptyString") {
    check("", "\"\"");
  }

  SECTION("QuotationMark") {
    check("\"", "\"\\\"\"");
  }

  SECTION("ReverseSolidus") {
    check("\\", "\"\\\\\"");
  }

  SECTION("Solidus") {
    check("/", "\"/\"");  // but the JSON format allows \/
  }

  SECTION("Backspace") {
    check("\b", "\"\\b\"");
  }

  SECTION("Formfeed") {
    check("\f", "\"\\f\"");
  }

  SECTION("Newline") {
    check("\n", "\"\\n\"");
  }

  SECTION("CarriageReturn") {
    check("\r", "\"\\r\"");
  }

  SECTION("HorizontalTab") {
    check("\t", "\"\\t\"");
  }
}
