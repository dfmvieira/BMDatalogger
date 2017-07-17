/*void ScreenJ12() {
  unsigned long current_time = millis();
  if (current_time - last_datalog_time > Timeout) {
    EcuConnected = GetJ12Cut();
    last_datalog_time = current_time;
  }
  
  if (!EcuConnected) {
    ResetBufferIndex();
    GetInfosString(14);
    writeBigString(2, 1);
  }else {
    ShowMenu();
  }
}*/

