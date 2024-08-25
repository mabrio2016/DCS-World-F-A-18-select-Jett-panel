/*
  Tell DCS-BIOS to use a serial connection and use the default Arduino Serial
  library. This will work on the vast majority of Arduino-compatible boards,
  but you can get corrupted data if you have too many or too slow outputs
  (e.g. when you have multiple character displays), because the receive
  buffer can fill up if the sketch spends too much time updating them.
  
  If you can, use the IRQ Serial connection instead.
*/
// SerialSpeed = 250000 baud

//SEL_JETT_KNOB 0
//SEL_JETT_KNOB 1
  
#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"
#include <Adafruit_PCF8574.h>

Adafruit_PCF8574 pcf;
static int last_Switch = false;
static int Switch = false;
static bool flag_[] = {false,false,false,false,false,false,false,false};
static bool flagOld_[] = {false,false,false,false,false,false,false,false};

/* paste code snippets from the reference documentation here */
DcsBios::Switch2Pos selJettBtn("SEL_JETT_BTN", 4);
DcsBios::Switch3Pos flapSw("FLAP_SW", 6, 7);
DcsBios::Switch2Pos hookBypassSw("HOOK_BYPASS_SW", 3);

void setup() {
  DcsBios::setup();
  if (!pcf.begin(0x20, &Wire)) {
    Serial.println("Couldn't find PCF8574");
    while (1);
  }
  for (uint8_t p=0; p<8; p++) {
    pcf.pinMode(p, INPUT_PULLUP);
  }
}
void loop() 
{
  DcsBios::loop();
  for (uint8_t p=0; p<8; p++) 
  {
    if (! pcf.digitalRead(p)) 
    {
      {                   // Rotary Switch 5 poles //
        if (p == 0) {
          Switch = 0;
          if (last_Switch != Switch) Serial.println("SEL_JETT_KNOB 0");
        }
        if (p == 1) {
          Switch = 1;
          if (last_Switch != Switch) Serial.println("SEL_JETT_KNOB 1");          
        }
        if (p == 2) {
          Switch = 2;
          if (last_Switch != Switch) Serial.println("SEL_JETT_KNOB 2");
        }
        if (p == 3) {
          Switch = 3;
          if (last_Switch != Switch) Serial.println("SEL_JETT_KNOB 3");
        }
        if (p == 4) {
          Switch = 4;
          if (last_Switch != Switch) Serial.println("SEL_JETT_KNOB 4");
        }
      }                     // Rotary Switch 5 poles //
      last_Switch = Switch;         
      delay(30);            // a short debounce delay
    }                       
    // Two position Switches //
    if (pcf.digitalRead(5) == true) {
      flag_[5] = true;
      if (flagOld_[5] != flag_[5]) Serial.println("LAUNCH_BAR_SW 1");
      flagOld_[5] = flag_[5];
    }
    if (pcf.digitalRead(5) == false) {
      flag_[5] = false;
      if (flagOld_[5] != flag_[5]) Serial.println("LAUNCH_BAR_SW 0");
      flagOld_[5] = flag_[5];
    }
    if (pcf.digitalRead(6) == true) {
      flag_[6] = true;
      if (flagOld_[6] != flag_[6]) Serial.println("ANTI_SKID_SW 1");
      flagOld_[6] = flag_[6];
    }
    if (pcf.digitalRead(6) == false) {
      flag_[6] = false;
      if (flagOld_[6] != flag_[6]) Serial.println("ANTI_SKID_SW 0");
      flagOld_[6] = flag_[6];
    }
    if (pcf.digitalRead(7) == true) {
      flag_[7] = true;
      if (flagOld_[7] != flag_[7]) Serial.println("LDG_TAXI_SW 1");
      flagOld_[7] = flag_[7];
    }
    if (pcf.digitalRead(7) == false) {
      flag_[7] = false;
      if (flagOld_[7] != flag_[7]) Serial.println("LDG_TAXI_SW 0");
      flagOld_[7] = flag_[7];
    }
    // Two position Switches //
  }
}