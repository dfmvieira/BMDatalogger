const char custom[][8] PROGMEM = {
      { 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00 }, // char 1 
      { 0x18, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F }, // char 2 
      { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x03 }, // char 3 
      { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F }, // char 4 
      { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E, 0x1C, 0x18 }, // char 5 
      { 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F }, // char 6 
      { 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F }, // char 7 
      { 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F }  // char 8 
};

const char *bigChars[][2] = { 
  {"\024\024\024", "\024\024\024"}, // Space
  {"\024", "\004"}, // .
  {"\010\001\002", "\003\004\005"}, // 0
  {"\001\002\024", "\024\377\024"}, // 1
  {"\006\006\002", "\003\007\007"}, // 2
  {"\006\006\002", "\007\007\005"}, // 3
  {"\003\004\002", "\024\024\377"}, // 4
  {"\377\006\006", "\007\007\005"}, // 5
  {"\010\006\006", "\003\007\005"}, // 6
  {"\001\001\002", "\024\010\024"}, // 7
  {"\010\006\002", "\003\007\005"}, // 8
  {"\010\006\002", "\024\024\377"}, // 9
  {"\004", "\001"}, // :
  {"\010\006\002", "\377\024\377"}, // A
  {"\377\006\005", "\377\007\002"}, // B
  {"\010\001\001", "\003\004\004"}, // C
  {"\377\001\002", "\377\004\005"}, // D
  {"\377\006\006", "\377\007\007"}, // E
  {"\377\006\006", "\377\024\024"}, // F
  {"\010\001\001", "\003\004\002"}, // G
  {"\377\004\377", "\377\024\377"}, // H
  {"\001\377\001", "\004\377\004"}, // I
  {"\024\024\377", "\004\004\005"}, // J
  {"\377\004\005", "\377\024\002"}, // K
  {"\377\024\024", "\377\004\004"}, // L
  {"\010\003\005\002", "\377\024\024\377"}, // M
  {"\010\002\024\377", "\377\024\003\005"}, // N
  {"\010\001\002", "\003\004\005"}, // 0
  {"\377\006\002", "\377\024\024"}, // P
  {"\010\001\002\024", "\003\004\377\004"}, // Q
  {"\377\006\002", "\377\024\002"}, // R
  {"\010\006\006", "\007\007\005"}, // S
  {"\001\377\001", "\024\377\024"}, // T
  {"\377\024\377", "\003\004\005"}, // U
  {"\003\024\024\005", "\024\002\010\024"}, // V
  {"\377\024\024\377", "\003\010\002\005"}, // W
  {"\003\004\005", "\010\024\002"}, // X
  {"\003\004\005", "\024\377\024"}, // Y
  {"\001\006\005", "\010\007\004"}, // Z
};

int InitMode = 0;

void CharacterInit(bool Bars) {
  if (Bars && InitMode != 1) {
    lcd.begin(20, 4);
    for (int i=0; i<5; i++ ) {
      char ThisArray[8];
      byte ThisByte = 0x00;
      if (i == 0) ThisByte = 0x1F;
      if (i == 1) ThisByte = 0x10;
      if (i == 2) ThisByte = 0x18;
      if (i == 3) ThisByte = 0x1C;
      if (i == 4) ThisByte = 0x1E;
      for (int i2=0; i2<8; i2++) ThisArray[i2]= (char) ThisByte;
      lcd.createChar (i, ThisArray);
    }
    InitMode = 1;
  }
  if (!Bars && InitMode != 2) {
    lcd.begin(20, 4);
    for (int i=0; i<8; i++ ) {
      char ThisArray[8];
      for (int i2=0; i2<8; i2++) ThisArray[i2]= (char) pgm_read_byte( &custom[i][i2] );
      lcd.createChar (i+1, ThisArray);
    }
    InitMode = 2;
  }
}

void GraphDrawValue(const int value, const int Lenght) {
  CharacterInit(true);
  
  double percent = (((double) PeakMinValue + (double) value) / (double) PeakMaxValue) * 100;
  double RowsNumber = ((double) Lenght / 100) * (double) percent;
  int RowsDone = 0;
  
  if (RowsNumber >= 1) {
    for (int i=1; i < RowsNumber; i++) {
      lcd.write((uint8_t)0);
      RowsDone++;
    }
  }

  RowsNumber = RowsNumber - RowsDone;
  unsigned int peace = RowsNumber * 5;
  
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
  
  for (int i =0; i < (Lenght - RowsDone); i++) lcd.write(' ');
}

int writeBigChar(const char ch, const int x, const int y) {
  const char *(*blocks)[2] = NULL;

  if (ch < ' ' || ch > '_') return 0;
  if (ch >= '!' || ch <= '-') return 0;
  if (ch == '/') return 0;
  if (ch >= ';' || ch <= '@') return 0;
  
  blocks = &bigChars[ch-' '];
  
  for (int half = 0; half <=1; half++) {
    int t = x;
    for (const char *cp = (*blocks)[half]; *cp; cp++) {
      lcd.setCursor(t, y+half);
      lcd.write(*cp);
      t = (t+1) % 40;
    }
    lcd.setCursor(t, y+half);
    lcd.write(' ');
  }
  return strlen((*blocks)[0]);
}

void writeBigString(const char *str, int x, int y) {
  CharacterInit(false);
  char c;
  while ((c = *str++)) x += writeBigChar(c, x, y) + 1;
}
