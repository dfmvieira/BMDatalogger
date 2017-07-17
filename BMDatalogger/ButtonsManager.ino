#define ON 1
#define OFF 0
volatile int buttonTop = 0;
volatile int buttonBottom = 0;
volatile int buttonDual = 0;
unsigned long last_interrupt_time=0;
const int debouncing = 80;

void GetButtonStates() {
  GetButtonTopState();
  if (buttonTop == ON) {
    if (!InMain) {
      if(ScreenCurrentMenu != 2) NextDisplay();
      //if(ScreenCurrentMenu == 2) ResetMilCodes();
      if(ScreenCurrentMenu == 2) buttonTop = OFF;
    } else {
      if (!Sleeping) MainMenuNext();
    }
  }
  if (buttonBottom == ON) MainMenu();
  if (buttonDual == ON) ResetPeaks();
}

/*void ResetMilCodes() {
  lcd.clear();
  ResetBufferIndex();
  GetInfosString(11);
  writeBigString(0, 0);
  ResetBufferIndex();
  delay(250);
  bool Resetted = ResetMil();
  if (Resetted) GetInfosString(12);
  if (!Resetted) GetInfosString(13);
  writeBigString(0, 2);

  delay(1000);
  lcd.clear();
  buttonTop=OFF;
}*/

void ResetPeaks() {
  lcd.clear();
  ResetBufferIndex();
  GetInfosString(11);
  writeBigString(0, 0);
  ResetBufferIndex();
  InitPeak();
  GetInfosString(12);
  writeBigString(0, 2);

  delay(1000);
  lcd.clear();
  buttonDual=OFF;
}

void NextDisplay() {
  if(ScreenCurrentMenu == 0) {
    ScreenCurrentPage++;
    if(ScreenCurrentPage > 8) ScreenCurrentPage = 1;
  }
  if(ScreenCurrentMenu == 1) {
    ScreenCurrentPeak++;
    if(ScreenCurrentPeak >= MaxDataValue) ScreenCurrentPeak = 0;
  }
  ShowPage();
  buttonTop=OFF;
}

void MainMenu() {
  lcd.backlight();
  lcd.clear();
  if(ScreenCurrentMenu != 3) {
    if (InMain) InMain = false;
    else InMain = true;
  }
  else {
    if (!Sleeping) {
      lcd.noBacklight();
      Sleeping = true;
    } else {
      Sleeping = false;
    }
  }
  buttonBottom=OFF;
  delay(500);
}

void MainMenuNext() {
  ScreenCurrentMenu++;
  if(ScreenCurrentMenu > 3) ScreenCurrentMenu = 0;
  buttonTop=OFF;
  delay(100);
}

void ShowPage() {
  lcd.clear();
  lcd.backlight();

  ResetBufferIndex();
  GetInfosString(5);
  writeBigString(3, 0);
  
  ResetBufferIndex();
  if(ScreenCurrentMenu == 0) Add_String(String(ScreenCurrentPage));
  if(ScreenCurrentMenu == 1) Add_String(String(ScreenCurrentPeak));
  writeBigString(7, 2);
  
  delay(500);
  lcd.clear();
  buttonTop=OFF;
}

void ShowMenu() {
  lcd.clear();
  lcd.backlight();
  ResetBufferIndex();
  GetInfosString(6);
  writeBigString(3, 0);

  ResetBufferIndex();
  int XOffset = 0;
  if (ScreenCurrentMenu == 0) GetInfosString(7);
  if (ScreenCurrentMenu == 1) {
    GetInfosString(8);
    XOffset = 2;
  }
  if (ScreenCurrentMenu == 2) {
    GetInfosString(9);
    XOffset = 5;
  }
  writeBigString(XOffset, 2);
  
  delay(1000);
  lcd.clear();
  buttonTop=OFF;
}

void GetButtonTopState() {
  if (digitalRead(TopButton) == LOW) {
    unsigned long interrupt_time = millis();  
    if (buttonTop == OFF && buttonDual == OFF && (interrupt_time - last_interrupt_time > debouncing)) {
      if (ScreenCurrentMenu == 1 && digitalRead(BottomButton) == LOW && buttonBottom == OFF) buttonDual=ON;
      else buttonTop=ON;
      
      last_interrupt_time = interrupt_time;
    }
  }

  if (digitalRead(BottomButton) == LOW) {
    unsigned long interrupt_time = millis();
    if (buttonBottom == OFF && buttonDual == OFF && (interrupt_time - last_interrupt_time > debouncing)) {
      buttonBottom=ON;
      last_interrupt_time = interrupt_time;
    }
  }
}
