void StartScreen(){
  String T1 = "BMDatalogger " + VersionStr + " ";
  String T2 = "   eCtune ISR V3    ";
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
  //delay(2000);
  delay(1000);
  if (!GetJ12Cut()) {
    T1 += "    NOT CONNECTED   ";
    T2 += "   IS J12 INPLACE?  ";
    T4 += "    PUSH TO START   "; 
  }
  else 
  {
    T1 += "     CONNECTED      ";
    T2 += "                    ";
    T4 += "    WAIT TO START   "; 
  }
  T3 += "                    ";
  delay(1000);

  //Display Scroll (20px)
  for (int i=0; i<20; i++) {
    T1.remove(0, 1);
    T2.remove(0, 1);
    T3.remove(0, 1);
    T4.remove(0, 1);
    T1 += " ";
    T2 += " ";
    T3 += " ";
    T4 += " ";
    lcd.setCursor(0,0);
    lcd.print(T1);
    lcd.setCursor(0,1);
    lcd.print(T2);
    lcd.setCursor(0,2);
    lcd.print(T3);
    lcd.setCursor(0,3);
    lcd.print(T4);
    delay(75);
  }
}
