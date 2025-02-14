#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\esp_interface.h"
#ifndef esp_interface_h
#define esp_interface_h

#include "configs.h"

#ifdef HAS_SCREEN
  #include "Display.h"
#endif

#include <HardwareSerial.h>

#define ESP_RST  14
#define ESP_ZERO 13
#define BAUD     115200

#ifdef HAS_SCREEN
  extern Display display_obj;
#endif

class EspInterface {
  public:
    bool supported = false;

    uint32_t initTime;

    void RunUpdate();
    void bootProgramMode();
    void bootRunMode();
    void begin();

    void program();
    void main(uint32_t current_time);
};

#endif
