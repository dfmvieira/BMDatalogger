#define ON 1
#define OFF 0
volatile int buttonTop = 0;
volatile int buttonHold = 0;
unsigned long last_interrupt_time=0;
const int debouncing = 80;
bool Holding = false;

void GetButtonStates() {
  GetButtonTopState();
  if (buttonTop == ON) NextDisplay();
  if (buttonHold == ON) NextMenu();
}

void NextDisplay() {
  if(ScreenCurrentMenu == 0) {
    ScreenCurrentPage++;
    if(ScreenCurrentPage > 4) ScreenCurrentPage = 1;
  }
  if(ScreenCurrentMenu == 1) {
    ScreenCurrentPeak++;
    if(ScreenCurrentPeak >= MaxDataValue) ScreenCurrentPeak = 0;
  }
  ShowPage();
  buttonTop=OFF;
}

void NextMenu() {
  ScreenCurrentMenu++;
  if(ScreenCurrentMenu > 1) ScreenCurrentMenu = 0;
  ShowMenu();
  buttonHold=OFF;
}

void ShowPage() {
  lcd.clear();
  ResetBufferIndex(0);
  GetStringAt(0, 5, true);
  RemakeBigBuffer();
  writeBigString(StringBufferBig, 0, 0);

  ResetBufferIndex(0);
  if(ScreenCurrentMenu == 0) Add_String(0, String(ScreenCurrentPage));
  if(ScreenCurrentMenu == 1) Add_String(0, String(ScreenCurrentPeak));
  RemakeBigBuffer();
  writeBigString(StringBufferBig, 0, 3);
  
  delay(1000);
  lcd.clear();
  buttonTop=OFF;
}

void ShowMenu() {
  lcd.clear();
  ResetBufferIndex(0);
  GetStringAt(0, 6, true);
  RemakeBigBuffer();
  writeBigString(StringBufferBig, 0, 0);

  ResetBufferIndex(0);
  Add_String(0, String(ScreenCurrentMenu));
  RemakeBigBuffer();
  writeBigString(StringBufferBig, 0, 3);
  delay(1000);
  lcd.clear();
  buttonTop=OFF;
}

void GetButtonTopState() {
  if (digitalRead(TopButton) == LOW) {
    if (!EcuConnected)
      EcuConnected = true;
    else {
      unsigned long interrupt_time = millis();  
      if (buttonTop == OFF && buttonHold == OFF && (interrupt_time - last_interrupt_time > debouncing)) {
        if (!Holding) buttonTop=ON;
        if (Holding) buttonHold=ON;
        Holding = true;
        last_interrupt_time = interrupt_time;
      }
    }
  } else Holding = false;
}
