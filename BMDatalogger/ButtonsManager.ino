//Buttons Vars
#define ON 1
#define OFF 0
volatile int buttonTop = 0;
unsigned long last_interrupt_time=0;
const int debouncing = 80;

//Apply Buttons
void GetButtonStates() {
  GetButtonTopState();
  if (buttonTop == ON) NextDisplay();
}

void NextDisplay() {
  ScreenCurrentPage++;
  if(ScreenCurrentPage > 4) ScreenCurrentPage = 1;
  ApplyPage();
  buttonTop=OFF;
}

void ApplyPage() {
  if (ScreenCurrentPage == 1) for (int i=0; i < 8; ++i ) ScreenIndex[i] = ScreenPage1[i];
  if (ScreenCurrentPage == 2) for (int i=0; i < 8; ++i ) ScreenIndex[i] = ScreenPage2[i];
  if (ScreenCurrentPage == 3) for (int i=0; i < 8; ++i ) ScreenIndex[i] = ScreenPage3[i];
  if (ScreenCurrentPage == 4) for (int i=0; i < 8; ++i ) ScreenIndex[i] = ScreenPage4[i];
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
