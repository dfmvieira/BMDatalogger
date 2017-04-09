bool J12_Cut            = true;
const int Array_Size    = 52;
byte Datalog_Bytes[Array_Size];

//###########################################################################################################
//###########################################################################################################
//###########################################################################################################

void Connect() {
  Serial.begin(38400);
}

bool GetJ12Cut() {
  J12_Cut = false;
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
}

long Long2Bytes(byte ThisByte1, byte ThisByte2) {
  return (long) ((long) ThisByte2 * 256 + (long) ThisByte1);
}

float GetTemperature(byte ThisByte) {
  float ThisTemp = (float) ThisByte / 51;
  ThisTemp = (0.1423*pow(ThisTemp,6)) - (2.4938*pow(ThisTemp,5))  + (17.837*pow(ThisTemp,4)) - (68.698*pow(ThisTemp,3)) + (154.69*pow(ThisTemp,2)) - (232.75*ThisTemp) + 284.24;
  ThisTemp = ((ThisTemp - 32)*5)/9;

  if (UseCelcius == 0)
    ThisTemp = ThisTemp * 1.8 + 32.0;
  
  return ThisTemp;
  /*if (UseCelcius)
    return round(double_Temperature[(int) ThisByte]);
  return round(GetTemperatureF(double_Temperature[(int) ThisByte]));*/
}

double GetVolt(byte ThisByte) {
  return round(((double) ThisByte * 0.0196078438311815) * 100) / 100;
}

float GetDuration(int ThisInt) {
  return (float) ThisInt * 3.20000004768372 / 1000.0;
}

byte GetActivated(byte ThisByte, int ThisPos, bool Reversed) {
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
  float hundredkm = ((60 / GetVss()) * 100) / 60;     //minutes needed to travel 100km
  float fuelc = (hundredkm * ((Injectors_Size / 100) * GetDuty())) / 1000;     
  return constrain(fuelc, 0.0, 50.0);
}

float GetDuty(){
  return ((float) GetRpm() * (float) GetInj()) / 1200;
}

float GetValueHG(int ThisInt) {
  return (float) round(((double) ThisInt * 0.02952999) * 10) / 10;
}

int GetEct(){
  return GetTemperature(Datalog_Bytes[0]);
}

int GetIat(){
  return GetTemperature(Datalog_Bytes[1]);                  
}

double GetO2(){
  //if (O2Input == 0) return round((float) GetVolt(Datalog_Bytes[2]) * 10) / 10;//O2Byte = Datalog_Bytes[2];
  //if (O2Input == 1) return round((float) GetVolt(Datalog_Bytes[24]) * 10) / 10;//O2Byte = Datalog_Bytes[24];
  //if (O2Input == 2) return round((float) GetVolt(Datalog_Bytes[44]) * 10) / 10;//O2Byte = Datalog_Bytes[44];   //byte_25
  //if (O2Input == 3) return round((float) GetVolt(Datalog_Bytes[45]) * 10) / 10;//O2Byte = Datalog_Bytes[45]; 
  //return round((float) GetVolt(O2Byte) * 100) / 100;
  //return ((2 * (float) O2Byte[2]) + 10) / 10f;

  //New Extracted method
  byte WBByte = 0;
  if (O2Input == 0) WBByte = Datalog_Bytes[2];
  if (O2Input == 1) WBByte = Datalog_Bytes[24];
  if (O2Input == 2) WBByte = Datalog_Bytes[44];
  if (O2Input == 3) WBByte = Datalog_Bytes[45];
  double RTND = 0.0;
  if (UseLAMBA == 1) RTND = round((double) InterpolateWB(GetVolt(WBByte) * 10) / 10);
  else RTND = round((double) InterpolateWB(GetVolt(WBByte) * 14.75 * 10) / 10);
  return RTND;
}

