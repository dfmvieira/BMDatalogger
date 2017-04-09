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
// -- character with one bars
/*byte _level1[8] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000
};
// -- character with two bars
byte _level2[8] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000
};
// -- character with three bars
byte _level3[8] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100
};
// -- character with four bars
byte _level4[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110
};*/

//###########################################################################################################
//###########################################################################################################
//###########################################################################################################

void GraphInit() {
  lcd.createChar(10, _level0);
  /*lcd.createChar(11, _level1);
  lcd.createChar(12, _level2);
  lcd.createChar(13, _level3);
  lcd.createChar(14, _level4);*/
  
}

int GraphMinValue = 0;
int GraphMaxValue = 1;

void GraphSetValue(int minValue, int maxValue) {
  GraphMinValue = minValue;
  GraphMaxValue = maxValue;
}

void GraphDrawValue(int value, int Lenght) {
  int Count = GraphMinValue + value * Lenght / GraphMaxValue;
  int CountHalf = (GraphMinValue + value * Lenght * 5 / GraphMaxValue) % 5;

  for(byte i=0; i < Count; i++) lcd.write((uint8_t)10);
  /*if(CountHalf > 0) {
    lcd.write((char) CountHalf + 10);
    Count++;
  }*/
  for(byte i=0; i < Lenght - Count; i++) lcd.write(' ');
}
