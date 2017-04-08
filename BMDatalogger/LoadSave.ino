void SaveOptions() {
  EEPROM.put(0, Timeout);
  EEPROM.put(5, Injectors_Size);
  EEPROM.put(10, mBarSeaLevel);
  EEPROM.put(15, TrannyType);
  EEPROM.put(16, O2Input);
  EEPROM.put(17, MapValue);
  EEPROM.put(18, UseCelcius);
  EEPROM.put(19, UseKMH);
  EEPROM.put(20, UseLAMBA);
  EEPROM.put(21, WBType);
  
  EEPROM.put(100, ScreenIndex);

  //Write 4 at the last location to tell data ever get saved
  EEPROM.write(1023, 4);
}

void LoadOptions() {
  if (EEPROM.read(1023) == 4) {
    EEPROM.get(0, Timeout);
    EEPROM.get(5, Injectors_Size);
    EEPROM.get(10, mBarSeaLevel);
    EEPROM.get(15, TrannyType);
    EEPROM.get(16, O2Input);
    EEPROM.get(17, MapValue);
    EEPROM.get(18, UseCelcius);
    EEPROM.get(19, UseKMH);
    EEPROM.get(20, UseLAMBA);
    EEPROM.get(21, WBType);

    
    EEPROM.get(100, ScreenIndex);
  }
  else
    SaveOptions();
}
