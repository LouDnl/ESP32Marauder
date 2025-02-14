#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\TFT_eSPI\\examples\\Generic\\drawXBitmap\\xbm.h"
// Images can be converted to XBM format by using the online converter here:
// https://www.online-utility.org/image/convert/to/XBM

// The output must be pasted in a header file, renamed and adjusted to appear
// as as a const unsigned char array in PROGMEM (FLASH program memory).

// The xbm format adds padding to pixel rows so they are a whole number of bytes
// In this example 50 pixel width means 56 bits = 7 bytes
// the 50 height then means array uses 50 x 7 = 350 bytes of FLASH
// The library ignores the padding bits when drawing the image on the display.

// Example of the correct format is shown below

#include <pgmspace.h>  // PROGMEM support header

// Espressif logo 50 x 50 pixel array in XBM format
#define logoWidth  50  // logo width
#define logoHeight 50  // logo height

// Image is stored in this array
PROGMEM const unsigned char logo[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00, 
  0x00, 0x00, 0x00, 0x07, 0xFC, 0x07, 0x00, 0x00, 0x00, 0x82, 0x7F, 0xF0, 
  0x1F, 0x00, 0x00, 0x00, 0xC6, 0xFF, 0xC3, 0x3F, 0x00, 0x00, 0x00, 0xE7, 
  0xFF, 0x8F, 0x7F, 0x00, 0x00, 0x80, 0xE3, 0xFF, 0x1F, 0xFE, 0x00, 0x00, 
  0x80, 0xE1, 0xFF, 0x7F, 0xFC, 0x01, 0x00, 0xC0, 0x00, 0xFF, 0xFF, 0xF8, 
  0x03, 0x00, 0xE0, 0x00, 0xE0, 0xFF, 0xF1, 0x03, 0x00, 0x60, 0xF0, 0x81, 
  0xFF, 0xE3, 0x07, 0x00, 0x60, 0xFC, 0x1F, 0xFE, 0xC7, 0x07, 0x00, 0x30, 
  0xFE, 0x7F, 0xF8, 0x8F, 0x0F, 0x00, 0x30, 0xFF, 0xFF, 0xF1, 0x9F, 0x0F, 
  0x00, 0xB0, 0xFF, 0xFF, 0xE3, 0x3F, 0x0F, 0x00, 0xB0, 0xFF, 0xFF, 0xC7, 
  0x3F, 0x1E, 0x00, 0xB8, 0xFF, 0xFF, 0x8F, 0x7F, 0x1E, 0x00, 0x98, 0x1F, 
  0xFC, 0x3F, 0xFF, 0x1C, 0x00, 0xB8, 0x3F, 0xE0, 0x3F, 0xFE, 0x1C, 0x00, 
  0x98, 0xFF, 0xC3, 0x7F, 0xFE, 0x19, 0x00, 0x98, 0xFF, 0x0F, 0xFF, 0xFC, 
  0x19, 0x00, 0x38, 0xFF, 0x3F, 0xFF, 0xFC, 0x01, 0x00, 0x30, 0xFE, 0x7F, 
  0xFE, 0xF9, 0x03, 0x00, 0x30, 0xFC, 0xFF, 0xFC, 0xF9, 0x03, 0x00, 0x30, 
  0xF8, 0xFF, 0xF8, 0xF3, 0x03, 0x00, 0x30, 0x00, 0xFF, 0xF9, 0xF3, 0x03, 
  0x00, 0x70, 0x00, 0xFC, 0xF9, 0xF3, 0x07, 0x00, 0x60, 0x00, 0xF8, 0xF3, 
  0xF3, 0x07, 0x00, 0xE0, 0xF8, 0xF8, 0xF3, 0xF7, 0x03, 0x00, 0xC0, 0xF8, 
  0xF1, 0xF3, 0xE3, 0x03, 0x00, 0xC0, 0xFD, 0xF1, 0xF3, 0xF7, 0x01, 0x00, 
  0x80, 0xFD, 0xF1, 0xF3, 0xE7, 0x00, 0x00, 0x00, 0xFF, 0xF1, 0xF3, 0x07, 
  0x00, 0x00, 0x00, 0xFF, 0xF8, 0xF3, 0x07, 0x00, 0x00, 0x00, 0x7E, 0xF8, 
  0xF3, 0x83, 0x03, 0x00, 0x00, 0x3C, 0xF8, 0xF3, 0xC3, 0x01, 0x00, 0x00, 
  0x70, 0xF8, 0xF9, 0xE3, 0x00, 0x00, 0x00, 0xE0, 0xE1, 0x41, 0x78, 0x00, 
  0x00, 0x00, 0xC0, 0x0F, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFD, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 
  0x80, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, };

