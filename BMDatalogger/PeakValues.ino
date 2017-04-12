int PeakValuesMin[17];
int PeakValuesMax[17];
byte PeakInitialized = 0;

void InitPeak() {
  for (int i=0; i < sizeof(PeakValuesMin); i++) {
    ThisScreenIndex = i;
    PeakValuesMin[ThisScreenIndex] = GetInt();
    PeakValuesMax[ThisScreenIndex] = GetInt();
  }
  PeakInitialized = 1;
}

void SetPeakValue(const int minValue, const int maxValue) {
  if (PeakInitialized == 0) InitPeak();
  if (PeakInitialized == 1) {
    PeakMinValue = minValue;
    PeakMaxValue = maxValue;
  }
}

void ApplyPeak() {
  for (int i=0; i < sizeof(PeakValuesMin); i++) {
    int ThisValue = GetInt();
    if (ThisValue < PeakMinValue) PeakValuesMin[ThisScreenIndex] = ThisValue;
    if (ThisValue > PeakMaxValue) PeakValuesMax[ThisScreenIndex] = ThisValue;
  }
}

int GetPeakMin() {
  return PeakValuesMin[ThisScreenIndex];
}

int GetPeakMax() {
  return PeakValuesMax[ThisScreenIndex];
}

