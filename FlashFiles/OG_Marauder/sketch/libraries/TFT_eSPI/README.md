#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\TFT_eSPI\\README.md"
# Tips
If you load a new copy of TFT_eSPI then it will over-write your setups if they are kept within the TFT_eSPI folder. One way around this is to create a new folder in your Arduino library folder called "TFT_eSPI_Setups". You then place your custom setup.h files in there. After an upgrade simply edit the User_Setup_Select.h file to point to your custom setup file e.g.:
```
#include <../TFT_eSPI_Setups/my_custom_setup.h>
```
You must make sure only one setup file is called. In the the custom setup file I add the file path as a commented out first line that can be cut and pasted back into the upgraded User_Setup_Select.h file.  The ../ at the start of the path means go up one directory level. Clearly you could use different file paths or directory names as long as it does not clash with another library or folder name.

You can take this one step further and have your own setup select file and then you only need to replace the Setup.h line reference in User_Setup_Select.h to, for example:
```
#include <../TFT_eSPI_Setups/my_setup_select.h>
```
To select a new setup you then edit your own my_setup_select.h file (which will not get over-written during an upgrade).

# News
1. The Sprite class now supports 4 bits per pixel with a 16 color palette. Three new examples have been added.

2. The library has been upgraded to support STM32 processors when used with SPI or 8 bit parallel displays. DMA capability for SPI displays has been added for STM32F103 (e.g. "Blue Pill") and STM32F2xx/4xx/7xx (e.g. 32/64/144 Nucleo boards). New DMA demo examples have been added (for STM32 only). Smooth (anti-aliased) fonts are not yet supported for STM32 processors due to the lack of SPIFFS, support for smooth fonts using SD cards will be added at a future date.

3. The ST7796 display controller has been added. The ST7796 RPi MHS-4.0 inch Display-B type display is supported (this is fast for a SPI display as an ESP32 can clock it at 80MHz (ESP8266 at 40MHz)), see setups 27 and 28.

