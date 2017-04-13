//#####################################################
//#####################################################
//#####################################################
/*
 *         THIS IS THE BM DEVS DATALOGGER
 * 
 * THIS WORKS BY DATALOGGING ECTUNE ISR V3 PROTOCOL ON
 * THE ARDUINO SERIAL PORT. THIS WORKS WITH 2X BUTTONS 
 * NAVIGATION ONLY. IT ONLY WORKS FOR THE 20X04 LCD
 * 
 *  ####################################################
 *    ALL CREDITS GOES TO :
 * -Bouletmarc (BM Devs)
 * -Majidi
 * -Thatguy
*/
//#####################################################
//#####################################################
//#####################################################

#include "Wire.h"
#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal.h>
//#include <stdio.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
const int TopButton = 9;
//const int TopButton = 6;

byte ScreenCurrentPage = 1;
byte ScreenCurrentPeak = 0; //This also refer to the Display Data index (ex: 0 = rpm)
byte ScreenCurrentMenu = 0; //0=displays, 1=peak
int ThisScreenIndex = 0;    //
int XPos = 0;
int YPos = 0;

char StringBuffer[10];      //10x chars buffer
char StringBufferLong[20];  //20x chars buffer
char StringBufferBig[5];    //5x chars buffer
int CurrentBufferIndex = 0; //which index we are now doing into the Buffer (0-10 or 0-20)

const int MaxDataValue = 20;
int PeakMinValue = 0;
int PeakMaxValue = 1;
bool EcuConnected = false;
unsigned long last_datalog_time=0;

const byte ScreenPage1[8] = {0, 1, 2, 3, 4, 5, 6 ,7};
const byte ScreenPage2[8] = {8, 9, 10, 11, 12, 13, 14 ,18};
const byte ScreenPage3[8] = {50, 0, 51, 0, 53, 0, 54, 0};
const byte ScreenPage4[8] = {100, 0, 0, 0, 0, 0, 0, 0};

const String VersionStr = "V1.4.2";
const int Timeout = 120;
const int Injectors_Size = 240;   //Switch this to 2byte
const byte O2Input = 0;
const byte MapValue = 0;
const byte BoostValue = 0;
const byte UseCelcius = 1;
const byte UseKMH = 1;
const byte UseLAMBA = 0;
const byte WBType = 0;
const double WBConversion[4] = {0.5, 0.75, 3.38, 1.14};
const byte Tranny[4] = {0x46, 0x67, 0x8E, 0xB8};

//const double WBConversion[24] = {0.5, 0.75, 0.75, 0.79, 1, 0.82, 1.25, 0.85, 1.5, 0.89, 1.75, 0.92, 2, 0.96, 2.25, 0.99, 2.5, 1.02, 2.75, 1.06, 3, 1.09, 3.38, 1.14};
//const byte Tranny[10] = {0x46, 0x00, 0x67, 0x00, 0x8E, 0x00, 0xB8, 0x00, 0x52, 0xDE};

//#####################################################

void setup() {
  pinMode(TopButton,INPUT_PULLUP);

  //Serial.begin(38400);
  //Serial.println("Serial Debugger Started");
  
  lcd.begin(20, 4);
  Screen(false);
  lcd.clear();
  Connect();
}

//#####################################################

void loop() {
  //delay(Timeout);
  if (!EcuConnected) Screen(true);
  if (EcuConnected) Display();
  GetButtonStates();
}

