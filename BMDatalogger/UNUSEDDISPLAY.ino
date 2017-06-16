//###########################################################################################################
//###########################################################################################################
//###########################################################################################################
//PROTOCOL


/*const byte Tranny[4] = {70,103,142,184};
unsigned int GetGear(){
  if (GetVssKMH() == 0 | GetRpm() == 0) return 0;
  
  long num = (((long) GetVssKMH() * 256) * (long) GetRpm()) / 65535;
  for (int i = 0; i < 4; i++) if (num < (long) Tranny[i]) return i + 1;
  return 5;
}*/

/*void Disconnect() {
  Serial.end();
}

bool GetOutputBST(){
  return (bool) GetActivated(Datalog_Bytes[39], 7, false);
}

bool GetOutputFTL(){
  return (bool) GetActivated(Datalog_Bytes[39], 0, false);
}

bool GetOutputAntilag(){
  return (bool) GetActivated(Datalog_Bytes[39], 1, false);
}

bool GetOutputFTS(){
  return (bool) GetActivated(Datalog_Bytes[39], 2, false);
}

bool GetOutputEBC(){
  return (bool) GetActivated(Datalog_Bytes[39], 4, false);
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
