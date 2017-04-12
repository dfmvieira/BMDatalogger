double TimeVal = 99.99;
double BestTimeVal = 99.99;
unsigned long last_zero_time=0;
bool CheckDone = false;

void SetSpeedTime() {
  int Speed = GetVss();
  if (UseKMH == 0) Speed = (int) round((double) Datalog_Bytes[16] * 1.6);
  
  if (Speed == 0) {
    TimeVal = 99.99;
    last_zero_time = millis();
    CheckDone = false;
  }
  if (Speed > 0 && Speed < 100) TimeVal = (double) (millis() - last_zero_time);
  if (Speed >= 100) {
    if (!CheckDone) {
      if (TimeVal < BestTimeVal) BestTimeVal = TimeVal;
      CheckDone = true;
    }
  }
}

double GetSpeedTime() {
  return TimeVal;
}

double GetBestSpeedTime() {
  return BestTimeVal;
}

