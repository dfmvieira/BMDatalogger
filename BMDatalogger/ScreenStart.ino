void Screen(){
  lcd.begin(20, 4);
  lcd.clear();
  ResetBufferIndex();
  Add_String(VersionStr);
  writeBigString(4, 1);

  delay(2000);
  lcd.clear();
}
