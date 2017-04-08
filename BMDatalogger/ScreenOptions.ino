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
  GetButtonStates();

  //Line 1
  lcd.setCursor(0, 0);
  if (ScreenCurrentIndex == 0) lcd.print("    OPTIONS MENU    ");
  
  //Line 2-4
  for (int i=0; i<6; i++) {
    String Text = "";
    if (ScreenOptionPage == 0) {
      if (i == 0) Text += "INJ:" + String(Injectors_Size);
      if (i == 1) Text += "GB:" + String(GetTrannyStr());
      if (i == 2) Text += "O2IN:" + String(GetO2Str());
      if (i == 3) Text += "MAP:" + String(GetMapStr());
      if (i == 4) Text += "TEMP:" + String(GetTempCelcius());
      if (i == 5) Text += "SPEED:" + String(GetKMH());
    }
    if (ScreenOptionPage == 1) {
      if (i == 0) Text += "DELAY:" + String(Timeout) + "ms";
      if (i == 1) Text += "SLVL:" + String(mBarSeaLevel);
      if (i == 2) Text += "O2:" + String(GetLAMBA());
      if (i == 3) Text += "WB:" + String(GetWBType());
      if (i == 4) Text += "";
      if (i == 5) Text += "";
    }

    //Reset Invalid Char Over Text Lenght
    int ResetLenght = 10 - Text.length();
    for (int i2=0; i2<ResetLenght; i2++) Text += " ";

    SetOffset(i+2);
    lcd.setCursor(Offset, Lines);
    lcd.print(Text);
  }
}

String GetLAMBA() {
  String Str = "";
  if (UseLAMBA == 1) Str = "LAMBA";
  if (UseLAMBA == 0) Str = "AFR";
  return Str;
}

String GetWBType() {
  String Str = "";
  if (WBType == 0) Str = "OEM";
  return Str;
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
  return Str;
}

String GetMapStr() {
  String Str = "";
  if (MapValue == 0) Str = "mBar";
  if (MapValue == 1) Str = "Bar";
  if (MapValue == 2) Str = "inHgG";
  if (MapValue == 3) Str = "inHg";
  if (MapValue == 4) Str = "PSI";
  if (MapValue == 5) Str = "kPa";
  return Str;
}

String GetTempCelcius() {
  String Str = "";
  if (UseCelcius == 1) Str = DegChar + "C";
  if (UseCelcius == 0) Str = DegChar + "F";
  return Str;
}

String GetKMH() {
  String Str = "";
  if (UseKMH == 1) Str = "kmh";
  if (UseKMH == 0) Str = "mph";
  return Str;
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
    if (i == 9) EEPROM.put(Addr, UseLAMBA);
    if (i == 10) EEPROM.put(Addr, WBType);

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
      if (i == 9) EEPROM.get(Addr, UseLAMBA);
      if (i == 10) EEPROM.get(Addr, WBType);
    }
  }
  else
    SaveOptions();
}




