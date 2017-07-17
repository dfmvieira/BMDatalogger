void Display() {
  /*unsigned long current_time = millis();
  if (current_time - last_datalog_time > Timeout) {
    GetData();
    ApplyPeak();
    last_datalog_time = current_time;
  }

  SetSpeedTime();
  GetWarnings();*/
  
  for (int i=0; i<8; i++) {
    ThisScreenIndex = 0;
    if (ScreenCurrentPage == 0) ScreenCurrentPage = 1;
    if (ScreenCurrentPage == 1) ThisScreenIndex = ScreenPage1[i];
    if (ScreenCurrentPage == 2) ThisScreenIndex = ScreenPage2[i];
    if (ScreenCurrentPage == 3) ThisScreenIndex = ScreenPage3[i];
    if (ScreenCurrentPage == 4) ThisScreenIndex = ScreenPage4[i];
    if (ScreenCurrentPage == 5) ThisScreenIndex = ScreenPage5[i];
    if (ScreenCurrentPage == 6) ThisScreenIndex = ScreenPage6[i];
    if (ScreenCurrentPage == 7) ThisScreenIndex = ScreenPage7[i];
    if (ScreenCurrentPage == 8) ThisScreenIndex = ScreenPage8[i];
    if (ScreenCurrentMenu == 1) ThisScreenIndex = ScreenCurrentPeak;

    int ThisScreenMode = 0;                                 //normal
    if (ThisScreenIndex >= 50) ThisScreenMode = 1;          //progressbar
    if (ThisScreenIndex >= 100) ThisScreenMode = 2;         //big
    if (ThisScreenIndex >= 150) ThisScreenMode = 3;         //big2
    if (ScreenCurrentMenu == 1) ThisScreenMode = 4;         //peak
    if (ScreenCurrentMenu == 2) ThisScreenMode = 5;         //mil

    if (ThisScreenMode != 5) {
      if (ThisScreenIndex >= 50 && ThisScreenIndex < 100) ThisScreenIndex -= 50;
      if (ThisScreenIndex >= 100 && ThisScreenIndex < 150) ThisScreenIndex -= 100;
      if (ThisScreenIndex >= 150) ThisScreenIndex -= 150;

      ResetBufferIndex();
      
      //Empty
      /*if (ThisScreenIndex >= MaxDataValue) {
        SetPos(i);
        if (ThisScreenMode >= 1) XPos = 0;
        if (ThisScreenMode >= 3) YPos = 0;
        PrintText(10, XPos, YPos);
        if (ThisScreenMode >= 1) PrintText(20, XPos, YPos);
        if (ThisScreenMode >= 2) PrintText(20, XPos, YPos + 1);
        if (ThisScreenMode == 3) {
          PrintText(20, XPos, YPos + 3);
          PrintText(20, XPos, YPos + 4);
        }
      }*/

      //Only Run 'reconized' data values
      if (ThisScreenIndex < MaxDataValue) {
        GetSensorString(ThisScreenIndex);
        
        if (ThisScreenMode < 2) {
          SetValueToBuffer();
          Add_Sensor_Desc();
        }
    
        SetPos(i);
        if (ThisScreenMode >= 1) XPos = 0;
        if (ThisScreenMode >= 3) YPos = 0;

        //normal
        if (ThisScreenMode == 0) {
          PrintText(10, XPos, YPos);
        }

        //progressbar
        if (ThisScreenMode == 1) {
          if (ProgressBarLeft == 0) XPos = 10;
          PrintText(10, XPos, YPos);
          if (ProgressBarLeft == 0) XPos = 0;
          if (ProgressBarLeft == 1) XPos = 10;
          DrawProgressBar(GetInt(), 10);
          i++;
        }

        //big font
        if (ThisScreenMode == 2) {
          PrintTextLenght(XPos, YPos);
          int StartAt = GetBufferLenght();
          ResetBufferIndex();
          SetValueToBuffer();
          writeBigString(StartAt, YPos);
          i += 3;
        }

        //big font #2
        if (ThisScreenMode == 3) {
          writeBigString(XPos, YPos);
          ResetBufferIndex();
          SetValueToBuffer();
          writeBigString(XPos, YPos+2);
          i += 8;
        }

        //peak
        if (ThisScreenMode == 4) {
          writeBigString(XPos, YPos);
          ResetBufferIndex();
          GetInfosString(15);
          Add_String(String(GetPeakMin()));
          Add_Sensor_Desc();
          PrintText(10, XPos, YPos + 2);

          ResetBufferIndex();
          GetInfosString(17);
          SetValueToBuffer();
          Add_Sensor_Desc();
          PrintText(10, XPos + 10, YPos + 2);
          
          ResetBufferIndex();
          GetInfosString(16);
          Add_String(String(GetPeakMax()));
          Add_Sensor_Desc();
          PrintText(20, XPos, YPos + 3);
          
          i += 8;
        }
      }
    }
    else {
      //Mil Menu
      ResetBufferIndex();
      GetInfosString(9);
      writeBigString(5, 0);
      GetMil();
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

int GetInt() {
  if (ThisScreenIndex == 0) return (int) GetRpm();
  if (ThisScreenIndex == 1) return (int) GetEct();
  if (ThisScreenIndex == 2) return (int) GetIat();
  if (ThisScreenIndex == 3) return (int) GetTps();
  if (ThisScreenIndex == 4) return (int) GetO2();
  if (ThisScreenIndex == 5) return (int) GetIgn();
  if (ThisScreenIndex == 6) return (int) GetInjDurr();
  if (ThisScreenIndex == 7) return (int) GetInstantConsumption();
  if (ThisScreenIndex == 8) return (int) GetIACVDuty();
  if (ThisScreenIndex == 9) return (int) GetMap();
  if (ThisScreenIndex == 10) return (int) GetBoost();
  if (ThisScreenIndex == 11) return (int) GetVss();
  if (ThisScreenIndex == 12) return (int) GetOutputFanCtrl();
  if (ThisScreenIndex == 13) return (int) GetBattery();
  if (ThisScreenIndex == 14) return (int) GetIgnCut();
  if (ThisScreenIndex == 15) return (int) GetFuelCut1();
  if (ThisScreenIndex == 16) return (int) GetInjFV();
  if (ThisScreenIndex == 17) return (int) GetOutput2ndMap();
  if (ThisScreenIndex == 18) return (int) GetSpeedTime();
  if (ThisScreenIndex == 19) return (int) GetBestSpeedTime();
  if (ThisScreenIndex == 20) return (int) GetVTS();
  if (ThisScreenIndex == 21) return (int) GetVTP();
  if (ThisScreenIndex == 22) return (int) GetELDVolt();
  if (ThisScreenIndex == 23) return (int) GetO2Heater();
  if (ThisScreenIndex == 24) return (int) GetAC();
  if (ThisScreenIndex == 25) return (int) GetAtlCtrl();
  if (ThisScreenIndex == 26) return (int) GetGear();
}

void SetValueToBuffer() {
  if (ThisScreenIndex == 0) Add_String(String(GetRpm()));
  if (ThisScreenIndex == 1) Add_String(String(GetEct()));
  if (ThisScreenIndex == 2) Add_String(String(GetIat()));
  if (ThisScreenIndex == 3) Add_String(String(GetTps()));
  if (ThisScreenIndex == 4) Add_String(String(GetO2()));
  if (ThisScreenIndex == 5) Add_String(String(GetIgn()));
  if (ThisScreenIndex == 6) Add_String(String(GetInjDurr()));
  if (ThisScreenIndex == 7) Add_String(String(GetInstantConsumption()));
  if (ThisScreenIndex == 8) Add_String(String(GetIACVDuty()));
  if (ThisScreenIndex == 9) Add_String(String(GetMap()));
  if (ThisScreenIndex == 10) Add_String(String(GetBoost()));
  if (ThisScreenIndex == 11) Add_String(String(GetVss()));
  if (ThisScreenIndex == 12) GetActivatedString(GetOutputFanCtrl());
  if (ThisScreenIndex == 13) Add_String(String(GetBattery()));
  if (ThisScreenIndex == 14) GetActivatedString(GetIgnCut());
  if (ThisScreenIndex == 15) GetActivatedString(GetFuelCut1());
  if (ThisScreenIndex == 16) Add_String(String(GetInjFV()));
  if (ThisScreenIndex == 17) GetActivatedString(GetOutput2ndMap());
  if (ThisScreenIndex == 18) Add_String(String(GetSpeedTime()));
  if (ThisScreenIndex == 19) Add_String(String(GetBestSpeedTime()));
  if (ThisScreenIndex == 20) GetActivatedString(GetVTS());
  if (ThisScreenIndex == 21) GetActivatedString(GetVTP());
  if (ThisScreenIndex == 22) Add_String(String(GetELDVolt()));
  if (ThisScreenIndex == 23) GetActivatedString(GetO2Heater());
  if (ThisScreenIndex == 24) GetActivatedString(GetAC());
  if (ThisScreenIndex == 25) GetActivatedString(GetAtlCtrl());
  if (ThisScreenIndex == 26) Add_String(String(GetGear()));

  //remake double into 1decimal
  if (ThisScreenIndex == 4) RemoveLastChar();
  if (ThisScreenIndex == 7) RemoveLastChar();
  if (ThisScreenIndex == 10) RemoveLastChar();
  if (ThisScreenIndex == 13) RemoveLastChar();
  if (ThisScreenIndex == 18) RemoveLastChar();
  if (ThisScreenIndex == 19) RemoveLastChar();
}

