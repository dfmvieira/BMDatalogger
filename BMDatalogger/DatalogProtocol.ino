const int Array_Size    = 52;
byte Datalog_Bytes[Array_Size];

void Connect() {
  Serial.begin(38400);
}

bool GetJ12Cut() {
  bool J12_Cut = false;
  Serial.write((byte) 16);
  if ((int) Serial.read() == 205) J12_Cut = true;
  return J12_Cut;
}

void GetData(){
  while(Serial.available())
    for (int i = 0; i < Array_Size; i++)
      Datalog_Bytes[i] = Serial.read();
      
  Serial.flush();
  Serial.write(" ");

  //FakeValue += 1;
  //if (FakeValue >= 180) FakeValue = 0;
}

bool ResetMil() {
  bool MilResetted = false;
  Serial.write((byte) 80);
  delay(500);
  if ((int) Serial.read() == 80) MilResetted = true;
  return MilResetted;
}

void GetMil() {
  int Displayed = 0;
  for (int i = 1; i <= 8; i++) {
    if (Displayed < 4) {
      if (GetActivated(Datalog_Bytes[12], i - 1, false) == 1) {
        ResetBufferIndex();
        GetErrorString(FixMil(i));
        DisplayMil(Displayed);
        Displayed++;
      }
    }
  }
  for (int j = 1; j <= 8; j++) {
    if (Displayed < 4) {
      if (GetActivated(Datalog_Bytes[13], j - 1, false) == 1) {
        ResetBufferIndex();
        GetErrorString(FixMil(j + 8));
        DisplayMil(Displayed);
        Displayed++;
      }
    }
  }
  for (int k = 1; k <= 8; k++) {
    if (Displayed < 4) {
      if (GetActivated(Datalog_Bytes[14], k - 1, false) == 1) {
        ResetBufferIndex();
        GetErrorString(FixMil((k + 8) + 8));
        DisplayMil(Displayed);
        Displayed++;
      }
    }
  }
  for (int m = 1; m <= 8; m++) {
    if (Displayed < 4) {
      if (GetActivated(Datalog_Bytes[15], m - 1, false) == 1) {
        ResetBufferIndex();
        GetErrorString(FixMil(((m + 8) + 8) + 8));
        DisplayMil(Displayed);
        Displayed++;
      }
    }
  }

  if (Displayed == 0) {
    ResetBufferIndex();
    GetInfosString(10);
    writeBigString(0, 2);
  }
}

int FixMil(int Value) {
  switch (Value) {
      case 0x18:
          return 30;
      case 0x19:
          return 0x1f;
      case 0x1a:
          return 0x24;
      case 0x1b:
          return 0x29;
      case 0x1c:
          return 0x2b;
  }
  //if (Value >= 0x18) return 0;
  return Value;
}

long Long2Bytes(const byte ThisByte1, const byte ThisByte2) {
  return (long) ((long) ThisByte2 * 256 + (long) ThisByte1);
}

float GetTemperature(const byte ThisByte) {
  float ThisTemp = (float) ThisByte / 51;
  ThisTemp = (0.1423*pow(ThisTemp,6)) - (2.4938*pow(ThisTemp,5))  + (17.837*pow(ThisTemp,4)) - (68.698*pow(ThisTemp,3)) + (154.69*pow(ThisTemp,2)) - (232.75*ThisTemp) + 284.24;
  ThisTemp = ((ThisTemp - 32)*5)/9;

  if (UseCelcius == 0)
    ThisTemp = ThisTemp * 1.8 + 32.0;
  
  return ThisTemp;
}

double GetVolt(const byte ThisByte) {
  return (double) ThisByte * 0.0196078438311815;
}

float GetDuration(const int ThisInt) {
  return (float) ThisInt * 3.20000004768372 / 1000.0;
}

byte GetActivated(byte ThisByte, const int ThisPos, const bool Reversed) {
  int bitArray[8];
  for (int i=0; i < 8; ++i ) {
    bitArray[i] = ThisByte & 1;
    ThisByte = ThisByte >> 1;
  }

  if (Reversed)
    return bitArray[ThisPos] ? (byte) 0 : (byte) 1;
  return bitArray[ThisPos] ? (byte) 1 : (byte) 0;
}

float GetInstantConsumption(){
  if (GetVssKMH() == 0) return 0;
  //float hundredkm = ((60 / GetVssKMH()) * 100) / 60;     //minutes needed to travel 100km
  float hundredkm = (60 / GetVssKMH()) * 100;     //minutes needed to travel 100km
  float fuelc = (hundredkm * ((Injectors_Size / 100) * GetDuty())) / 1000;     
  return constrain(fuelc, 0.0, 50.0);
}

float GetDuty(){
  return ((float) GetRpm() * (float) GetInj()) / 1200;
}

int GetEct(){
  return constrain(GetTemperature(Datalog_Bytes[0]), -40, 140);
}

int GetIat(){
  return constrain(GetTemperature(Datalog_Bytes[1]), -40, 140);                  
}

