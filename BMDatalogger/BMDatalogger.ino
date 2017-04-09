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

//Load Modules
#include "Wire.h"
#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <LcdBarGraph.h>
#include <phi_big_font.h>

//Set Inputs
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LcdBarGraph progBar(&lcd, 10);
const int TopButton = 9;

//Screen Settings
byte ScreenCurrentPage = 1;
byte ScreenIndex[8];
int Offset = 0;
int Lines = 0;
bool EcuConnected = false;

//Pages Settings
const byte ScreenPage1[8] = {0, 1, 2, 3, 4, 5, 6 ,7};
const byte ScreenPage2[8] = {8, 9, 10, 11, 12, 13, 14 ,15};
const byte ScreenPage3[8] = {16, 17, 18, 19, 20, 21, 22 ,0};
//const byte ScreenPage4[8] = {50, 0, 101, 0, 0, 0, 52, 0};
const byte ScreenPage4[8] = {50, 0, 51, 0, 102, 0, 0, 0};

//Options Vars
const String VersionStr = "V1.3.0";
const int Timeout = 200;
const int Injectors_Size = 240;
const byte O2Input = 0;
const byte MapValue = 0;
const byte UseCelcius = 1;
const byte UseKMH = 1;
const byte UseLAMBA = 0;
const byte WBType = 0;
const double WBConversion[24] = {0.5, 0.75, 0.75, 0.79, 1, 0.82, 1.25, 0.85, 1.5, 0.89, 1.75, 0.92, 2, 0.96, 2.25, 0.99, 2.5, 1.02, 2.75, 1.06, 3, 1.09, 3.38, 1.14};
const byte Tranny[10] = {0x46, 0x00, 0x67, 0x00, 0x8E, 0x00, 0xB8, 0x00, 0x52, 0xDE};


//#####################################################

void setup() {
  //Initialize Buttons Pinout
  pinMode(TopButton,INPUT_PULLUP);  

  //Start LCD Display
  lcd.begin(20, 4);
  init_big_font(&lcd);
  StartScreen();
  lcd.clear();
  Connect();
  ApplyPage();
}

//#####################################################

void loop() {
  delay(Timeout);
  LcdBarGraph progBar(&lcd, 10);
  init_big_font(&lcd);   
  lcd.clear();
  if (!EcuConnected) SetJ12Screen();
  if (EcuConnected) Display();
}

