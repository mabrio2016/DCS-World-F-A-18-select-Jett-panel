 
// SerialSpeed = 250000 baud

//SEL_JETT_KNOB 0
//SEL_JETT_KNOB 1

#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"
#include <Adafruit_PCF8574.h>
#include <PCF8575.h>
#include "Arduino.h"

Adafruit_PCF8574 pcf1;  // PCF8574 has 8 input ports
PCF8575 pcf2(0x20);     // PCF8575 has 16 input ports
PCF8575 pcf3(0x21);     // PCF8575 has 16 input ports
bool flag_[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
bool flagOld_[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
bool flag_2[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
bool flagOld_2[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
bool flag_3[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
bool flagOld_3[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
static int pcf1_flag = 1;
static int pcf2_flag = 1;
static int pcf3_flag = 1;

/* paste code snippets from the reference documentation here */
DcsBios::Switch2Pos selJettBtn("SEL_JETT_BTN", 4);
DcsBios::Switch3Pos flapSw("FLAP_SW", 7, 6);
DcsBios::Switch2Pos hookBypassSw("HOOK_BYPASS_SW", 5);

void setup() {
  Serial.begin(250000);
  DcsBios::setup();
  if (!pcf1.begin(0x22, &Wire)) {
    Serial.println("Couldn't find PCF8574 (0x27) - Jett panel");
    pcf1_flag = 0;
  }

  for (uint8_t p = 0; p < 8; p++) {
    pcf1.pinMode(p, INPUT_PULLUP);
  }

  for (uint8_t p = 0; p < 16; p++) { 
    pcf2.pinMode(p, INPUT_PULLUP);
    if (p == 15) pcf2.pinMode(15, INPUT);   // there is a problem with PCF8575 to set the input 15 as INPUT_PULLUP, so I had to set it as IMPUT here.
  }  
  if (!pcf2.begin()) {
    Serial.println("Couldn't find PCF8575 (0x20) - SNSR panel");
    pcf2_flag = 0;
  }
  for (uint8_t p = 0; p < 16; p++) { 
    pcf3.pinMode(p, INPUT_PULLUP);
    if (p == 15) pcf3.pinMode(15, INPUT);   // there is a problem with PCF8575 to set the input 15 as INPUT_PULLUP, so I had to set it as IMPUT here.
  }
  if (!pcf3.begin()) {
    Serial.println("Couldn't find PCF8575 (0x21) - ECS Panel");
    pcf3_flag = 0;
  }
}
void loop() {
  DcsBios::loop();
  if (pcf1_flag == 1) {
// Jett Panel //
// Start of Rotary Switch 5 positions //
    int last_Switch;
    int Switch;
    for (uint8_t p = 0; p < 6; p++) {

      if (!pcf1.digitalRead(p)) {
        {
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
        }
        last_Switch = Switch;
        delay(15);
      }
      // End of Rotary Switch 5 positions //
      // Start two position Switches //
      if (pcf1.digitalRead(5) == true) {
        flag_[5] = true;
        if (flagOld_[5] != flag_[5]) Serial.println("LAUNCH_BAR_SW 0");
        flagOld_[5] = flag_[5];
      }
      if (pcf1.digitalRead(5) == false) {
        flag_[5] = false;
        if (flagOld_[5] != flag_[5]) Serial.println("LAUNCH_BAR_SW 1");
        flagOld_[5] = flag_[5];
      }
      if (pcf1.digitalRead(6) == true) {
        flag_[6] = true;
        if (flagOld_[6] != flag_[6]) Serial.println("ANTI_SKID_SW 1");
        flagOld_[6] = flag_[6];
      }
      if (pcf1.digitalRead(6) == false) {
        flag_[6] = false;
        if (flagOld_[6] != flag_[6]) Serial.println("ANTI_SKID_SW 0");
        flagOld_[6] = flag_[6];
      }
      if (pcf1.digitalRead(7) == true) {
        flag_[7] = true;
        if (flagOld_[7] != flag_[7]) Serial.println("LDG_TAXI_SW 1");
        flagOld_[7] = flag_[7];
      }
      if (pcf1.digitalRead(7) == false) {
        flag_[7] = false;
        if (flagOld_[7] != flag_[7]) Serial.println("LDG_TAXI_SW 0");
        flagOld_[7] = flag_[7];
      }
      // End of Two position Switches //
    }
  }
// End of Jett Panel //
//----------------------------------------------------------------------//
// Start of SNSR Panel //
  if (pcf2_flag == 1) {
  // Start of RADAR Rotary Switch 4 positions //
    int last_Switch1;
    int Switch1;
    for (uint8_t p1 = 0; p1 <= 3; p1++) {
      static bool RADAR_SW_PULL_Flag = 0;
      if (!pcf2.digitalRead(p1)) {
        if (p1 == 0) {
          Switch1 = 0;
          if (last_Switch1 != Switch1) Serial.println("RADAR_SW 0");
          //delay(15);
        }
        if (p1 == 1) {
          Switch1 = 1;
          if (last_Switch1 != Switch1) Serial.println("RADAR_SW 1");
        }
        if (p1 == 2) {
          Switch1 = 2;
          if (last_Switch1 != Switch1) {
            if (RADAR_SW_PULL_Flag == 1) {
              Serial.println("RADAR_SW_PULL 1");
              //delay(100);
            }
            Serial.println("RADAR_SW 2");
            RADAR_SW_PULL_Flag = 0;
            //delay(15);
          }
        }
        if (p1 == 3) {
          Switch1 = 3;
          if (last_Switch1 != Switch1) {
            if (RADAR_SW_PULL_Flag == 0) {
              Serial.println("RADAR_SW_PULL 1");
              //delay(100);
            }
            Serial.println("RADAR_SW 3");
            RADAR_SW_PULL_Flag = 1;
            //delay(15);
          }
        }
        last_Switch1 = Switch1;
      }
    }
// End Rotary Switch 4 positions //
// --------------------------------------------------------------//
// Start of INS Rotary Switch 8 positions //
    int last_Switch2;
    int Switch2;
    for (uint8_t p2 = 4; p2 <= 11; p2++) {
      if (!pcf2.digitalRead(p2)) {
        if (p2 == 4) {
          Switch2 = 4;
          if (last_Switch2 != Switch2) Serial.println("INS_SW 0");
          //delay(15);
        }
        if (p2 == 5) {
          Switch2 = 5;
          if (last_Switch2 != Switch2) Serial.println("INS_SW 1");
          //delay(15);
        }
        if (p2 == 6) {
          Switch2 = 6;
          if (last_Switch2 != Switch2) Serial.println("INS_SW 2");
          //delay(15);
        }
        if (p2 == 7) {
          Switch2 = 7;
          if (last_Switch2 != Switch2) Serial.println("INS_SW 3");
          //delay(15);
        }
        if (p2 == 8) {
          Switch2 = 8;
          if (last_Switch2 != Switch2) Serial.println("INS_SW 4");
          //delay(15);
        }
        if (p2 == 9) {
          Switch2 = 9;
          if (last_Switch2 != Switch2) Serial.println("INS_SW 5");
          //delay(15);
        }
        if (p2 == 10) {
          Switch2 = 10;
          if (last_Switch2 != Switch2) Serial.println("INS_SW 6");
          //delay(15);
        }
        if (p2 == 11) {
          Switch2 = 11;
          if (last_Switch2 != Switch2) Serial.println("INS_SW 7");
          //delay(15);
        }
        last_Switch2 = Switch2;
        //delay(15);
      }
    }
// End of INS Rotary Switch 8 positions //
// Start of Two position Switches //
    if (pcf2.digitalRead(12) == 0) 
    {
      flag_2[12] = true;
      if (flagOld_2[12] != flag_2[12]) Serial.println("LST_NFLR_SW 0");
      delay(15);
      flagOld_2[12] = flag_2[12];
    }
    if (pcf2.digitalRead(12) == 1) {
      flag_2[12] = false;
      if (flagOld_2[12] != flag_2[12]) Serial.println("LST_NFLR_SW 1");
      delay(15);
      flagOld_2[12] = flag_2[12];
    }
    delay(15);  // this Deelay is important to give time for the Multiplex to refrech the port status
    if (pcf2.digitalRead(13) == 0) {
      flag_2[13] = true;
      if (flagOld_2[13] != flag_2[13]) Serial.println("LTD_R_SW 0");
      //delay(15);
      flagOld_2[13] = flag_2[13];
    }
    delay(15);
    if (pcf2.digitalRead(13) == 1) {
      flag_2[13] = false;
      if (flagOld_2[13] != flag_2[13]) Serial.println("LTD_R_SW 1");
      //delay(15);
      flagOld_2[13] = flag_2[13];
    }
// End of Two position Switches //
// Start of Three position Switches //
    delay(15);
    if (pcf2.digitalRead(14) == 1) {
      flag_2[14] = true;
      if (flagOld_2[14] != flag_2[14]) Serial.println("FLIR_SW 1");
      //delay(15);
      flagOld_2[14] = flag_2[14];
    }
    delay(15);
    if (pcf2.digitalRead(14) == 0) {
      flag_2[14] = false;
      if (flagOld_2[14] != flag_2[14]) Serial.println("FLIR_SW 0");
      //delay(15);
      flagOld_2[14] = flag_2[14];
    }
    if (pcf2.digitalRead(15) == 1) {
      flag_2[15] = true;
      if (flagOld_2[15] != flag_2[15]) Serial.println("FLIR_SW 1");
      delay(15);
      flagOld_2[15] = flag_2[15];
    }
    if (pcf2.digitalRead(15) == 0) {
      flag_2[15] = false;
      if (flagOld_2[15] != flag_2[15]) Serial.println("FLIR_SW 2");
      delay(15);
      flagOld_2[15] = flag_2[15];
    }
// End of Three position Switches //
  }
    // End of SNSR Panel //
    //----------------------------------------------------------------------//
  // ECS Panel //
  if (pcf3_flag == 1) {
    // Start of Rotary Switch 5 poles //
    int last_Switch;
    int Switch;
    for (uint8_t p = 0; p < 5; p++) {

      if (!pcf3.digitalRead(p)) {
        {
          if (p == 0) {
            Switch = 0;
            if (last_Switch != Switch) Serial.println("BLEED_AIR_KNOB 0");
          }
          if (p == 1) {
            Switch = 1;
            if (last_Switch != Switch) Serial.println("BLEED_AIR_KNOB 1");
          }
          if (p == 2) {
            Switch = 2;
            if (last_Switch != Switch) Serial.println("BLEED_AIR_KNOB 2");
          }
          if (p == 3) {
            Switch = 3;
            if (last_Switch != Switch) Serial.println("BLEED_AIR_KNOB 3");
          }
        }
        // End of Rotary Switch 4 poles //
        last_Switch = Switch;
        //delay(15);
      }
    // Start of Two position Switches //
      delay(15);
      if (pcf3.digitalRead(10) == 0) 
      {
        flag_3[10] = true;
        if (flagOld_3[10] != flag_3[10]) Serial.println("PITOT_HEAT_SW 0");
        //delay(15);
        flagOld_3[10] = flag_3[10];
      }
      //delay(15);
      if (pcf3.digitalRead(10) == 1) {
        flag_3[10] = false;
        if (flagOld_3[10] != flag_3[10]) Serial.println("PITOT_HEAT_SW 1");
        delay(15);
        flagOld_3[10] = flag_3[10];
      }
    // End of Two position Switches //
    // Start of Three position Switches //
    //delay(15);
    if (pcf3.digitalRead(4) == 1) {
      flag_3[4] = true;
      if (flagOld_3[4] != flag_3[4]) Serial.println("CABIN_PRESS_SW 1");
      //delay(15);
      flagOld_3[4] = flag_3[4];
    }
    delay(15);
    if (pcf3.digitalRead(4) == 0) {
      flag_3[4] = false;
      if (flagOld_3[4] != flag_3[4]) Serial.println("CABIN_PRESS_SW 0");
      //delay(15);
      flagOld_3[4] = flag_3[4];
    }
    if (pcf3.digitalRead(5) == 1) {
      flag_3[5] = true;
      if (flagOld_3[5] != flag_3[5]) Serial.println("CABIN_PRESS_SW 1");
      delay(15);
      flagOld_3[5] = flag_3[5];
    }
    delay(15);
    if (pcf3.digitalRead(5) == 0) {
      flag_3[5] = false;
      if (flagOld_3[5] != flag_3[5]) Serial.println("CABIN_PRESS_SW 2");
      //delay(15);
      flagOld_3[5] = flag_3[5];
    }
    //-------------------------------------------------//
    if (pcf3.digitalRead(6) == 1) {
      flag_3[6] = true;
      if (flagOld_3[6] != flag_3[6]) Serial.println("ECS_MODE_SW 1");
      delay(15);
      flagOld_3[6] = flag_3[6];
    }
    delay(15);
    if (pcf3.digitalRead(6) == 0) {
      flag_3[6] = false;
      if (flagOld_3[6] != flag_3[6]) Serial.println("ECS_MODE_SW 0");
      //delay(15);
      flagOld_3[6] = flag_3[6];
    }
    if (pcf3.digitalRead(7) == 1) {
      flag_3[7] = true;
      if (flagOld_3[7] != flag_3[7]) Serial.println("ECS_MODE_SW 1");
      //delay(15);
      flagOld_3[7] = flag_3[7];
    }
    delay(15);
    if (pcf3.digitalRead(7) == 0) {
      flag_3[7] = false;
      if (flagOld_3[7] != flag_3[7]) Serial.println("ECS_MODE_SW 2");
      //delay(15);
      flagOld_3[7] = flag_3[7];
    }
    //-------------------------------------------------//
    if (pcf3.digitalRead(8) == 1) {
      flag_3[8] = true;
      if (flagOld_3[8] != flag_3[8]) Serial.println("ENG_ANTIICE_SW 1");
      delay(15);
      flagOld_3[8] = flag_3[8];
    }
    delay(15);
    if (pcf3.digitalRead(8) == 0) {
      flag_3[8] = false;
      if (flagOld_3[8] != flag_3[8]) Serial.println("ENG_ANTIICE_SW 0");
      //delay(15);
      flagOld_3[8] = flag_3[8];
    }
    if (pcf3.digitalRead(9) == 1) {
      flag_3[9] = true;
      if (flagOld_3[9] != flag_3[9]) Serial.println("ENG_ANTIICE_SW 1");
      //delay(15);
      flagOld_3[9] = flag_3[9];
    }
    delay(15);
    if (pcf3.digitalRead(9) == 0) {
      flag_3[9] = false;
      if (flagOld_3[9] != flag_3[9]) Serial.println("ENG_ANTIICE_SW 2");
      //delay(15);
      flagOld_3[9] = flag_3[9];
    }


    // End of Three position Switches //
  }
}}
