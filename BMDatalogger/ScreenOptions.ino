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




