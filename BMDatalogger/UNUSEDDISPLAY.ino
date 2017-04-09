//###########################################################################################################
//###########################################################################################################
//###########################################################################################################
//DISPLAY
    //POSSIBLE USELESS DATALOGS
    //if (ThisScreenIndex == 8 | ThisScreenIndex == 58  | ThisScreenIndex == 108) {
    //  Text1 = "DTY:";
    //  Text2 = String(GetInjectorDuty());
    //  progBar.setMinValue(0);
    //  progBar.setMaxValue(50);
    //}
    //if (ThisScreenIndex == 16) {
    //  Text1 = "INJDU:";
    //  Text2 = String(GetInjDuration());
    //  Min = 0;
    //  Max = 11000;
    //}
    /*if (ThisScreenIndex == 16 | ThisScreenIndex == 66  | ThisScreenIndex == 116) {
      Text1 = "VTP:";
      Text2 = String(GetVTP());
      progBar.setMinValue(0);
      progBar.setMaxValue(1);
    }*/
    //if (ThisScreenIndex == 00) Text += "VTSM:" + String(GetVTSM());
    //if (ThisScreenIndex == 00) Text += "FCUT2:" + String(GetFuelCut2());
    //if (ThisScreenIndex == 00) Text += "FCTRL:" + String(GetFanCtrl());
    //if (ThisScreenIndex == 00) Text += "ACTRL:" + String(GetAtlCtrl());
    //if (ThisScreenIndex == 00) Text += "MIL:" + String(GetMIL());
    //if (ThisScreenIndex == 00) Text += "FTLI:" + String(GetInputFTL());
    //if (ThisScreenIndex == 00) Text += "FTSI:" + String(GetInputFTS());
    //if (ThisScreenIndex == 00) Text += "EBCI:" + String(GetInputEBC());
    //if (ThisScreenIndex == 00) Text += "BSTI:" + String(GetInputBST());
    //if (ThisScreenIndex == 00) Text += "BSTCT:" + String(GetOutputBoostCut());
    //if (ThisScreenIndex == 00) Text += "   BARO:" + String(GetBaro());
    //if (ThisScreenIndex == 00) Text += "    PSTF:" + String(GetPostFuel());
    //if (ThisScreenIndex == 00) Text += "   SCC.C:" + String(GetSCCChecker());
    //if (ThisScreenIndex == 00) Text += "   ATSF1:" + String(GetATShift1());
    //if (ThisScreenIndex == 00) Text += "   ATSF2:" + String(GetATShift2());
    //if (ThisScreenIndex == 00) Text += "    IGNT:" + String(GetIgnTable());
    //if (ThisScreenIndex == 00) Text += "    PARK:" + String(GetParkN());
    //if (ThisScreenIndex == 00) Text += "    BKSW:" + String(GetBKSW());
    //if (ThisScreenIndex == 00) Text += "    ACC:" + String(GetACC());
    //if (ThisScreenIndex == 00) Text += "    STRT:" + String(GetStart());
    //if (ThisScreenIndex == 00) Text += "    SCC:" + String(GetSCC());
    //if (ThisScreenIndex == 00) Text += "   VTSFB:" + String(GetVTSFeedBack());
    //if (ThisScreenIndex == 00) Text += "    PSP:" + String(GetPSP());
    //if (ThisScreenIndex == 00) Text += "    FPMP:" + String(GetFuelPump());
    //if (ThisScreenIndex == 00) Text += "    IAB:" + String(GetIAB());
    //if (ThisScreenIndex == 00) Text += "   PURGE:" + String(GetPurge());
    //if (ThisScreenIndex == 00) Text += "    AC:" + String(GetAC());
    //if (ThisScreenIndex == 00) Text += "    O2H:" + String(GetO2Heater());
    //if (ThisScreenIndex == 00) Text += "    VTS:" + String(GetVTS());
    //if (ThisScreenIndex == 00) Text += "  ELDV:" + String(GetELDVolt()) + "v";
    //if (ThisScreenIndex == 00) Text += "   ECTFC:" + String(GetECTFC());
    //if (ThisScreenIndex == 00) Text += "    O2S:" + String(GetO2Short());
    //if (ThisScreenIndex == 00) Text += "    O2L:" + String(GetO2Long());
    //if (ThisScreenIndex == 00) Text += "   IATFC:" + String(GetIATFC());
    //if (ThisScreenIndex == 00) Text += "   VEFC:" + String(GetVEFC());
    //if (ThisScreenIndex == 00) Text += "  IATIC:" + String(GetIATIC());
    //if (ThisScreenIndex == 00) Text += "  ECTIC:" + String(GetECTIC());
    //if (ThisScreenIndex == 00) Text += "  GEARIC:" + String(GetGEARIC());
    //if (ThisScreenIndex == 00) Text += "   EBCHi:" + String(GetInputEBCHi());
    //if (ThisScreenIndex == 00) Text += "   GPO1I:" + String(GetInputGPO1());
    //if (ThisScreenIndex == 00) Text += "   GPO2I:" + String(GetInputGPO2());
    //if (ThisScreenIndex == 00) Text += "   GPO3I:" + String(GetInputGPO3());
    //if (ThisScreenIndex == 00) Text += " EBCBDTY:" + String(GetEBCBaseDuty());
    //if (ThisScreenIndex == 00) Text += "  EBCDTY:" + String(GetEBCDuty());
    //if (ThisScreenIndex == 00) Text += "   GPO1O:" + String(GetOutputGPO1());
    //if (ThisScreenIndex == 00) Text += "   GPO2O:" + String(GetOutputGPO2());
    //if (ThisScreenIndex == 00) Text += "   GPO3O:" + String(GetOutputGPO3());
    //if (ThisScreenIndex == 00) Text += "   BSTS2:" + String(GetOutputBSTStage2());
    //if (ThisScreenIndex == 00) Text += "   BSTS3:" + String(GetOutputBSTStage3());
    //if (ThisScreenIndex == 00) Text += "   BSTS4:" + String(GetOutputBSTStage4());
    //if (ThisScreenIndex == 00) Text += "    LEAN:" + String(GetLeanProtect());





