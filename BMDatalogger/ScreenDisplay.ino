void Display() {
  GetData();
  
  for (int i=0; i<8; i++) {
    ThisScreenIndex = 0;
    if (ScreenCurrentPage == 1) ThisScreenIndex = ScreenPage1[i];
    if (ScreenCurrentPage == 2) ThisScreenIndex = ScreenPage2[i];
    if (ScreenCurrentPage == 3) ThisScreenIndex = ScreenPage3[i];
    if (ScreenCurrentPage == 4) ThisScreenIndex = ScreenPage4[i];
    if (ScreenCurrentMenu == 1) ThisScreenIndex = ScreenCurrentPeak;

    if (ThisScreenIndex >= 50 && ThisScreenIndex < 100) ThisScreenIndex -= 50;
    if (ThisScreenIndex >= 100) ThisScreenIndex -= 100;

    int ThisScreenMode = 0;
    if (ThisScreenIndex >= 50) ThisScreenMode = 1;
    if (ThisScreenIndex >= 100) ThisScreenMode = 2;
    if (ScreenCurrentMenu == 1) ThisScreenMode = 3;
    
    ResetBufferIndex(false);
    GetStringAt(false, ThisScreenIndex, false);
    if (ThisScreenMode < 2) SetValueToBuffer();

    if (ThisScreenIndex == 1) GetTempCelcius();
    if (ThisScreenIndex == 2) GetTempCelcius();
    if (ThisScreenIndex == 3) GetStringAt(false, 2, true);
    if (ThisScreenIndex == 6) GetStringAt(false, 3, true);
    if (ThisScreenIndex == 7) GetStringAt(false, 4, true);
    if (ThisScreenIndex == 11) GetKMH();

    SetSpeedTime();
    SetPeak();
    SetPos(i);
    if (ThisScreenMode >= 1) XPos = 0;
    if (ThisScreenMode >= 2) YPos = 0;
    lcd.setCursor(XPos, YPos);
    
    if (ThisScreenMode < 2) lcd.print(StringBuffer);
    
    if (ThisScreenMode == 1) {
      lcd.setCursor(XPos+10, YPos);
      GraphDrawValue(GetInt(), 10);
      i++;
    }

    if (ThisScreenMode == 2) {
      writeBigString(StringBuffer, XPos, YPos);
      ResetBufferIndex(false);
      SetValueToBuffer();
      writeBigString(StringBuffer, XPos, YPos+2);
      i += 8;
    }

    if (ThisScreenMode == 3) {
      writeBigString(StringBuffer, XPos, YPos);
      ResetBufferIndex(false);
      Add_String(true, "Minimum :");
      Add_String(true, String(GetPeakMin()));
      lcd.setCursor(XPos, YPos + 2);
      lcd.print(StringBufferLong);
      
      ResetBufferIndex(false);
      Add_String(true, "Maximum :");
      Add_String(true, String(GetPeakMax()));
      lcd.setCursor(XPos, YPos + 3);
      lcd.print(StringBufferLong);
      
      i += 8;
    }
  }
}

void SetPos(const int ThisLine) {
  XPos = 0;
  YPos = ThisLine;
    
  if (ThisLine == 1)  {
    XPos = 10;
    YPos = 0;
  }
  if (ThisLine == 2) YPos = 1;
  if (ThisLine == 3) {
    XPos = 10;
    YPos = 1;
  }
  if (ThisLine == 4) YPos = 2;
  if (ThisLine == 5) {
    XPos = 10;
    YPos = 2;
  }
  if (ThisLine == 6) YPos = 3;
  if (ThisLine == 7) {
    XPos = 10;
    YPos = 3;
  }
}

void GetTempCelcius() {
   if (CurrentBufferIndex <= 9) {
    StringBuffer[CurrentBufferIndex] = (char)0xDF; //(char) 223
    CurrentBufferIndex++;
    
    if (UseCelcius == 1) StringBuffer[CurrentBufferIndex] = 'C';
    if (UseCelcius == 0) StringBuffer[CurrentBufferIndex] = 'F';
    CurrentBufferIndex++;
  }
}

void GetKMH() {
  if (UseKMH == 1) GetStringAt(false, 0, true);
  if (UseKMH == 0) GetStringAt(false, 1, true);
}

