void SetJ12Screen() {
    //Get States
    EcuConnected = GetJ12Cut();
    GetButtonStates();

    //Doesnt show if the ecu get connected on first startup
    if (!EcuConnected) {
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("    NOT CONNECTED");
      lcd.setCursor(0,2);
      lcd.print("   IS J12 INPLACE?");
      lcd.setCursor(0,3);
      lcd.print("                ");
    }
}

