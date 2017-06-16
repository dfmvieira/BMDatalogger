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
    if (EcuConnected) {
      if(ScreenCurrentMenu != 2) NextDisplay();
      if(ScreenCurrentMenu == 2) ResetMilCodes();
    } else {
      NextMenu();
      buttonTop=OFF;
    }
  }
  if (buttonBottom == ON) NextMenu();
  if (buttonDual == ON) {
    InitPeak();
    buttonDual = OFF;
  }
}

void ResetMilCodes() {
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

void NextMenu() {
  if (EcuConnected) ScreenCurrentMenu++;
  if (!EcuConnected) EcuConnected = true;
  
  if(ScreenCurrentMenu > 2) ScreenCurrentMenu = 0;
  ShowMenu();
  buttonBottom=OFF;
}

void ShowPage() {
  lcd.clear();
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
  ResetBufferIndex();
  GetInfosString(6);
  writeBigString(3, 0);

  ResetBufferIndex();
  if (ScreenCurrentMenu == 0) GetInfosString(7);
  if (ScreenCurrentMenu == 1) GetInfosString(8);
  if (ScreenCurrentMenu == 2) GetInfosString(9);
  writeBigString(0, 2);
  
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
