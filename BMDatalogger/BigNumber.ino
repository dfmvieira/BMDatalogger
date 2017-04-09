byte custom[8][8] = {
  { 
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000 
  },
  {
    B11100,
    B11110,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
  },  
  { 
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B01111,
    B00111 
  },
  { 
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111 
  },
  { 
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11110,
    B11100 
  },
  { 
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111 
  },
  { 
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111 
  },
  {
    B00111,
    B01111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
  }
};

// Characters, each with top and bottom half strings
// \nnn string encoding is octal, so:
// \010 = 8 decimal (8th programmable character)
// \024 = 20 decimal (space)
// \377 = 255 decimal (black square)

const char *bigChars[][2] = {
  {"\024", "\004"}, // .
  {"\024\024\004\001", "\004\001\024\024"}, // /
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
};

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
  char c;
  while ((c = *str++)) x += writeBigChar(c, x, y) + 1;
}

void BigNumberInit() {
  for (int i=0; i<8; i++) lcd.createChar(i+1, custom[i]);
}
