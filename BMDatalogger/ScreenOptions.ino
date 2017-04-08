// TRANNY TYPES REFERENCES :
//0 = 'Y21/Y80/S80'
//1 = 'ITR S80 JDM 98-01'
//2 = 'ITR S80 USDM 97-01 '
//3 = 'Z6/Y8'
//4 = 'GSR'
//5 = 'LS/RS/GS/SE'
//6 = 'H22 JDM'
//7 = 'H22 USDM/H23 JDM'
//8 = 'H23 USDM'
//9 = 'D16Y7'

// O2 REFERENCES
// o2Input, eldInput, egrInput, b6Input

//MAPS REFERENCES :
// mBar, Bar, inHgG, inHg, psi, kPa (type it with specifics caps)

void DisplayOptions() {
  for (int i=0; i<8; i++) {
    String Text = "";
    if (i == 0) Text += "INJ:" + String(Injectors_Size);
    if (i == 1) Text += "TRANNY:" + String(GetTrannyStr());
    if (i == 2) Text += "O2IN:" + String(GetO2Str());
    if (i == 3) Text += "MAP:" + String(GetMapStr());
    if (i == 4) Text += "TEMP:" + String(GetTempCelcius());
    if (i == 5) Text += "SPEED:" + String(GetKMH());
    if (i == 6) Text += "T/O:" + String(Timeout) + "ms";
    if (i == 7) Text += "SLVL:" + String(mBarSeaLevel);

    //Reset Invalid Char Over Text Lenght
    int ResetLenght = 10 - Text.length();
    for (int i2=0; i2<ResetLenght; i2++) Text += " ";

    SetOffset(i);
    lcd.setCursor(Offset, Lines);
    lcd.print(Text);
  }
}

