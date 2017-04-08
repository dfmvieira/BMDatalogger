//Buttons Vars
#define ON 1
#define OFF 0
volatile int buttonTop = 0;
volatile int buttonBottom = 0;
volatile int buttonHold = 0;
unsigned long last_interrupt_time=0;
int debouncing = 50;
bool DoublePress = false;

//Apply Buttons
void GetButtonStates() {
  GetButtonTopState();
  GetButtonBottomState();
  
  if (buttonTop == ON) ApplyTop();
  if (buttonBottom == ON) ApplyBottom();
  if (buttonHold == ON) ApplyDual();
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
  buttonHold=OFF;
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

void GetButtonBottomState() {
  if (digitalRead(BottomButton) == LOW) {
    if (!EcuConnected)
      EcuConnected = true;
    else {
      unsigned long interrupt_time = millis();  
      if (buttonBottom == OFF && (interrupt_time - last_interrupt_time > debouncing)) {
        if (!DoublePress) {
          DoublePress = true;
          buttonBottom=ON;
        }
        else buttonHold=ON;
        last_interrupt_time = interrupt_time;
      }
    }
  } else DoublePress = false;
}
