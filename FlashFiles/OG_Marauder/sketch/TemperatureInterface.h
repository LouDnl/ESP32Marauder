#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\TemperatureInterface.h"
#ifndef TemperatureInterface_h
#define TemperatureInterface_h

#include "configs.h"

#include <Arduino.h>

class TemperatureInterface {

  private:
    uint32_t initTime = 0;
    
  public:
    TemperatureInterface();

    uint8_t current_temp = 0;
    uint8_t old_temp = 0;

    uint8_t getCurrentTemp();
    void RunSetup();
    void main(uint32_t currentTime);
};

#endif
