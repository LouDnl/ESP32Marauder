#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\TFT_eSPI\\User_Setups\\Setup31_ST7796_Parallel_STM32.h"
        ///////////////////////////////////////////////////
        // Setup for Nucleo-F446/767 and ILI9341 display //
        ///////////////////////////////////////////////////
        
// See SetupX_Template.h for all options available

// Define STM32 to invoke optimised processor support
#define STM32

// Defining the board allows the library to optimise the performance
// for UNO compatible "MCUfriend" style shields
#define NUCLEO_64_TFT
//#define NUCLEO_144_TFT

// Tell the library to use 8 bit parallel mode(otherwise SPI is assumed)
#define TFT_PARALLEL_8_BIT

// Define the display driver chip type
#define ST7796_DRIVER
//#define ILI9481_DRIVER

// Define the Nucleo 64/144 pins used for the parallel interface TFT
// The pins can be changed here but these are the ones used by the
// common "MCUfriend" shields
#define TFT_CS   A3  // Chip select control pin
#define TFT_DC   A2  // Data Command control pin
#define TFT_RST  A4  // Reset pin

#define TFT_WR   A1  // Write strobe control pin 
#define TFT_RD   A0  // Read pin

#define TFT_D0   D8  // 8 bit parallel bus to TFT
#define TFT_D1   D9
#define TFT_D2   D2
#define TFT_D3   D3
#define TFT_D4   D4
#define TFT_D5   D5
#define TFT_D6   D6
#define TFT_D7   D7

// Fonts to be available
#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// At the moment SMOOTH fonts must be disabled for STM32 processors (due to lack of SPIFFS)
// Support for smooth fonts via SD cards is planned.
//#define SMOOTH_FONT
