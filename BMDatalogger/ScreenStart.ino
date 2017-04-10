void StartScreen(){
  /*String T1 = "BMDatalogger " + VersionStr + " ";
  String T2 = "   eCtune ISR V3    ";
  String T3 = "  Datalog Protocol  ";
  String T4 = "  Made by BM Devs   ";

  lcd.clear();
  //render_big_msg("HONDA",0,0);
  writeBigString("HONDA", 0, 0);
  lcd.setCursor(0,2);
  lcd.print(T1);
  lcd.setCursor(0,3);
  lcd.print(T2);
  delay(2000);*/

  lcd.clear();
  writeBigString("BMDEV", 0, 0);
  //lcd.setCursor(0,0);
  //lcd.print("BMDatalogger " + VersionStr + " ");
  //delay(1000);
  //lcd.setCursor(0,1);
  //lcd.print("   eCtune ISR V3    ");
  delay(1000);
  lcd.setCursor(0,2);
  lcd.print(" Datalogger " + VersionStr + "  ");
  //lcd.print("  Datalog Protocol  ");
  delay(1000);
  lcd.setCursor(0,3);
  lcd.print("  Made for eCtune   ");
  //lcd.print("  Made by BM Devs   ");
  delay(2000);
}