void DisplayEdit() {
  //Set Top Title
  lcd.setCursor(0, 0);
  if (ScreenCurrentIndex == 0) lcd.print("    INJECTOR SIZE   ");
  if (ScreenCurrentIndex == 1) lcd.print("    TRANNY TYPE     ");
  if (ScreenCurrentIndex == 2) lcd.print("      O2 INPUT      ");
  if (ScreenCurrentIndex == 3) lcd.print("      MAP TYPE      ");
  if (ScreenCurrentIndex == 4) lcd.print("  TEMPERATURE TYPE  ");
  if (ScreenCurrentIndex == 5) lcd.print("     SPEED TYPE     ");
  if (ScreenCurrentIndex == 6) lcd.print("    DISPLAY DELAY   ");
  if (ScreenCurrentIndex == 7) lcd.print("   MBAR SEA LEVEL   ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);

  String Text1 = "";
  String Text2 = "";
  
  //Set Bottom Edit Texts
  if (ScreenCurrentIndex == 0) {
    Text1 = "   " + String(Injectors_Size);
    DisplayMode1();
  }
  if (ScreenCurrentIndex == 1) {
    Text1 = "   #" + TrannyType;
    Text1 += " " + String(GetTrannyStr());
    DisplayModel2();
  }
  if (ScreenCurrentIndex == 2) {
    Text1 = "   #" + O2Input;
    Text1 += " " + String(GetO2Str());
    DisplayModel2();
  }
  if (ScreenCurrentIndex == 3) {
    Text1 = "   #" + MapValue;
    Text1 += " " + String(GetMapStr());
    DisplayModel2();
  }
  if (ScreenCurrentIndex == 4) {
    Text1 = "   #" + UseCelcius;
    Text1 += " " + String(GetTempCelcius());
    DisplayModel2();
  }
  if (ScreenCurrentIndex == 5) {
    Text1 = "   #" + UseKMH;
    Text1 += " " + String(GetKMH());
    DisplayModel2();
  }
  if (ScreenCurrentIndex == 6) {
    Text1 = "   " + String(Timeout);
    DisplayMode1();
  }
  if (ScreenCurrentIndex == 7) {
    Text1 = "   " + String(mBarSeaLevel);
    DisplayMode1();
  }
  
  int ResetLenght = 10 - Text1.length();
  for (int i2=0; i2<ResetLenght; i2++) Text1 += " ";
  lcd.print(Text1);
}

void DisplayMode1() {
  lcd.setCursor(10, 2);
  lcd.print("  <    >  ");
  
  lcd.setCursor(0, 3);
  if (!ScreenEditInc) lcd.print("DECREASE    ^       ");
  if (ScreenEditInc) lcd.print("INCREASE         ^  ");
}

void DisplayModel2() {
  lcd.setCursor(10, 2);
  lcd.print("       >  ");
  lcd.setCursor(0, 3);
  lcd.print("    NEXT         ^  ");
}

//Top Button Input
void EditTop() {
  if (ScreenCurrentIndex == 0) {
    if (!ScreenEditInc) Injectors_Size -= 10;
    if (ScreenEditInc) Injectors_Size += 10;
  }
  if (ScreenCurrentIndex == 1) {
    TrannyType++;
    if (TrannyType > 9) TrannyType = 0;
  }
  if (ScreenCurrentIndex == 2) {
    O2Input++;
    if (O2Input > 3) O2Input = 0;
  }
  if (ScreenCurrentIndex == 3) {
    MapValue++;
    if (MapValue > 5) MapValue = 0;
  }
  if (ScreenCurrentIndex == 4) {
    UseCelcius++;
    if (UseCelcius > 1) UseCelcius = 0;
  }
  if (ScreenCurrentIndex == 5) {
    UseKMH++;
    if (UseKMH > 1) UseKMH = 0;
  }
  if (ScreenCurrentIndex == 6) {
    if (!ScreenEditInc) Timeout -= 5;
    if (ScreenEditInc) Timeout += 5;
  }
  if (ScreenCurrentIndex == 7) {
    if (!ScreenEditInc) mBarSeaLevel -= 10;
    if (ScreenEditInc) mBarSeaLevel += 10;
  }
}

//Botom Button Input
void EditBottom() {
  if (!ScreenEditInc) ScreenEditInc = true;
  else ScreenEditInc = false;
}

String GetTrannyStr() {
  String Str = "";
  if (TrannyType == 0) Str = "Y21/80";
  if (TrannyType == 1) Str = "S80J";
  if (TrannyType == 2) Str = "S80U";
  if (TrannyType == 3) Str = "Z6/Y8";
  if (TrannyType == 4) Str = "GSR";
  if (TrannyType == 5) Str = "RS";
  if (TrannyType == 6) Str = "H22J";
  if (TrannyType == 7) Str = "H23U";
  if (TrannyType == 8) Str = "H22U";
  if (TrannyType == 9) Str = "Y7";
  return Str;
}

String GetO2Str() {
  String Str = "";
  if (O2Input == 0) Str = "O2";
  if (O2Input == 1) Str = "ELD";
  if (O2Input == 2) Str = "EGR";
  if (O2Input == 3) Str = "B6";
}

String GetMapStr() {
  String Str = "";
  if (MapValue == 0) Str = "mBar";
  if (MapValue == 1) Str = "Bar";
  if (MapValue == 2) Str = "inHgG";
  if (MapValue == 3) Str = "inHg";
  if (MapValue == 4) Str = "psi";
  if (MapValue == 5) Str = "kPa";
}

String GetTempCelcius() {
  String Str = "";
  if (UseCelcius == 1) Str = "CEL";
  if (UseCelcius == 0) Str = "FAR";
}

String GetKMH() {
  String Str = "";
  if (UseKMH == 1) Str = "KMH";
  if (UseKMH == 0) Str = "MPH";
}

void SaveOptions() {
  for (int i=0; i < 9; i++) {
    int Addr = i * 10;
    if (i == 0) EEPROM.put(Addr, Timeout);
    if (i == 1) EEPROM.put(Addr, Injectors_Size);
    if (i == 2) EEPROM.put(Addr, mBarSeaLevel);
    if (i == 3) EEPROM.put(Addr, TrannyType);
    if (i == 4) EEPROM.put(Addr, O2Input);
    if (i == 5) EEPROM.put(Addr, MapValue);
    if (i == 6) EEPROM.put(Addr, UseCelcius);
    if (i == 7) EEPROM.put(Addr, UseKMH);
    if (i == 8) EEPROM.put(Addr, ScreenIndex);

    //Write 3 at the last location to tell data ever get saved
    EEPROM.write(1023, 3);
  }
}

void LoadOptions() {
  if (EEPROM.read(1023) == 3) {
    for (int i=0; i < 9; i++) {
      int Addr = i * 10;
      if (i == 0) EEPROM.get(Addr, Timeout);
      if (i == 1) EEPROM.get(Addr, Injectors_Size);
      if (i == 2) EEPROM.get(Addr, mBarSeaLevel);
      if (i == 3) EEPROM.get(Addr, TrannyType);
      if (i == 4) EEPROM.get(Addr, O2Input);
      if (i == 5) EEPROM.get(Addr, MapValue);
      if (i == 6) EEPROM.get(Addr, UseCelcius);
      if (i == 7) EEPROM.get(Addr, UseKMH);
      if (i == 8) EEPROM.get(Addr, ScreenIndex);
    }
  }
  else
    SaveOptions();
}




