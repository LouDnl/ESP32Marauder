#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\Display.h"
#ifndef Display_h
#define Display_h

#include "configs.h"

#ifdef HAS_SCREEN

#include <FS.h>
#include <functional>
#include <JPEGDecoder.h>
//#include <SimpleList.h>
#include <LinkedList.h>
#include <SPI.h>
#include <lvgl.h>
#include <Ticker.h>
//#include <M5Stack.h>
#include "SPIFFS.h"
#include "Assets.h"

#include <TFT_eSPI.h>

// WiFi stuff
#define OTA_UPDATE 100
#define SHOW_INFO 101
#define WIFI_SCAN_OFF 0
#define WIFI_SCAN_PROBE 1
#define WIFI_SCAN_AP 2
#define WIFI_SCAN_PWN 3
#define WIFI_SCAN_EAPOL 4
#define WIFI_SCAN_DEAUTH 5
#define WIFI_SCAN_ALL 6
#define WIFI_PACKET_MONITOR 7
#define WIFI_ATTACK_BEACON_SPAM 8
#define WIFI_ATTACK_RICK_ROLL 9
#define BT_SCAN_ALL 10
#define BT_SCAN_SKIMMERS 11
#define WIFI_SCAN_ESPRESSIF 12
#define LV_JOIN_WIFI 13
#define LV_ADD_SSID 14
#define WIFI_ATTACK_BEACON_LIST 15

/*
PROGMEM void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
PROGMEM bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data);

PROGMEM static lv_disp_buf_t disp_buf;
PROGMEM static lv_color_t buf[LV_HOR_RES_MAX * 10];

PROGMEM static void ta_event_cb(lv_obj_t * ta, lv_event_t event);
PROGMEM static void keyboard_event_cb(lv_obj_t * keyboard, lv_event_t event);

// lvgl stuff
PROGMEM static lv_obj_t *kb;
*/

// #define KIT
// #define TFT_DIY

class Display
{
  private:
    bool SwitchOn = false;
    
    bool run_setup = true;
    
    // For the byte we read from the serial port
    byte data = 0;
    
    // A few test variables used during debugging
    boolean change_colour = 1;
    boolean selected = 1;

    void drawFrame();

    #ifdef SCREEN_BUFFER
      void scrollScreenBuffer(bool down = false);
    #endif

    //void addNodes(Menu* menu, String name, Menu* child, std::function<void()> callable);
    //void changeMenu(Menu* menu);
    //void showMenuList(Menu* menu, int layer);
    //static void lv_tick_handler();

  public:
    Display();
    //Ticker tick;
    TFT_eSPI tft = TFT_eSPI();
    TFT_eSprite img = TFT_eSprite(&tft);
    TFT_eSPI_Button key[BUTTON_ARRAY_LEN];
    const String PROGMEM version_number = MARAUDER_VERSION;

    bool printing = false;
    bool loading = false;
    bool tteBar = false;
    bool draw_tft = false;
    bool exit_draw = false;

    int TOP_FIXED_AREA_2 = 48;
    int print_delay_1, print_delay_2 = 10;
    int current_banner_pos = SCREEN_WIDTH;

    //Menu* current_menu;
    
    //Menu mainMenu;
    //Menu wifiMenu;
    //Menu bluetoothMenu;

    LinkedList<String>* display_buffer;

    #ifdef SCREEN_BUFFER
      LinkedList<String>* screen_buffer;
    #endif

    // The initial y coordinate of the top of the bottom text line
    uint16_t yDraw = YMAX - BOT_FIXED_AREA - TEXT_HEIGHT;

    // Keep track of the drawing x coordinate
    uint16_t xPos = 0;

    // The initial y coordinate of the top of the scrolling area
    uint16_t yStart = TOP_FIXED_AREA_2;
    // yArea must be a integral multiple of TEXT_HEIGHT
    uint16_t yArea = YMAX - TOP_FIXED_AREA_2 - BOT_FIXED_AREA;

    // We have to blank the top line each time the display is scrolled, but this takes up to 13 milliseconds
    // for a full width line, meanwhile the serial buffer may be filling... and overflowing
    // We can speed up scrolling of short text lines by just blanking the character we drew
    int blank[19]; // We keep all the strings pixel lengths to optimise the speed of the top line blanking

    //void initLVGL();
    //void deinitLVGL();
    //void joinWiFiGFX();
    void tftDrawRedOnOffButton();
    void tftDrawGreenOnOffButton();
    void tftDrawGraphObjects(byte x_scale);
    void tftDrawEapolColorKey();
    void tftDrawColorKey();
    void tftDrawXScaleButtons(byte x_scale);
    void tftDrawYScaleButtons(byte y_scale);
    void tftDrawChannelScaleButtons(int set_channel);
    void tftDrawExitScaleButtons();
    void buildBanner(String msg, int xpos);
    void clearScreen();
    void displayBuffer(bool do_clear = false);
    void drawJpeg(const char *filename, int xpos, int ypos);
    void setupDraw();
    void drawStylus();
    void getTouchWhileFunction(bool pressed);
    void initScrollValues(bool tte = false);
    void jpegInfo();
    void jpegRender(int xpos, int ypos);
    void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    void listFiles();
    void main(uint8_t scan_mode);
    void RunSetup();
    void scrollAddress(uint16_t vsp);
    int scroll_line(uint32_t color);
    void setupScrollArea(uint16_t tfa, uint16_t bfa);
    void showCenterText(String text, int y);
    void touchToExit();
    void twoPartDisplay(String center_text);
    void updateBanner(String msg);
};
#endif
#endif
