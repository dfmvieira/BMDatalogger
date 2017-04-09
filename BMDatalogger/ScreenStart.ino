void StartScreen(){
  String T1 = "BMDatalogger " + VersionStr;
  String T2 = "   eCtune ISR V3    " + VersionStr;
  String T3 = "  Datalog Protocol  ";
  String T4 = "  Made by BM Devs   ";

  lcd.clear();
  //render_big_msg("HONDA",0,0);
  /*writeBigString("HONDA", 0, 0);
  lcd.setCursor(0,2);
  lcd.print(T1);
  lcd.setCursor(0,3);
  lcd.print(T2);
  delay(2000);*/
  
  lcd.setCursor(0,0);
  lcd.print(T1);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(T2);
  delay(1000);
  lcd.setCursor(0,2);
  lcd.print(T3);
  delay(1000);
  lcd.setCursor(0,3);
  lcd.print(T4);
  delay(2000);
}
