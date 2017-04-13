double TimeVal = 99.99;
double BestTimeVal = 99.99;
unsigned long last_zero_time=0;
bool CheckDone = false;

void SetSpeedTime() {
  int Speed = GetVss();
  if (UseKMH == 0) Speed = Speed * 1.6;
  
  if (Speed == 0) {
    TimeVal = 99.99;
    last_zero_time = millis();
    CheckDone = false;
  }
  if (Speed > 0 && Speed < 100 && !CheckDone) TimeVal = (double)(((long) millis() - (long) last_zero_time)) / 1000;
  if (Speed >= 100 && !CheckDone) {
    if (TimeVal < BestTimeVal) BestTimeVal = TimeVal;
    CheckDone = true;
  }
}

double GetSpeedTime() {
  return TimeVal;
}

double GetBestSpeedTime() {
  return BestTimeVal;
}

