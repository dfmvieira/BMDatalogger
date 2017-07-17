void Screen(){
  lcd.begin(20, 4);
  lcd.clear();
  ResetBufferIndex();
  GetInfosString(20);
  PrintText(20, 4, 0);
  
  delay(800);
  
  ResetBufferIndex();
  Add_String(VersionStr);
  writeBigString(4, 1);

  delay(800);
  
  ResetBufferIndex();
  GetInfosString(21);
  PrintText(20, 3, 3);

  delay(1500);
  lcd.clear();
}
