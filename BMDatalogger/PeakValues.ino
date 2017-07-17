int PeakValuesMin[MaxDataValue];
int PeakValuesMax[MaxDataValue];
int PeakMinValue = 0;
int PeakMaxValue = 1;
byte PeakInitialized = 0;

void InitPeak() {
  for (int i=0; i < MaxDataValue; i++) {
    ThisScreenIndex = i;
    int Value = GetInt();
    PeakValuesMin[i] = Value;
    PeakValuesMax[i] = Value;
  }
  PeakInitialized = 1;
}

void SetPeakValue(const int minValue, const int maxValue) {
  if (PeakInitialized == 0) InitPeak();
  PeakMinValue = minValue;
  PeakMaxValue = maxValue;
}

void ApplyPeak() {
  for (int i=0; i < MaxDataValue; i++) {
    ThisScreenIndex = i;
    SetPeak();
    int ThisValue = GetInt();
    if (ThisValue < PeakValuesMin[ThisScreenIndex]) PeakValuesMin[ThisScreenIndex] = ThisValue;
    if (ThisValue > PeakValuesMax[ThisScreenIndex]) PeakValuesMax[ThisScreenIndex] = ThisValue;
  }
}

void SetPeak() {
  if (ThisScreenIndex == 0) SetPeakValue(0,11000);
  if (ThisScreenIndex == 1) SetPeakValue(TempMin, TempMax);
  if (ThisScreenIndex == 1) SetPeakValue(TempMin, TempMax);
  if (ThisScreenIndex == 3) SetPeakValue(0,100);
  if (ThisScreenIndex == 4) SetPeakValue(10,20);
  if (ThisScreenIndex == 5) SetPeakValue(-6,60);
  if (ThisScreenIndex == 6) SetPeakValue(0,20);
  if (ThisScreenIndex == 7) SetPeakValue(0,50);
  if (ThisScreenIndex == 8) SetPeakValue(-100,100);
  if (ThisScreenIndex == 9) SetPeakValue(mBarMin, mBarMax);
  if (ThisScreenIndex == 10) SetPeakValue(0,40);
  if (ThisScreenIndex == 11) SetPeakValue(0,300);
  if (ThisScreenIndex == 12) SetPeakValue(0,1);
  if (ThisScreenIndex == 13) SetPeakValue(0,18);
  if (ThisScreenIndex == 14) SetPeakValue(0,1);
  if (ThisScreenIndex == 15) SetPeakValue(0,1);
  if (ThisScreenIndex == 16) SetPeakValue(0,3000);
  if (ThisScreenIndex == 17) SetPeakValue(0,1);
  if (ThisScreenIndex == 18) SetPeakValue(2,18);
  if (ThisScreenIndex == 19) SetPeakValue(2,18);
  if (ThisScreenIndex == 20) SetPeakValue(0,1);
  if (ThisScreenIndex == 21) SetPeakValue(0,1);
  if (ThisScreenIndex == 22) SetPeakValue(0,18);
  if (ThisScreenIndex == 23) SetPeakValue(0,1);
  if (ThisScreenIndex == 24) SetPeakValue(0,1);
  if (ThisScreenIndex == 25) SetPeakValue(0,1);
  if (ThisScreenIndex == 26) SetPeakValue(0,5);
  
  if (ThisScreenIndex == 27) SetPeakValue(0,1);
  if (ThisScreenIndex == 28) SetPeakValue(0,1);
  if (ThisScreenIndex == 29) SetPeakValue(0,1);
  if (ThisScreenIndex == 30) SetPeakValue(0,1);
  if (ThisScreenIndex == 31) SetPeakValue(0,1);
  if (ThisScreenIndex == 32) SetPeakValue(0,1);
  if (ThisScreenIndex == 33) SetPeakValue(0,1);
  if (ThisScreenIndex == 34) SetPeakValue(0,1);
  if (ThisScreenIndex == 35) SetPeakValue(0,1);
  if (ThisScreenIndex == 36) SetPeakValue(0,1);
  if (ThisScreenIndex == 37) SetPeakValue(0,1);
  if (ThisScreenIndex == 38) SetPeakValue(0,1);
  if (ThisScreenIndex == 39) SetPeakValue(0,1);
  if (ThisScreenIndex == 40) SetPeakValue(0,1);
  if (ThisScreenIndex == 41) SetPeakValue(0,1);
  if (ThisScreenIndex == 42) SetPeakValue(0,1);
  if (ThisScreenIndex == 43) SetPeakValue(0,1);
  if (ThisScreenIndex == 44) SetPeakValue(0,1);
  if (ThisScreenIndex == 45) SetPeakValue(0,1);
  if (ThisScreenIndex == 46) SetPeakValue(0,1);
  if (ThisScreenIndex == 47) SetPeakValue(0,1);
  if (ThisScreenIndex == 48) SetPeakValue(0,1);
  if (ThisScreenIndex == 49) SetPeakValue(0,1);
}

double GetPeakPercent(int value) {
  SetPeak();
  if (value < PeakMinValue) return 0.0;
  if (value > PeakMaxValue) return 100.0;
  return map((double) value, (double) PeakMinValue, (double) PeakMaxValue, (double) 0, (double) 100);
}

int GetPeakMin() {
  return PeakValuesMin[ThisScreenIndex];
}

int GetPeakMax() {
  return PeakValuesMax[ThisScreenIndex];
}

