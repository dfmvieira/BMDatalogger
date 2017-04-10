//Buttons Vars
#define ON 1
#define OFF 0
volatile int buttonTop = 0;
unsigned long last_interrupt_time=0;
const int debouncing = 80;

//###########################################################################################################
//###########################################################################################################
//###########################################################################################################

//Apply Buttons
void GetButtonStates() {
  GetButtonTopState();
  if (buttonTop == ON) NextDisplay();
}

void NextDisplay() {
  ScreenCurrentPage++;
  if(ScreenCurrentPage > 4) ScreenCurrentPage = 1;
  ShowPage();
  buttonTop=OFF;
}

void ShowPage() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     PAGE #" + String(ScreenCurrentPage));
  delay(1000);
  lcd.clear();
  buttonTop=OFF;
}

//###########################################################################################################
//###########################################################################################################
//###########################################################################################################
//Get States
void GetButtonTopState() {
  if (digitalRead(TopButton) == LOW) {
    if (!EcuConnected)
      EcuConnected = true;
    else {
      unsigned long interrupt_time = millis();  
      if (buttonTop == OFF && (interrupt_time - last_interrupt_time > debouncing)) {
        buttonTop=ON;
        last_interrupt_time = interrupt_time;
      }
    }
  }
}
