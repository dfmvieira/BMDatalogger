void Display() {
  GetData();
  GetButtonStates();
  
  //Running 8x Loop for 20x04 Display
  for (int i=0; i<8; i++) {
    //Get Text Index
    int ThisScreenIndex = ScreenIndex[i];
    int ThisScreenMode = 0;
    if (ThisScreenIndex >= 50) ThisScreenMode = 1;
    if (ThisScreenIndex >= 100) ThisScreenMode = 2;
    
    //Set Text
    String Text1 = "";
    String Text2 = "";
    if (ThisScreenIndex == 0 | ThisScreenIndex == 50  | ThisScreenIndex == 100) {
      Text1 = "RPM:";
      Text2 = String(GetRpm());
      progBar.setMinValue(0);
      progBar.setMaxValue(11000);
    }
    if (ThisScreenIndex == 1 | ThisScreenIndex == 51  | ThisScreenIndex == 101) {
      Text1 = "ECT:";
      Text2 =  String(GetEct()) + GetTempCelcius();
      progBar.setMinValue(-40);
      progBar.setMaxValue(140);
    }
    if (ThisScreenIndex == 2 | ThisScreenIndex == 52  | ThisScreenIndex == 102) {
      Text1 = "IAT:";
      Text2 = String(GetIat()) + GetTempCelcius();
      progBar.setMinValue(-40);
      progBar.setMaxValue(140);
    }
    if (ThisScreenIndex == 3 | ThisScreenIndex == 53  | ThisScreenIndex == 103) {
      Text1 = "TPS:";
      Text2 = String(GetTps()) + "%";
      progBar.setMinValue(0);
      progBar.setMaxValue(100);
    }
    if (ThisScreenIndex == 4 | ThisScreenIndex == 54  | ThisScreenIndex == 104) {
      Text1 = "O2:";
      Text2 = String(GetO2());
      progBar.setMinValue(0);
      progBar.setMaxValue(20);
    }
    if (ThisScreenIndex == 5 | ThisScreenIndex == 55  | ThisScreenIndex == 105) {
      Text1 = "IGN:";
      Text2 = String(GetIgn());
      progBar.setMinValue(-6);
      progBar.setMaxValue(60);
    }
    if (ThisScreenIndex == 6 | ThisScreenIndex == 56  | ThisScreenIndex == 106) {
      Text1 = "INJ:";
      Text2 = String(GetInj()) + "ms";
      progBar.setMinValue(0);
      progBar.setMaxValue(20);
    }
    if (ThisScreenIndex == 7 | ThisScreenIndex == 57  | ThisScreenIndex == 107) {
      Text1 = "FUEL:";
      Text2 = String(GetInstantConsumption()) + "L";
      progBar.setMinValue(0);
      progBar.setMaxValue(50);
    }
    if (ThisScreenIndex == 8 | ThisScreenIndex == 58  | ThisScreenIndex == 108) {
      Text1 = "IACV:";
      Text2 = String(GetIACVDuty());
      progBar.setMinValue(-100);
      progBar.setMaxValue(100);
    }
    if (ThisScreenIndex == 9 | ThisScreenIndex == 59  | ThisScreenIndex == 109) {
      Text1 = GetMapStr() + ":";
      Text2 = String(GetMap());
      progBar.setMinValue(0);
      progBar.setMaxValue(1048);
    }
    if (ThisScreenIndex == 10 | ThisScreenIndex == 60  | ThisScreenIndex == 110) {
      Text1 = "VSS:";
      Text2 = String(GetVss()) + GetKMH();
      progBar.setMinValue(0);
      progBar.setMaxValue(300);
    }
    if (ThisScreenIndex == 11 | ThisScreenIndex == 61  | ThisScreenIndex == 111) {
      Text1 = "Gear:";
      Text2 = String(GetGear());
      progBar.setMinValue(0);
      progBar.setMaxValue(5);
    }
    if (ThisScreenIndex == 12 | ThisScreenIndex == 62  | ThisScreenIndex == 112) {
      Text1 = "BATT:";
      Text2 = String(GetBattery());
      progBar.setMinValue(0);
      progBar.setMaxValue(16);
    }
    if (ThisScreenIndex == 13 | ThisScreenIndex == 63  | ThisScreenIndex == 113) {
      Text1 = "ICUT:";
      Text2 = String(GetIgnCut());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }
    if (ThisScreenIndex == 14 | ThisScreenIndex == 64  | ThisScreenIndex == 114) {
      Text1 = "FCUT:";
      Text2 = String(GetFuelCut1());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }
    if (ThisScreenIndex == 15 | ThisScreenIndex == 65  | ThisScreenIndex == 115) {
      Text1 = "INJFV:";
      Text2 = String(GetInjFV());
      progBar.setMinValue(0);
      progBar.setMaxValue(3000);
    }
    if (ThisScreenIndex == 16 | ThisScreenIndex == 66  | ThisScreenIndex == 116) {
      Text1 = "2MAP:";
      Text2 = String(GetOutput2ndMap());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }
    if (ThisScreenIndex == 17 | ThisScreenIndex == 67  | ThisScreenIndex == 117) {
      Text1 = "FTLO:";
      Text2 = String(GetOutputFTL());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }
    if (ThisScreenIndex == 18 | ThisScreenIndex == 68  | ThisScreenIndex == 118) {
      Text1 = "ATLG:";
      Text2 = String(GetOutputAntilag());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }
    if (ThisScreenIndex == 19 | ThisScreenIndex == 69  | ThisScreenIndex == 119) {
      Text1 = "FTSO:";
      Text2 = String(GetOutputFTS());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }
    if (ThisScreenIndex == 20 | ThisScreenIndex == 70  | ThisScreenIndex == 120) {
      Text1 = "EBCO:";
      Text2 = String(GetOutputEBC());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }
    if (ThisScreenIndex == 21 | ThisScreenIndex == 71  | ThisScreenIndex == 121) {
      Text1 = "FCTRLO:";
      Text2 = String(GetOutputFanCtrl());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }
    if (ThisScreenIndex == 22 | ThisScreenIndex == 72  | ThisScreenIndex == 122) {
      Text1 = "BSTO:";
      Text2 = String(GetOutputBST());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }
    
    //Reset Invalid Char Over Text Lenght
    if (ThisScreenMode < 2) {
      Text1 = Text1 + Text2;
      int ResetLenght = 10 - Text1.length();
      for (int i2=0; i2<ResetLenght; i2++) Text1 += " ";
    }

    //Reset Offset for bigfont & progressbar (always start of the line)
    if (ThisScreenMode > 0) Offset = 0;

    SetOffset(i);
    lcd.setCursor(Offset, Lines);
    if (ThisScreenMode != 2) lcd.print(Text1);  //dont print this text for BigFont (missing space)

    //Display Progressbar
    if (ThisScreenMode == 1) {
      //Line 10-20 serve to display Progressbar
      Offset += 10;
      lcd.setCursor(Offset, Lines);

      int Value = 15;
      progBar.drawValue(Value);
      
      //Increase 1 index (doesnt overlay display, since progressbar use 2x display)
      i++;
    }

    //Display BigFont
    if (ThisScreenMode == 2) {
      //Reset Big Text
      int ResetLenght = 6 - Text2.length();
      for (int i2=0; i2<ResetLenght; i2++) Text2 += " ";
      
      //Display Big Text
      char charBuf[sizeof(Text2)];
      Text2.toCharArray(charBuf, 6); 
      render_big_msg(charBuf,Offset,Lines);
      
      //Set 2nd line texts (spaces)
      Text1 = "";
      for (int i2=0; i2 < sizeof(Text1); i2++) Text1 += " ";
      Lines++;
      lcd.setCursor(Offset, Lines);
      lcd.print(Text1);
      
      //Increase 3 index (doesnt overlay display, since big font use 4x display)
      i += 3;
    }
  }
}

void SetOffset(int ThisLine) {
  //Offset the text (to show 2x value wide rather than only one)
  Offset = 0;
  Lines = ThisLine;
    
  if (ThisLine == 1)  {
      Lines = 0;
      Offset = 10;
    }
    if (ThisLine == 2) Lines = 1;
    if (ThisLine == 3) {
      Lines = 1;
      Offset = 10;
    }
    if (ThisLine == 4) Lines = 2;
    if (ThisLine == 5) {
      Lines = 2;
      Offset = 10;
    }
    if (ThisLine == 6) Lines = 3;
    if (ThisLine == 7) {
      Lines = 3;
      Offset = 10;
    }
}
