//Buttons Vars
#define ON 1
#define OFF 0
volatile int buttonTop = 0;
volatile int buttonBottom = 0;
volatile int buttonDual = 0;
unsigned long last_interrupt_time=0;
const int debouncing = 80;

//Apply Buttons
void GetButtonStates() {
  GetButtonTopState();
  GetButtonBottomState();
  
  if (buttonTop == ON) ApplyTop();
  if (buttonBottom == ON) ApplyBottom();
  if (buttonDual == ON) ApplyDual();
}

void ApplyTop() {
  if (!ScreenOption) NextDisplay();
  if (ScreenOption) {
    if (ScreenEdit) EditTop();
    if (!ScreenEdit) ScreenEdit = true;
  }
  buttonTop=OFF;
}

void ApplyBottom() {
  if (!ScreenOption) NextLine();
  if (ScreenOption) {
    if (ScreenEdit) EditBottom();
    if (!ScreenEdit) NextLine();
  }
  buttonBottom=OFF;
}

void ApplyDual() {
  if (ScreenOption) {
    if (!ScreenEdit) ScreenOption = false;
    else {
      SaveOptions();
      ScreenEdit = false;
    }
  }
  else {
    ScreenCurrentIndex = 0;  //Reselect The First Index to Edit
    ScreenOption = true;
  }
  buttonDual=OFF;
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
      if (buttonTop == OFF &&  buttonDual == OFF && (interrupt_time - last_interrupt_time > debouncing)) {
        delay(30);
        if (digitalRead(BottomButton) == LOW) buttonDual = ON;
        else buttonTop=ON;
        last_interrupt_time = interrupt_time;
      }
    }
  }
}

void GetButtonBottomState() {
  if (digitalRead(BottomButton) == LOW) {
    if (!EcuConnected)
      EcuConnected = true;
    else {
      unsigned long interrupt_time = millis();  
      if (buttonBottom == OFF &&  buttonDual == OFF && (interrupt_time - last_interrupt_time > debouncing)) {
        delay(30);
        if (digitalRead(TopButton) == LOW) buttonDual = ON;
        else buttonBottom=ON;
        last_interrupt_time = interrupt_time;
      }
    }
  }
}
