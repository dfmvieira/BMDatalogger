void StartScreen(){
  String T1 = " BMDatalogger" + VersionStr;
  String T2 = "  Made by BM Devs   ";

  lcd.clear();
  render_big_msg("HONDA",0,0);
  delay(1000);
  lcd.setCursor(0,2);
  lcd.print(T1);
  lcd.setCursor(0,3);
  lcd.print(T2);
  delay(2000);
}
