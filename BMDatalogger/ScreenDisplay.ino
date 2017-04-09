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
      GraphSetValue(0, 11000);
    }
    if (ThisScreenIndex == 1 | ThisScreenIndex == 51  | ThisScreenIndex == 101) {
      Text1 = "ECT:";
      Text2 =  String(GetEct()) + GetTempCelcius();
      GraphSetValue(-40, 140);
    }
    if (ThisScreenIndex == 2 | ThisScreenIndex == 52  | ThisScreenIndex == 102) {
      Text1 = "IAT:";
      Text2 = String(GetIat()) + GetTempCelcius();
      GraphSetValue(-40, 140);
    }
    if (ThisScreenIndex == 3 | ThisScreenIndex == 53  | ThisScreenIndex == 103) {
      Text1 = "TPS:";
      Text2 = String(GetTps()) + "%";
      GraphSetValue(0, 100);
    }
    if (ThisScreenIndex == 4 | ThisScreenIndex == 54  | ThisScreenIndex == 104) {
      Text1 = "O2:";
      Text2 = String(GetO2());
      GraphSetValue(0, 20);
    }
    if (ThisScreenIndex == 5 | ThisScreenIndex == 55  | ThisScreenIndex == 105) {
      Text1 = "IGN:";
      Text2 = String(GetIgn());
      GraphSetValue(-6, 60);
    }
    if (ThisScreenIndex == 6 | ThisScreenIndex == 56  | ThisScreenIndex == 106) {
      Text1 = "INJ:";
      Text2 = String(GetInj()) + "ms";
      GraphSetValue(0, 20);
    }
    if (ThisScreenIndex == 7 | ThisScreenIndex == 57  | ThisScreenIndex == 107) {
      Text1 = "FUEL:";
      Text2 = String(GetInstantConsumption()) + "L";
      GraphSetValue(0, 50);
    }
    if (ThisScreenIndex == 8 | ThisScreenIndex == 58  | ThisScreenIndex == 108) {
      Text1 = "IACV:";
      Text2 = String(GetIACVDuty());
      GraphSetValue(-100, 100);
    }
    if (ThisScreenIndex == 9 | ThisScreenIndex == 59  | ThisScreenIndex == 109) {
      Text1 = GetMapStr() + ":";
      Text2 = String(GetMap());
      GraphSetValue(0, 1048);
    }
    if (ThisScreenIndex == 10 | ThisScreenIndex == 60  | ThisScreenIndex == 110) {
      Text1 = "VSS:";
      Text2 = String(GetVss()) + GetKMH();
      GraphSetValue(0, 300);
    }
    if (ThisScreenIndex == 11 | ThisScreenIndex == 61  | ThisScreenIndex == 111) {
      Text1 = "Gear:";
      Text2 = String(GetGear());
      GraphSetValue(0, 5);
    }
    if (ThisScreenIndex == 12 | ThisScreenIndex == 62  | ThisScreenIndex == 112) {
      Text1 = "BATT:";
      Text2 = String(GetBattery());
      GraphSetValue(0, 16);
    }
    if (ThisScreenIndex == 13 | ThisScreenIndex == 63  | ThisScreenIndex == 113) {
      Text1 = "ICUT:";
      Text2 = String(GetIgnCut());
      GraphSetValue(0, 1);
    }
    if (ThisScreenIndex == 14 | ThisScreenIndex == 64  | ThisScreenIndex == 114) {
      Text1 = "FCUT:";
      Text2 = String(GetFuelCut1());
      GraphSetValue(0, 1);
    }
    if (ThisScreenIndex == 15 | ThisScreenIndex == 65  | ThisScreenIndex == 115) {
      Text1 = "INJFV:";
      Text2 = String(GetInjFV());
      GraphSetValue(0, 3000);
    }
    if (ThisScreenIndex == 16 | ThisScreenIndex == 66  | ThisScreenIndex == 116) {
      Text1 = "2MAP:";
      Text2 = String(GetOutput2ndMap());
     GraphSetValue(0, 1);
    }
    if (ThisScreenIndex == 17 | ThisScreenIndex == 67  | ThisScreenIndex == 117) {
      Text1 = "FTLO:";
      Text2 = String(GetOutputFTL());
      GraphSetValue(0, 1);
    }
    if (ThisScreenIndex == 18 | ThisScreenIndex == 68  | ThisScreenIndex == 118) {
      Text1 = "ATLG:";
      Text2 = String(GetOutputAntilag());
      GraphSetValue(0, 1);
    }
    if (ThisScreenIndex == 19 | ThisScreenIndex == 69  | ThisScreenIndex == 119) {
      Text1 = "FTSO:";
      Text2 = String(GetOutputFTS());
      GraphSetValue(0, 1);
    }
    if (ThisScreenIndex == 20 | ThisScreenIndex == 70  | ThisScreenIndex == 120) {
      Text1 = "EBCO:";
      Text2 = String(GetOutputEBC());
      GraphSetValue(0, 1);
    }
    if (ThisScreenIndex == 21 | ThisScreenIndex == 71  | ThisScreenIndex == 121) {
      Text1 = "FCTRLO:";
      Text2 = String(GetOutputFanCtrl());
      GraphSetValue(0, 1);
    }
    if (ThisScreenIndex == 22 | ThisScreenIndex == 72  | ThisScreenIndex == 122) {
      Text1 = "BSTO:";
      Text2 = String(GetOutputBST());
      GraphSetValue(0, 1);
    }
    
    //Reset Invalid Char Over Text Lenght
    if (ThisScreenMode < 2) {
      Text1 += Text2;
      for (int i2=0; i2< (10 - Text1.length()); i2++) Text1 += " ";
    }
    
    //Set/Reset Offset
    SetOffset(i);
    if (ThisScreenMode > 0) Offset = 0;
    lcd.setCursor(Offset, Lines);
    if (ThisScreenMode < 2) lcd.print(Text1);
    
    //Display Progressbar
    if (ThisScreenMode == 1) {
      //Line 10-20 serve to display Progressbar
      Offset += 10;
      lcd.setCursor(Offset, Lines);
      GraphDrawValue(Text2.toInt());
      
      //Increase 1 index (doesnt overlay display, since progressbar use 2x display)
      i++;
    }

    //Display BigFont
    if (ThisScreenMode == 2) {
      //Reset Big Text
      for (int i2=0; i2< (10 - Text2.length()); i2++) Text2 += " ";
      
      //Display Big Text
      char charBuf[sizeof(Text2)];
      Text2.toCharArray(charBuf, sizeof(Text2));
      writeBigString(charBuf, Offset, Lines);
      //render_big_msg(charBuf, Offset, Lines);
      
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
