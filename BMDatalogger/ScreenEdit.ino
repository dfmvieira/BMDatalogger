void DisplayEdit() {
  GetButtonStates();
  
  //Set Top Title
  lcd.setCursor(0, 0);
  lcd.print("   EDIT PARAMETER   ");
  lcd.setCursor(0, 1);
  if (ScreenOptionPage == 0) {
    if (ScreenCurrentIndex == 0) lcd.print("    INJECTOR SIZE   ");
    if (ScreenCurrentIndex == 1) lcd.print("    GEARBOX TYPE    ");
    if (ScreenCurrentIndex == 2) lcd.print("      O2 INPUT      ");
    if (ScreenCurrentIndex == 3) lcd.print("      MAP TYPE      ");
    if (ScreenCurrentIndex == 4) lcd.print("  TEMPERATURE TYPE  ");
    if (ScreenCurrentIndex == 5) lcd.print("     SPEED TYPE     ");
  }
  if (ScreenOptionPage == 1) {
    if (ScreenCurrentIndex == 0) lcd.print("    DISPLAY DELAY   ");
    if (ScreenCurrentIndex == 1) lcd.print("   MBAR SEA LEVEL   ");
    if (ScreenCurrentIndex == 2) lcd.print("  O2 DISPLAY TYPE   ");
    if (ScreenCurrentIndex == 3) lcd.print("   WIDEBAND TYPE    ");
    if (ScreenCurrentIndex == 4) ScreenEdit = false;
    if (ScreenCurrentIndex == 5) ScreenEdit = false;
  }
  
  //Set Bottom Edit Texts
  String Text1 = "";

  //Screen1
  if (ScreenOptionPage == 0) {
    if (ScreenCurrentIndex == 0) {
      Text1 = "   " + String(Injectors_Size);
      DisplayModel1();
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
  }

  //Screen2
  if (ScreenOptionPage == 1) {
    if (ScreenCurrentIndex == 0) {
      Text1 = "   " + String(Timeout);
      DisplayModel1();
    }
    if (ScreenCurrentIndex == 1) {
      Text1 = "   " + String(mBarSeaLevel);
      DisplayModel1();
    }
    if (ScreenCurrentIndex == 2) {
      Text1 = "   " + String(GetLAMBA());
      DisplayModel2();
    }
    if (ScreenCurrentIndex == 3) {
      Text1 = "   " + String(GetWBType());
      DisplayModel2();
    }
  }
  
  int ResetLenght = 10 - Text1.length();
  for (int i2=0; i2<ResetLenght; i2++) Text1 += " ";
  lcd.setCursor(0, 2);
  lcd.print(Text1);
}

void DisplayModel1() {
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
  //Screen1
  if (ScreenOptionPage == 0) {
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
  }

  //Screen2
  if (ScreenOptionPage == 1) {
    if (ScreenCurrentIndex == 0) {
      if (!ScreenEditInc) Timeout -= 5;
      if (ScreenEditInc) Timeout += 5;
    }
    if (ScreenCurrentIndex == 1) {
      if (!ScreenEditInc) mBarSeaLevel -= 10;
      if (ScreenEditInc) mBarSeaLevel += 10;
    }
    if (ScreenCurrentIndex == 2) {
      UseLAMBA++;
      if (UseLAMBA > 1) UseLAMBA = 0;
    }
    if (ScreenCurrentIndex == 3) {
      WBType++;
      if (WBType > 0) WBType = 0;
    }
  }
}

//Botom Button Input
void EditBottom() {
  if (!ScreenEditInc) ScreenEditInc = true;
  else ScreenEditInc = false;
}