4. A callback function has been added, this allows antialiased fonts to be rendered over colour gradients or images. Two new examples have been added to illustrate this new capability:

           "Smooth_font_reading_TFT"
    
           "Smooth_font_gradient"
           
      ![AA_gradien](https://i.imgur.com/YMBcPHp.png)
    
5. Sprites can now by pushed to the screen (or another Sprite) with a rotation angle. The new function is pushRotated(). Three new examples (Rotate_Sprite_1/2/3) have been added to show how the functions can be used to rotate text, images and to draw animated dials with moving needles.

6. A new TFT_eFEX support library has been created which includes extra functions such as drawing a BMP or Jpeg to the screen. This library will simplify the examples. It will be expanded at a future date to include meters, dials and GUI elements like progress bars, graphs and animated buttons:
https://github.com/Bodmer/TFT_eFEX


# TFT_eSPI

An Arduino IDE compatible graphics and fonts library for ESP8266 and ESP32 processors with drivers for ILI9341, ILI9163, ST7735, S6D02A1, ILI9481, ILI9486, ILI9488, HX8357D, ST7789 and ST7796 based TFT displays that support SPI. The library can be loaded using the Arduino IDE's Library Manager.

8 bit parallel interface TFTs  (e.g. UNO format mcufriend shields) can used with an ESP32.

The library supports TFT displays designed for the Raspberry Pi (RPi) that are based on a ILI9486 or ST7796 driver chip with a 480 x 320 pixel screen. The ILI9486 RPi display must be of the Waveshare design and use a 16 bit serial interface based on the 74HC04, 74HC4040 and 2 x 74HC4094 logic chips. A modification to these displays is possible (see mod image in Tools folder) to make many graphics functions much faster (e.g. 23ms to clear the screen, 1.2ms to draw a 72 pixel high numeral). The RPi ST7796 display is superior to the Waveshare design, it must be of the MHS-4.0 inch Display-B type.

Some displays permit the internal TFT screen RAM to be read. The library supports reading from ILI9341, ST7789 and ILI9488 SPI displays for the ESP32 and ESP8266. The 8 bit parallel displays used with the ESP32 can usually can be read too. The TFT_Screen_Capture example allows full screens to be captured and sent to a PC, this is handy to create program documentation.

Support has been added recently for Waveshare 2 and 3 colour ePaper displays using full frame buffers. This addition is currently relatively immature and thus only one example has been provided. Further examples will be added soon.

The library includes a "Sprite" class, this enables flicker free updates of complex graphics. Direct writes to the TFT with graphics functions are still available, so existing sketches do not need to be changed.

A Sprite is notionally an invisible graphics screen that is kept in the processors RAM. Graphics can be drawn into the Sprite just as they can be drawn directly to the screen. Once the Sprite is completed it can be plotted onto the screen in any position. If there is sufficient RAM then the Sprite can be the same size as the screen and used as a frame buffer. Sprites by default use 16 bit colours, the bit depth can be set to 8 bits (256 colours) , or 1 bit (any 2 colours) to reduce the RAM needed. On an ESP8266 the largest 16 bit colour Sprite that can be created is about 160x128 pixels, this consumes 40Kbytes of RAM. On an ESP32 the workspace RAM is more limited than the datsheet implies so a 16 bit colour Sprite is limited to about 200x200 pixels (~80Kbytes), an 8 bit sprite to 320x240 pixels (~76kbytes). A 1 bit per pixel Sprite requires only 9600 bytes for a full 320 x 240 screen buffer, this is ideal for supporting use with 2 colour bitmap fonts.

One or more sprites can be created, a sprite can be any pixel width and height, limited only by available RAM. The RAM needed for a 16 bit colour depth Sprite is (2 x width x height) bytes, for a Sprite with 8 bit colour depth the RAM needed is (width x height) bytes. Sprites can be created and deleted dynamically as needed in the sketch, this means RAM can be freed up after the Sprite has been plotted on the screen, more RAM intensive WiFi based code can then be run and normal graphics operations still work.

Drawing graphics into a sprite is very fast, for those familiar with the Adafruit "graphicstest" example, this whole test completes in 18ms in a 160x128 sprite. Examples of sprite use can be found in the "examples/Sprite" folder.

Sprites can be plotted to the TFT with one colour being specified as "transparent", see Transparent_Sprite_Demo example.

If an ESP32 board has SPIRAM (i.e. PSRAM) fitted then Sprites will use the PSRAM memory and large full screen buffer Sprites can be created. Full screen Sprites take longer to render (~45ms for a 320 x 240 16 bit Sprite), so bear that in mind.

The XPT2046 touch screen controller is supported. The SPI bus for the touch controller is shared with the TFT and only an additional chip select line is needed.

The Button class from Adafruit_GFX is incorporated, with the enhancement that the button labels can be in any font.

The library supports SPI overlap on the ESP8266 so the TFT screen can share MOSI, MISO and SCLK pins with the program FLASH, this frees up GPIO pins for other uses.

The library contains proportional fonts, different sizes can be enabled/disabled at compile time to optimise the use of FLASH memory. Anti-alased (smooth) font files in vlw format stored in SPIFFS are supported. Any 16 bit Unicode character can be included and rendered, this means many language specific characters can be rendered to the screen.

The library is based on the Adafruit GFX and Adafruit driver libraries and the aim is to retain compatibility. Significant additions have been made to the library to boost the speed for ESP8266/ESP32 processors (it is typically 3 to 10 times faster) and to add new features. The new graphics functions include different size proportional fonts and formatting features. There are lots of example sketches to demonstrate the different features and included functions.

Configuration of the library font selections, pins used to interface with the TFT and other features is made by editting the User_Setup.h file in the library folder, or by selecting your own configuration in the "User_Setup_Selet,h" file.  Fonts and features can easily be enabled/disabled by commenting out lines.


# Anti-aliased Fonts

Anti-aliased (smooth) font files in "vlw" format are generated by the free [Processing IDE](https://processing.org/) using a sketch included in the library Tools folder. This sketch with the Processing IDE can be used to generate font files from your computer's font set or any TrueType (.ttf) font, the font file can include **any** combination of 16 bit Unicode characters. This means Greek, Japanese and any other UCS-2 glyphs can be used. Character arrays and Strings in UTF-8 format are supported.

Here is the Adafruit_GFX "FreeSans12pt" bitmap font compared to the same font drawn as anti-aliased:

![Smooth_font](https://i.imgur.com/gAeDPFY.png)

The smooth font example displays the following screen:

![Example](https://i.imgur.com/xJF0Oz7.png)

It would be possible to compress the vlw font files but the rendering performance to a TFT is still good when storing the font file(s) in SPIFFS.

Here is an example screenshot showing the anti-aliased Hiragana character Unicode block (0x3041 to 0x309F) in 24pt from the Microsoft Yahei font:

![Hiragana glyphs](https://i.imgur.com/jeXf2st.png)

Antialiased fonts can also be drawn over a gradient background with a callback to fetch the background colour of each pixel. This pixel colour can be set by the gradient algorithm or by reading back the TFT screen memory (if reading the display is supported).

# ESP32 with 8 bit Mcufriend UNO shields

The ESP32 board I have been using for testing has the following pinout:

![Example](https://i.imgur.com/bvM6leE.jpg)

UNO style boards with a Wemos R32(ESP32) label are also available at low cost with the same pin-out.

Unfortunately the typical UNO/mcufriend TFT display board maps LCD_RD, LCD_CS and LCD_RST signals to the ESP32 analogue pins 35, 34 and 36 which are input only.  To solve this I linked in the 3 spare pins IO15, IO33 and IO32 by adding wires to the bottom of the board as follows:

IO15 wired to IO35

IO33 wired to IO34

IO32 wired to IO36

![Example](https://i.imgur.com/pUZn6lF.jpg)

If the display board is fitted with a resistance based touch screen then this can be used by performing the modifications described here and the fork of the Adafruit library:
https://github.com/s60sc/Adafruit_TouchScreen

# ePaper displays

The library was intended to support only TFT displays but using a Sprite as a 1 bit per pixel screen buffer permits support for the Waveshare 2 and 3 colour SPI ePaper displays. This addition to the library is experimental and only one example is provided. Further examples will be added.

![Example](https://i.imgur.com/L2tV129.jpg?1)

