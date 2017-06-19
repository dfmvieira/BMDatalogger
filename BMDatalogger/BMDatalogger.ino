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
byte ScreenCurrentMenu = 0;
int ThisScreenIndex = 0;    //current display index number
int XPos = 0;
int YPos = 0;
char StringBuffer[20];

const int MaxDataValue = 27;
bool EcuConnected = false;
unsigned long last_datalog_time=0;

const byte ScreenPage1[8] = {50,0,1,2,3,4,5,6};
const byte ScreenPage2[8] = {50,0,7,8,9,10,11,12};
const byte ScreenPage3[8] = {50,0,13,14,15,16,17,18};
const byte ScreenPage4[8] = {50,0,51,0,52,0,53,0};
const byte ScreenPage5[8] = {50,0,56,0,66,0,8,16};
const byte ScreenPage6[8] = {50,0,5,9,2,4,68,0};
const byte ScreenPage7[8] = {50,0,68,0,56,0,53,0};
const byte ScreenPage8[8] = {1,2,100,0,0,0,3,4};

const String VersionStr = "1.6.0";
const byte ProgressBarMode = 0;
const byte ProgressBarLeft = 0;
const int Timeout = 200;
const int Injectors_Size = 240;
const byte O2Input = 0;
const byte MapValue = 0;
const byte UseCelcius = 1;
const byte UseKMH = 1;
const byte O2Type = 0;
const double WBConversion[4] = {0,1.3,1,0.71};
const byte MapByte[4] = {186,127,254,134};
const byte Tranny[4] = {70,103,142,184};
const int Warning_RPM = 7500;
const int Warning_IAT = 45;
const int Warning_ECT = 106;

int mBarMin = -70;
int mBarMax = 1790;
int TempMin = -40;
int TempMax = 140;

//#####################################################

void setup() {
  pinMode(TopButton,INPUT_PULLUP);
  pinMode(BottomButton,INPUT_PULLUP);
  
  mBarMin = (int) ((((long) MapByte[1] * 256) + (long) MapByte[0]) - 32768);
  mBarMax = (int) ((((long) MapByte[3] * 256) + (long) MapByte[2]) - 32768);
  if (UseCelcius == 0) TempMin = TempMin * 1.8 + 32.0;
  if (UseCelcius == 0) TempMax = TempMax * 1.8 + 32.0;
    
  Screen();
  Connect();
}

//#####################################################

void loop() {
  if (!EcuConnected) ScreenJ12();
  if (EcuConnected) Display();
  GetButtonStates();
}

