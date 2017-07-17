void ScreenMain(){
  ResetBufferIndex();
  GetInfosString(6);
  writeBigString(3, 0);
  
  ResetBufferIndex();
  GetInfosString(7);
  PrintText(9, 1, 2);

  ResetBufferIndex();
  GetInfosString(8);
  PrintText(9, 11, 2);
  
  ResetBufferIndex();
  GetInfosString(9);
  PrintText(9, 1, 3);

  ResetBufferIndex();
  GetInfosString(22);
  PrintText(9, 11, 3);

  //Set Indicator
  StringBuffer[0] = '>';
  if (ScreenCurrentMenu == 0) PrintText(1, 0, 2);
  if (ScreenCurrentMenu == 1) PrintText(1, 10, 2);
  if (ScreenCurrentMenu == 2) PrintText(1, 0, 3);
  if (ScreenCurrentMenu == 3) PrintText(1, 10, 3);

  //Reset empty selection
  ResetBufferIndex();
  if (ScreenCurrentMenu == 0) {
    //PrintText(1, 0, 2);
    PrintText(1, 10, 2);
    PrintText(1, 0, 3);
    PrintText(1, 10, 3);
  }
  if (ScreenCurrentMenu == 1) {
    PrintText(1, 0, 2);
    //PrintText(1, 10, 2);
    PrintText(1, 0, 3);
    PrintText(1, 10, 3);
  }
  if (ScreenCurrentMenu == 2) {
    PrintText(1, 0, 2);
    PrintText(1, 10, 2);
    //PrintText(1, 0, 3);
    PrintText(1, 10, 3);
  }
  if (ScreenCurrentMenu == 3) {
    PrintText(1, 0, 2);
    PrintText(1, 10, 2);
    PrintText(1, 0, 3);
    //PrintText(1, 10, 3);
  }
}
