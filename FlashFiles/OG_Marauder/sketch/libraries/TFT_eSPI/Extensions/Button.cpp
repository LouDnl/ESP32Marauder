#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\TFT_eSPI\\Extensions\\Button.cpp"
/***************************************************************************************
** Code for the GFX button UI element
** Grabbed from Adafruit_GFX library and enhanced to handle any label font
***************************************************************************************/
TFT_eSPI_Button::TFT_eSPI_Button(void) {
  _gfx       = 0;
  _xd        = 0;
  _yd        = 0;
  _textdatum = MC_DATUM;
}

// Classic initButton() function: pass center & size
void TFT_eSPI_Button::initButton(
 TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
 uint16_t outline, uint16_t fill, uint16_t textcolor,
 char *label, uint8_t textsize)
{
  // Tweak arguments and pass to the newer initButtonUL() function...
  initButtonUL(gfx, x - (w / 2), y - (h / 2), w, h, outline, fill,
    textcolor, label, textsize);
}

// Newer function instead accepts upper-left corner & size
void TFT_eSPI_Button::initButtonUL(
 TFT_eSPI *gfx, int16_t x1, int16_t y1, uint16_t w, uint16_t h,
 uint16_t outline, uint16_t fill, uint16_t textcolor,
 char *label, uint8_t textsize)
{
  _x1           = x1;
  _y1           = y1;
  _w            = w;
  _h            = h;
  _outlinecolor = outline;
  _fillcolor    = fill;
  _textcolor    = textcolor;
  _textsize     = textsize;
  _gfx          = gfx;
  strncpy(_label, label, 9);
}

// Adjust text datum and x, y deltas
void TFT_eSPI_Button::setLabelDatum(int16_t x_delta, int16_t y_delta, uint8_t datum)
{
  _xd        = x_delta;
  _yd        = y_delta;
  _textdatum = datum;
}

void TFT_eSPI_Button::drawButton(bool inverted, String long_name) {
  uint16_t fill, outline, text;

  if(!inverted) {
    fill    = _fillcolor;
    outline = _outlinecolor;
    text    = _textcolor;
  } else {
    fill    = _textcolor;
    outline = _outlinecolor;
    text    = _fillcolor;
  }

  uint8_t r = min(_w, _h) / 4; // Corner radius
  _gfx->fillRoundRect(_x1, _y1, _w, _h, r, fill);
  _gfx->drawRoundRect(_x1, _y1, _w, _h, r, outline);

  _gfx->setTextColor(text, fill);
  _gfx->setTextSize(_textsize);

  uint8_t tempdatum = _gfx->getTextDatum();
  _gfx->setTextDatum(_textdatum);
  if (long_name == "")
    _gfx->drawString(_label, _x1 + (_w/2) + _xd, _y1 + (_h/2) - 4 + _yd);
  else
    _gfx->drawString(long_name, _x1 + (_w/2) + _xd, _y1 + (_h/2) - 4 + _yd);
  _gfx->setTextDatum(tempdatum);
}

bool TFT_eSPI_Button::contains(int16_t x, int16_t y) {
  return ((x >= _x1) && (x < (_x1 + _w)) &&
          (y >= _y1) && (y < (_y1 + _h)));
}

void TFT_eSPI_Button::press(bool p) {
  laststate = currstate;
  currstate = p;
}

bool TFT_eSPI_Button::isPressed()    { return currstate; }
bool TFT_eSPI_Button::justPressed()  { return (currstate && !laststate); }
bool TFT_eSPI_Button::justReleased() { return (!currstate && laststate); }
