#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\SDInterface.h"
#ifndef SDInterface_h
#define SDInterface_h

#include "configs.h"

#include "settings.h"
#include "SD.h"
#include "Buffer.h"
#ifdef HAS_SCREEN
  #include "Display.h"
#endif
#include <Update.h>

extern Buffer buffer_obj;
extern Settings settings_obj;
#ifdef HAS_SCREEN
  extern Display display_obj;
#endif

#ifdef KIT
  #define SD_DET 4
#endif

class SDInterface {

  private:
    bool checkDetectPin();

  public:
    uint8_t cardType;
    //uint64_t cardSizeBT;
    //uint64_t cardSizeKB;
    uint64_t cardSizeMB;
    //uint64_t cardSizeGB;
    bool supported = false;
    bool do_save = true;

    String card_sz;
  
    bool initSD();

    void listDir(String str_dir);
    File getFile(String path);
    void addPacket(uint8_t* buf, uint32_t len, bool log = false);
    void openCapture(String file_name = "");
    void openLog(String file_name = "");
    void runUpdate();
    void performUpdate(Stream &updateSource, size_t updateSize);
    void main();
    //void savePacket(uint8_t* buf, uint32_t len);
};

#endif
