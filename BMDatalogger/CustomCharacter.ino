// -- character with fith bar
byte level0[8] = {
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
byte level1[8] = {
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
byte level2[8] = {
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
byte level3[8] = {
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
byte level4[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110
};

//###########################################################################################################
//###########################################################################################################
//###########################################################################################################

byte custom1[8] =
{ 
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000 
};

byte custom2[8] =
{ 
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte custom3[8] =
{ 
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111 
};

byte custom4[8] =
{ 
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};

byte custom5[8] =
{ 
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100 
};

byte custom6[8] =
{ 
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111 
};

byte custom7[8] =
{ 
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111 
};

byte custom8[8] =
{ 
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

const char *bigChars[][2] = {
  {"\024", "\004"}, // .
  {"\024\024\004\001", "\004\001\024\024"}, // /
  {"\010\001\002", "\003\004\005"}, // 0
  {"\002\024", "\377\024"}, // 1
  {"\006\006\002", "\003\007\007"}, // 2
  {"\006\006\002", "\007\007\005"}, // 3
  {"\003\004\002", "\024\024\377"}, // 4
  {"\377\006\006", "\007\007\005"}, // 5
  {"\010\006\006", "\003\007\005"}, // 6
  {"\001\001\002", "\024\010\024"}, // 7
  {"\010\006\002", "\003\007\005"}, // 8
  {"\010\006\002", "\024\024\377"}, // 9
};

//###########################################################################################################
//###########################################################################################################
//###########################################################################################################

int InitMode = 0;

void CharacterInit(bool Bars) {
  if (Bars && InitMode != 1) {
    lcd.begin(20, 4);
    lcd.createChar(0, level0);
    lcd.createChar(1, level1);
    lcd.createChar(2, level2);
    lcd.createChar(3, level3);
    lcd.createChar(4, level4);
    InitMode = 1;
  }
  if (!Bars && InitMode != 2) {
    lcd.begin(20, 4);
    lcd.createChar(1, custom1);
    lcd.createChar(2, custom2);
    lcd.createChar(3, custom3);
    lcd.createChar(4, custom4);
    lcd.createChar(5, custom5);
    lcd.createChar(6, custom6);
    lcd.createChar(7, custom7);
    lcd.createChar(8, custom8);
    InitMode = 2;
  }
}

int GraphMinValue = 0;
int GraphMaxValue = 1;

void GraphSetValue(int minValue, int maxValue) {
  GraphMinValue = minValue;
  GraphMaxValue = maxValue;
}

void GraphDrawValue(int value, int Lenght) {
  CharacterInit(true);
  
  double percent = (((double) GraphMinValue + (double) value) / (double) GraphMaxValue) * 100;
  double RowsNumber = ((double) Lenght / 100) * (double) percent;
  int RowsDone = 0;
  
  // drawing black rectangles on LCD
  if (RowsNumber >= 1) {
    for (int i=1; i < RowsNumber; i++) {
      lcd.write((uint8_t)0);
      RowsDone++;
    }
  }

  RowsNumber = RowsNumber - RowsDone;
  unsigned int peace = RowsNumber * 5;
  
  // drawing charater's colums
  switch (peace) {
    case 0:
      break;
    case 1:
      lcd.write((uint8_t)1);
      RowsDone++;
      break;
    case 2:
      lcd.write((uint8_t)2);
      RowsDone++;
      break;
    case 3:
      lcd.write((uint8_t)3);
      RowsDone++;
      break;
    case 4:
      lcd.write((uint8_t)4);
      RowsDone++;
      break;
  }
  
  //clearing line
  for (int i =0; i < (Lenght - RowsDone); i++) lcd.write(' ');   //Write Empty Lines
}

//###########################################################################################################
//###########################################################################################################
//###########################################################################################################

int writeBigChar(char ch, int x, int y) {
  const char *(*blocks)[2] = NULL; // Pointer to an array of two strings (character pointers)

  // If outside our table range, do nothing
  if (ch < '.' || ch > '9') return 0;
  
  blocks = &bigChars[ch-'.']; // Look up the definition
  
  for (int half = 0; half <=1; half++) {
    int t = x; // Write out top or bottom string, byte at a time
    for (const char *cp = (*blocks)[half]; *cp; cp++) {
      lcd.setCursor(t, y+half);
      lcd.write(*cp);
      t = (t+1) % 40; // Circular scroll buffer of 40 characters, loop back at 40
    }
    lcd.setCursor(t, y+half);
    lcd.write(' '); // Make space between letters, in case overwriting
  }
  return strlen((*blocks)[0]); // Return char width
}

void writeBigString(char *str, int x, int y) {
  CharacterInit(false);
  char c;
  while ((c = *str++)) x += writeBigChar(c, x, y) + 1;
}