//###########################################################################################################
//###########################################################################################################
//###########################################################################################################
//PROTOCOL

/*void Disconnect() {
  Serial.end();
}

bool GetVTP(){
  return (bool) GetActivated(Datalog_Bytes[21], 3, false);
}

int GetIgnTable(){
  return (0.25 * Datalog_Bytes[20]) - 6;
}

int GetBaro(){
  return (int) round((double) ((int) Datalog_Bytes[3] / 2 + 24) * 7.221 - 59.0);
}

bool GetVTSM(){
  return (bool) GetActivated(Datalog_Bytes[8], 3, false);
}

float GetInjectorDuty() {
  return (float) ((double) GetRpm() * (double) GetDuration(Long2Bytes(Datalog_Bytes[17], Datalog_Bytes[18])) / 1200.0);
}

bool GetFuelCut2(){
  return (bool) GetActivated(Datalog_Bytes[8], 5, false);
}

bool GetFanCtrl(){
  return (bool) GetActivated(Datalog_Bytes[22], 4, false);
}

bool GetAtlCtrl(){
  return (bool) GetActivated(Datalog_Bytes[22], 5, false);
}

bool GetMIL(){
  return (bool) GetActivated(Datalog_Bytes[23], 5, false);
}

bool GetInputFTL(){
  return (bool) GetActivated(Datalog_Bytes[38], 0, false);
}

bool GetInputFTS(){
  return (bool) GetActivated(Datalog_Bytes[38], 1, false);
}

bool GetInputEBC(){
  return (bool) GetActivated(Datalog_Bytes[38], 2, false);
}

bool GetInputBST(){
  return (bool) GetActivated(Datalog_Bytes[38], 7, false);
}

bool GetOutputBoostCut(){
  return (bool) GetActivated(Datalog_Bytes[39], 3, false);
}

double GetInjDuration(){
  return round(((double) GetDuration((int) Long2Bytes(Datalog_Bytes[17], Datalog_Bytes[18]))) * 100) / 100;
}

bool GetLeanProtect(){
  return (bool) GetActivated(Datalog_Bytes[43], 7, false);
}

bool GetParkN(){
  return (bool) GetActivated(Datalog_Bytes[21], 0, false);
}

bool GetBKSW(){
  return (bool) GetActivated(Datalog_Bytes[21], 1, false);
}

bool GetACC(){
  return (bool) GetActivated(Datalog_Bytes[21], 2, false);
}

bool GetStart(){
  return (bool) GetActivated(Datalog_Bytes[21], 4, false);
}

bool GetSCC(){
  return (bool) GetActivated(Datalog_Bytes[21], 5, false);
}

bool GetVTSFeedBack(){
  return (bool) GetActivated(Datalog_Bytes[21], 6, false);
}

bool GetPSP(){
  return (bool) GetActivated(Datalog_Bytes[21], 7, false);
}

bool GetFuelPump(){
  return (bool) GetActivated(Datalog_Bytes[22], 0, false);
}

bool GetIAB(){
  return (bool) GetActivated(Datalog_Bytes[22], 2, false);
}

bool GetPurge(){
  return (bool) GetActivated(Datalog_Bytes[22], 6, false);
}

bool GetAC(){
  return (bool) GetActivated(Datalog_Bytes[22], 7, false);
}

bool GetO2Heater(){
  return (bool) GetActivated(Datalog_Bytes[23], 6, false);
}

bool GetVTS(){
  return (bool) GetActivated(Datalog_Bytes[23], 7, false);
}

double GetELDVolt(){
  return GetVolt(Datalog_Bytes[24]);
}

bool GetATShift1(){
  return (bool) GetActivated(Datalog_Bytes[8], 6, false);
}

bool GetATShift2(){
  return (bool) GetActivated(Datalog_Bytes[8], 7, false);
}

double GetECTFC(){
  return GetFC(Datalog_Bytes[26], 128);
}

long GetO2Short(){
  return (long) GetFC(Long2Bytes(Datalog_Bytes[27], Datalog_Bytes[28]), 32768);
}

long GetO2Long(){
  return (long) GetFC(Long2Bytes(Datalog_Bytes[29], Datalog_Bytes[30]), 32768);
}

long GetIATFC(){
  return (long) GetFC(Long2Bytes(Datalog_Bytes[31], Datalog_Bytes[32]), 32768);
}

double GetVEFC(){
  return GetFC(Datalog_Bytes[33], 128);
}

float GetIATIC(){
  return GetIC(Datalog_Bytes[34]);
}

float GetECTIC(){
  return GetIC(Datalog_Bytes[35]);
}

float GetGEARIC(){
  return GetIC(Datalog_Bytes[36]);
}

bool GetInputEBCHi(){
  return (bool) GetActivated(Datalog_Bytes[38], 3, false);
}

bool GetInputGPO1(){
  return (bool) GetActivated(Datalog_Bytes[38], 4, false);
}

bool GetInputGPO2(){
  return (bool) GetActivated(Datalog_Bytes[38], 5, false);
}

bool GetInputGPO3(){
  return (bool) GetActivated(Datalog_Bytes[38], 6, false);
}

double GetEBCBaseDuty(){
  return GetEBC(Datalog_Bytes[40]);
}

double GetEBCDuty(){
  return GetEBC(Datalog_Bytes[41]);
}

bool GetOutputGPO1(){
  return (bool) GetActivated(Datalog_Bytes[43], 0, false);
}

bool GetOutputGPO2(){
  return (bool) GetActivated(Datalog_Bytes[43], 1, false);
}

bool GetOutputGPO3(){
  return (bool) GetActivated(Datalog_Bytes[43], 2, false);
}

bool GetOutputBSTStage2(){
  return (bool) GetActivated(Datalog_Bytes[43], 3, false);
}

bool GetOutputBSTStage3(){
  return (bool) GetActivated(Datalog_Bytes[43], 4, false);
}

bool GetOutputBSTStage4(){
  return (bool) GetActivated(Datalog_Bytes[43], 5, false);
}

bool GetPostFuel(){
  return (bool) GetActivated(Datalog_Bytes[8], 0, false);
}

bool GetSCCChecker(){
  return (bool) GetActivated(Datalog_Bytes[8], 1, false);
}

float GetIC(byte ThisByte) {
  if ((int) ThisByte == 128)
    return 0.0f;
  if ((int) ThisByte < 128)
    return (float) (128 - (int) ThisByte) * -0.25f;
  return (float) ((int) ThisByte - 128) * 0.25f;
}

double GetFC(long ThisByte, long ThisLong) {
  double num = (double) ThisByte / (double) ThisLong;
  //if (CorrectionUnits == "multi")
    return round((num) * 100) / 100;
  //return round(num * 100.0 - 100.0);
}

double GetEBC(byte ThisByte) {
  double num = (double) ThisByte / 2.0;
  if (num > 100.0)
    num = 100.0;
  return round((num * 10)) / 10;
}*/
