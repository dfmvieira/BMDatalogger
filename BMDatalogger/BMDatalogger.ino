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
 * -Thatguy
*/
//#####################################################
//#####################################################
//#####################################################

#include "Wire.h"
#include <LiquidCrystal_I2C.h>
//#include <stdio.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

//0x20-0x27 - 0x30 - 0x3F
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int TopButton = 9;
const int BottomButton = 8;

byte ScreenCurrentPage = 1;
byte ScreenCurrentPeak = 0;
byte ScreenCurrentMenu = 0; //0=displays, 1=peak
int ThisScreenIndex = 0;    //current display index number
int XPos = 0;
int YPos = 0;
char StringBuffer[20];

const int MaxDataValue = 20;
bool EcuConnected = false;
unsigned long last_datalog_time=0;

const byte ScreenPage1[8] = {0, 1, 2, 3, 4, 5, 6 ,7};
const byte ScreenPage2[8] = {8, 9, 10, 11, 12, 13, 14 ,18};
const byte ScreenPage3[8] = {68, 0, 69, 0, 1, 3, 5 ,7};
const byte ScreenPage4[8] = {50, 0, 51, 0, 53, 0, 54, 0};
const byte ScreenPage5[8] = {100, 0, 0, 0, 102, 0, 0, 0};
const byte ScreenPage6[8] = {150, 0, 0, 0, 0, 0, 0, 0};
const byte ScreenPage7[8] = {0, 1, 104, 0, 0, 0, 52, 3};
const byte ScreenPage8[8] = {168, 0, 0, 0, 0, 0, 0, 0};

const String VersionStr = "1.5.0";
const byte ProgressBarMode = 2;
const byte ProgressBarLeft = 1;
const int Timeout = 80;
const int Injectors_Size = 240;
const byte O2Input = 0;
const byte MapValue = 0;
//const byte BoostValue = 3;
const byte UseCelcius = 1;
const byte UseKMH = 1;
const byte UseLAMBA = 0;
//const byte WBType = 0;
const double WBConversion[4] = {0.5, 0.75, 3.38, 1.14};
const byte Tranny[4] = {0x46, 0x67, 0x8E, 0xB8};
const byte MapByte[2] = {0xBA, 0xFE};

//const double WBConversion[24] = {0.5, 0.75, 0.75, 0.79, 1, 0.82, 1.25, 0.85, 1.5, 0.89, 1.75, 0.92, 2, 0.96, 2.25, 0.99, 2.5, 1.02, 2.75, 1.06, 3, 1.09, 3.38, 1.14};
//const byte Tranny[10] = {0x46, 0x00, 0x67, 0x00, 0x8E, 0x00, 0xB8, 0x00, 0x52, 0xDE};
//oem = BA - FE
//2bar = 08 - F9

int FakeValue = 0;

//#####################################################

void setup() {
  pinMode(TopButton,INPUT_PULLUP);
  pinMode(BottomButton,INPUT_PULLUP);
  
  Screen();
  Connect();
}

//#####################################################

void loop() {
  if (!EcuConnected) ScreenJ12();
  if (EcuConnected) Display();
  GetButtonStates();
}

