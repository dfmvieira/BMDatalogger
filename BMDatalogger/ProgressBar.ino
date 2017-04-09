// -- character with fith bar
byte _level0[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};

void GraphInit() {
  lcd.createChar(0, _level0);
}

int GraphMinValue = 0;
int GraphMaxValue = 1;

void GraphSetMinValue(long minValue) {
  GraphMinValue = minValue;
}

void GraphSetMaxValue(long maxValue) {
  GraphMaxValue = maxValue;
}

void GraphDrawValue(int value) {
  // calculate character count
  byte fullChars = (long)(value + GraphMinValue) * 10 / GraphMaxValue;
      
  // write characters
  for(byte i=0; i<fullChars; i++) {
    lcd.write((byte)0);
  }
  
  // clear characters left over
  for(byte i=0; i<sizeof(fullChars) - 10; i++) {
      lcd.write(' ');
  }
}
