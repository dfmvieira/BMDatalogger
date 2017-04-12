void Screen(bool J12){
  if (J12) EcuConnected = GetJ12Cut();
  if ((J12 && !EcuConnected) | !J12) {
    lcd.setCursor(0,0);
    ResetBufferIndex(true);
    if (!J12) {
      GetStringAt(true, 0, false);
      Add_String(true, VersionStr);
    }
    if (J12) GetStringAt(true, 4, false);
    lcd.print(StringBufferLong);
    if (!J12) delay(1000);
  
    lcd.setCursor(0,1);
    ResetBufferIndex(true);
    if (!J12) GetStringAt(true, 1, false);
    if (J12) GetStringAt(true, 5, false);
    lcd.print(StringBufferLong);
    if (!J12) delay(1000);
  
    lcd.setCursor(0,2); 
    ResetBufferIndex(true);
    if (!J12) GetStringAt(true, 2, false);
    lcd.print(StringBufferLong);
    if (!J12) delay(1000);
  
    lcd.setCursor(0,3);
    ResetBufferIndex(true);
    if (!J12) GetStringAt(true, 3, false);
    if (J12) GetStringAt(true, 6, false);
    lcd.print(StringBufferLong);
    if (!J12) delay(2000);
  }
}
