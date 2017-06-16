bool IsWarning = false;

void GetWarnings() {
  bool Warning = false;
  if (GetRpm() > Warning_RPM) Warning = true;
  if (GetIat() > Warning_IAT) Warning = true;
  if (GetEct() > Warning_ECT) Warning = true;

  //Disable (not warning)
  if (!Warning && IsWarning) {
    lcd.setBacklight(255);
    IsWarning = false;
  }

  //Warning (Trigger Flash)
  if (Warning) {
    if (!IsWarning) {
      lcd.setBacklight(0);
      IsWarning = true;
    }
    else {
      lcd.setBacklight(255);
      IsWarning = false;
    }
  }
}