int GetInt() {
  if (ThisScreenIndex == 0) return (int) GetRpm();
  if (ThisScreenIndex == 1) return (int) GetEct();
  if (ThisScreenIndex == 2) return (int) GetIat();
  if (ThisScreenIndex == 3) return (int) GetTps();
  if (ThisScreenIndex == 4) return (int) GetO2();
  if (ThisScreenIndex == 5) return (int) GetIgn();
  if (ThisScreenIndex == 6) return (int) GetInj();
  if (ThisScreenIndex == 7) return (int) GetInstantConsumption();
  if (ThisScreenIndex == 8) return (int) GetIACVDuty();
  if (ThisScreenIndex == 9) return (int) GetMap();
  if (ThisScreenIndex == 10) return (int) GetBoost();
  if (ThisScreenIndex == 11) return (int) GetVss();
  if (ThisScreenIndex == 12) return (int) GetGear();
  if (ThisScreenIndex == 13) return (int) GetBattery();
  if (ThisScreenIndex == 14) return (int) GetIgnCut();
  if (ThisScreenIndex == 15) return (int) GetFuelCut1();
  if (ThisScreenIndex == 16) return (int) GetInjFV();
  if (ThisScreenIndex == 17) return (int) GetOutput2ndMap();
  if (ThisScreenIndex == 18) return (int) GetSpeedTime();
  if (ThisScreenIndex == 19) return (int) GetBestSpeedTime();
}

void SetValueToBuffer() {
  if (ThisScreenIndex == 0) Add_String(false, String(GetRpm()));
  if (ThisScreenIndex == 1) Add_String(false, String(GetEct()));
  if (ThisScreenIndex == 2) Add_String(false, String(GetIat()));
  if (ThisScreenIndex == 3) Add_String(false, String(GetTps()));
  if (ThisScreenIndex == 4) Add_String(false, String(GetO2()));
  if (ThisScreenIndex == 5) Add_String(false, String(GetIgn()));
  if (ThisScreenIndex == 6) Add_String(false, String(GetInj()));
  if (ThisScreenIndex == 7) Add_String(false, String(GetInstantConsumption()));
  if (ThisScreenIndex == 8) Add_String(false, String(GetIACVDuty()));
  if (ThisScreenIndex == 9) Add_String(false, String(GetMap()));
  if (ThisScreenIndex == 10) Add_String(false, String(GetBoost()));
  if (ThisScreenIndex == 11) Add_String(false, String(GetVss()));
  if (ThisScreenIndex == 12) Add_String(false, String(GetGear()));
  if (ThisScreenIndex == 13) Add_String(false, String(GetBattery()));
  if (ThisScreenIndex == 14) Add_String(false, String(GetIgnCut()));
  if (ThisScreenIndex == 15) Add_String(false, String(GetFuelCut1()));
  if (ThisScreenIndex == 16) Add_String(false, String(GetInjFV()));
  if (ThisScreenIndex == 17) Add_String(false, String(GetOutput2ndMap()));
  if (ThisScreenIndex == 18) Add_String(false, String(GetSpeedTime()));
  if (ThisScreenIndex == 19) Add_String(false, String(GetBestSpeedTime()));
}

void SetPeak() {
  if (ThisScreenIndex == 0) SetPeakValue(0, 11000);
  if (ThisScreenIndex == 1) SetPeakValue(-40, 140);
  if (ThisScreenIndex == 2) SetPeakValue(-40, 140);
  if (ThisScreenIndex == 3) SetPeakValue(0, 100);
  if (ThisScreenIndex == 4) {
    if (UseLAMBA) SetPeakValue(0, 5);
    if (!UseLAMBA) SetPeakValue(10, 20);
  }
  if (ThisScreenIndex == 5) SetPeakValue(-6, 60);
  if (ThisScreenIndex == 6) SetPeakValue(0, 20);
  if (ThisScreenIndex == 7) SetPeakValue(0, 50);
  if (ThisScreenIndex == 8) SetPeakValue(-100, 100);
  if (ThisScreenIndex == 9) SetPeakValue(0, 1048);
  if (ThisScreenIndex == 10) SetPeakValue(0, 40);
  if (ThisScreenIndex == 11) SetPeakValue(0, 300);
  if (ThisScreenIndex == 12) SetPeakValue(0, 5);
  if (ThisScreenIndex == 13) SetPeakValue(0, 16);
  if (ThisScreenIndex == 14) SetPeakValue(0, 1);
  if (ThisScreenIndex == 15) SetPeakValue(0, 1);
  if (ThisScreenIndex == 16) SetPeakValue(0, 3000);
  if (ThisScreenIndex == 17) SetPeakValue(0, 1);
  if (ThisScreenIndex == 18) SetPeakValue(2, 18);
  if (ThisScreenIndex == 19) SetPeakValue(2, 18);

  ApplyPeak();
}