double GetO2(){
  byte WBByte = 0;
  if (O2Input == 0) WBByte = Datalog_Bytes[2];
  if (O2Input == 1) WBByte = Datalog_Bytes[24];
  if (O2Input == 2) WBByte = Datalog_Bytes[44];
  if (O2Input == 3) WBByte = Datalog_Bytes[45];
  double RTND = 0.0;
  if (O2Type == 0) RTND = constrain((double) InterpolateWB(GetVolt(WBByte)) * 14.7, 10, 20);
  if (O2Type == 1) RTND = constrain((double) InterpolateWB(GetVolt(WBByte)), 0, 5);
  if (O2Type == 2) RTND = constrain((double) GetVolt(WBByte), 0, 16);

  //return RoundThis(1, RTND);
  return RTND;
}

double InterpolateWB(double ThisDouble) {
  if (ThisDouble < WBConversion[0]) return WBConversion[1];
  if (ThisDouble > WBConversion[2]) return WBConversion[3];
  return (WBConversion[1] + (((ThisDouble - WBConversion[0]) * (WBConversion[3] - WBConversion[1])) / (WBConversion[2] - WBConversion[0])));
}

int GetMBar() {
  long Value = (long) Datalog_Bytes[4];
  long MapLow = (MapByte[1] * 256) + MapByte[0];
  long MapHigh = (MapByte[3] * 256) + MapByte[2];
                
  return (int) ((((Value * (MapHigh - MapLow)) / 255) + MapLow) - 32768);
}

int GetMap(){
  int mBar = GetMBar();
  if (MapValue == 0) return constrain(mBar, 0, 1048);
  else if (MapValue == 1) {
    if (mBar <= 1013) return 0;
    else return constrain((int) ((float) (mBar - 1013) * 0.01450377), 0, 40); //GetValuePSI(ThisInt);
  }
  else if (MapValue == 2) return constrain((int) round((double) mBar * 0.1), 0, 105); //GetValueKPa(ThisInt);
  else return 0;
}

double GetBoost(){
  int ThisInt = GetMBar();
  if (ThisInt <= 1013) return 0;
  else return ((double) (ThisInt - 1013) * 0.0145037695765495);
}

unsigned int GetTps(){
  return constrain((int) round(((double) Datalog_Bytes[5] - 25.0) / 2.04), 0, 100);
  //return constrain((0.4716  * Datalog_Bytes[5]) - 11.3184, 0, 100);    
}

unsigned int GetRpm(){
  //return (int) (1875000/Long2Bytes(Datalog_Bytes[6], Datalog_Bytes[7]));  //unused
  
  int rpm = (int) (1851562/Long2Bytes(Datalog_Bytes[6], Datalog_Bytes[7]));
  return constrain(rpm, 0, 11000);
}

bool GetIgnCut(){
  return (bool) GetActivated(Datalog_Bytes[8], 2, false);
}

bool GetFuelCut1(){
  return (bool) GetActivated(Datalog_Bytes[8], 4, false);
}

unsigned int GetVss(){
  if (UseKMH == 1) return (int) Datalog_Bytes[16];
  return (int) round((float) Datalog_Bytes[16] / 1.6f);
}

unsigned int GetVssKMH(){
  return (int) Datalog_Bytes[16];
}

double GetInjFV() {
    return (double) Long2Bytes(Datalog_Bytes[17], Datalog_Bytes[18]) / 4.0;
}

int GetInj(){
  return (int) (Long2Bytes(Datalog_Bytes[17], Datalog_Bytes[18]) / 352);  
}

int GetIgn(){
  return constrain((0.25 * Datalog_Bytes[19]) - 6, -6, 60);
}

float GetBattery(){  
  return constrain((26.0 * Datalog_Bytes[25]) / 270.0, 0, 18);
}

bool GetOutput2ndMap(){
  return (bool) GetActivated(Datalog_Bytes[39], 5, false);
}

int GetIACVDuty(){
  return constrain(((int) ((float) Long2Bytes(Datalog_Bytes[49], Datalog_Bytes[50]) / 32768) * 100.0 - 100.0), -100, 100);
}

double GetMapVolt(){
  return constrain(GetVolt(Datalog_Bytes[4]), 0, 5);
}

double GetTPSVolt(){
  return constrain(GetVolt(Datalog_Bytes[5]), 0, 5);
}

//###############################

bool GetOutputFanCtrl(){
  return (bool) GetActivated(Datalog_Bytes[39], 6, false);
}

bool GetVTS(){
  return (bool) GetActivated(Datalog_Bytes[23], 7, false);
}

bool GetVTP(){
  return (bool) GetActivated(Datalog_Bytes[21], 3, false);
}

double GetELDVolt(){
  return GetVolt(Datalog_Bytes[24]);
}

bool GetO2Heater(){
  return (bool) GetActivated(Datalog_Bytes[23], 6, false);
}

bool GetAC(){
  return (bool) GetActivated(Datalog_Bytes[22], 7, false);
}

bool GetAtlCtrl(){
  return (bool) GetActivated(Datalog_Bytes[22], 5, false);
}