double InterpolateWB(double ThisDouble) {
  int index = sizeof(WBConversion) - 1;
  double RTN = 0.0;
  if (ThisDouble < WBConversion[0]) RTN = WBConversion[1];
  if (ThisDouble > WBConversion[index - 1]) RTN = WBConversion[index];
  for (int i = 0; i < (sizeof(WBConversion) / 2); i++)
  {
      index = 2 * i;
      if ((ThisDouble >= WBConversion[index]) && (ThisDouble <= WBConversion[index + 2])) 
          RTN = (WBConversion[index + 1] + (((ThisDouble - WBConversion[index]) * (WBConversion[index + 3] - WBConversion[index + 1])) / (WBConversion[index + 2] - WBConversion[index])));
  }

  return RTN;
}

float GetMap(){
  int ThisInt = round((double) (((int) Datalog_Bytes[4] * 7.221) - 59.0));
  if (MapValue == 0) return (int) ThisInt;
  else if (MapValue == 1) return (ThisInt / 1000);
  else if (MapValue == 2) return GetValueHG(ThisInt);
  else if (MapValue == 3) {
    if (ThisInt <= 1013) return 0;
    else return (float) round(((double) (ThisInt - 1013) * 0.0145037695765495) * 10) / 10; //GetValuePSI(ThisInt);
  }
  else if (MapValue == 4) return (int) round((double) ThisInt * 0.1); //GetValueKPa(ThisInt);
  else return 0;

  //int ThisInt = (int) Datalog_Bytes[4];
  //if (MapValue == 0) return ((float) ThisInt * 2041) / 255;  //(1764/255) * (float) ThisInt;
  //if (MapValue == 0) return (int) 6.9176 * (float) ThisInt;
  //float mapRaw = Datalog_Bytes[4];
  //return (1764/255)*mapRaw;
}

unsigned int GetTps(){
  return constrain((int) round(((double) Datalog_Bytes[5] - 25.0) / 2.04), 0, 100);
  //return constrain((0.4716  * Datalog_Bytes[5]) - 11.3184, 0, 100);    
}

unsigned int GetRpm(){
  //return (int) (1875000/Long2Bytes(Datalog_Bytes[6], Datalog_Bytes[7]));
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
  if (UseKMH == 1)
    return (int) Datalog_Bytes[16];
  return (int) round((float) Datalog_Bytes[16] / 1.6f);
}

double GetInjFV() {
    return round(((double) Long2Bytes(Datalog_Bytes[17], Datalog_Bytes[18]) / 4.0) * 10) / 10;
}

int GetInj(){
  return (int) (Long2Bytes(Datalog_Bytes[17], Datalog_Bytes[18]) / 352);  
}

int GetIgn(){
  return constrain((0.25 * Datalog_Bytes[19]) - 6, -6, 60);
}

float GetBattery(){  
  return (26.0 * Datalog_Bytes[25]) / 270.0;
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

bool GetOutput2ndMap(){
  return (bool) GetActivated(Datalog_Bytes[39], 5, false);
}

bool GetOutputFanCtrl(){
  return (bool) GetActivated(Datalog_Bytes[39], 6, false);
}

bool GetOutputBST(){
  return (bool) GetActivated(Datalog_Bytes[39], 7, false);
}

double GetIACVDuty(){
  return ((double) ((float) Long2Bytes(Datalog_Bytes[49], Datalog_Bytes[50]) / 32768) * 100.0 - 100.0);
}

double GetMapVolt(){
  return GetVolt(Datalog_Bytes[4]);
}

double GetTPSVolt(){
  return GetVolt(Datalog_Bytes[5]);
}

unsigned int GetGear(){ 
  if (GetVss() == 0)
    return 0;
    
  byte Gear = 0;
  for (int i = 0; i < 4; i++) {
    if (((int) (GetVss() * 256) * (int) GetRpm() / (int) 256) >= Tranny[i * 2]) Gear = i + 1;
    else break;
  }

  return Gear;
}
