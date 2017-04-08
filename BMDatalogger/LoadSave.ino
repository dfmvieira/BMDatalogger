void SaveOptions() {
  for (int i=0; i < 9; i++) {
    int Addr = i * 10;
    if (i == 0) EEPROM.put(Addr, Timeout);
    if (i == 1) EEPROM.put(Addr, Injectors_Size);
    if (i == 2) EEPROM.put(Addr, mBarSeaLevel);
    if (i == 3) EEPROM.put(Addr, TrannyType);
    if (i == 4) EEPROM.put(Addr, O2Input);
    if (i == 5) EEPROM.put(Addr, MapValue);
    if (i == 6) EEPROM.put(Addr, UseCelcius);
    if (i == 7) EEPROM.put(Addr, UseKMH);
    if (i == 8) EEPROM.put(Addr, ScreenIndex);
    if (i == 9) EEPROM.put(Addr, UseLAMBA);
    if (i == 10) EEPROM.put(Addr, WBType);

    //Write 3 at the last location to tell data ever get saved
    EEPROM.write(1023, 3);
  }
}

void LoadOptions() {
  if (EEPROM.read(1023) == 3) {
    for (int i=0; i < 9; i++) {
      int Addr = i * 10;
      if (i == 0) EEPROM.get(Addr, Timeout);
      if (i == 1) EEPROM.get(Addr, Injectors_Size);
      if (i == 2) EEPROM.get(Addr, mBarSeaLevel);
      if (i == 3) EEPROM.get(Addr, TrannyType);
      if (i == 4) EEPROM.get(Addr, O2Input);
      if (i == 5) EEPROM.get(Addr, MapValue);
      if (i == 6) EEPROM.get(Addr, UseCelcius);
      if (i == 7) EEPROM.get(Addr, UseKMH);
      if (i == 8) EEPROM.get(Addr, ScreenIndex);
      if (i == 9) EEPROM.get(Addr, UseLAMBA);
      if (i == 10) EEPROM.get(Addr, WBType);
    }
  }
  else
    SaveOptions();
}
