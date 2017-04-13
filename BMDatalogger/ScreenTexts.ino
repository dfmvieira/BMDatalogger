const char string_0[] PROGMEM = "RPM:";
const char string_1[] PROGMEM = "ECT:";
const char string_2[] PROGMEM = "IAT:";
const char string_3[] PROGMEM = "TPS:";
const char string_4[] PROGMEM = "O2:";
const char string_5[] PROGMEM = "IGN:";
const char string_6[] PROGMEM = "INJ:";
const char string_7[] PROGMEM = "FUEL:";
const char string_8[] PROGMEM = "IACV:";
const char string_9[] PROGMEM = "MAP:";
const char string_10[] PROGMEM = "BOOST:";
const char string_11[] PROGMEM = "VSS:";
const char string_12[] PROGMEM = "GEAR:";
const char string_13[] PROGMEM = "BATT:";
const char string_14[] PROGMEM = "ICUT:";
const char string_15[] PROGMEM = "FCUT:";
const char string_16[] PROGMEM = "INJFV:";
const char string_17[] PROGMEM = "2MAP:";
const char string_18[] PROGMEM = "0-100:";
const char string_19[] PROGMEM = "B0100:";

const char inf_0[] PROGMEM = "kmh";
const char inf_1[] PROGMEM = "mph";
const char inf_2[] PROGMEM = "%";
const char inf_3[] PROGMEM = "ms";
const char inf_4[] PROGMEM = "L";
const char inf_5[] PROGMEM = "PAGE";
const char inf_6[] PROGMEM = "MENU";

const char long_0[] PROGMEM = "BMDatalogger ";
const char long_1[] PROGMEM = "   eCtune ISR V3";
const char long_2[] PROGMEM = "  Datalog Protocol  ";
const char long_3[] PROGMEM = "  Made by BM Devs   ";
const char long_4[] PROGMEM = "    NOT CONNECTED   ";
const char long_5[] PROGMEM = "   IS J12 INPLACE?  ";
const char long_6[] PROGMEM = "    PUSH TO START   ";

const char* const StringVars[] PROGMEM = {
  string_0, string_1, string_2, string_3, string_4,
  string_5, string_6, string_7, string_8, string_9, 
  string_10, string_11, string_12, string_13, string_14,
  string_15, string_16, string_17, string_18, string_19
};

const char* const StringInfos[] PROGMEM = {
  inf_0, inf_1, inf_2, inf_3, inf_4, 
  inf_5, inf_6
};

const char* const StringDesc[] PROGMEM = {
  long_0, long_1, long_2, long_3, long_4, 
  long_5, long_6
};

void ResetBufferIndex(bool Long) {
  CurrentBufferIndex = 0;
  if (!Long) for (int i=0; i < 10; i++) StringBuffer[i] = ' ';
  if (Long) for (int i=0; i < 20; i++) StringBufferLong[i] = ' ';
}

void Add_String(bool Long, String ThisStr) {
  int Size = ThisStr.length();
  //int Size = (int) strlen(ThisStr);
  if (!Long && Size > 10) Size = 10;
  if (Long && Size > 20) Size = 20;
  
  Serial.println(String(ThisStr) + " SIZE:" + String(Size));

  char charBuf[ThisStr.length()];
  ThisStr.toCharArray(charBuf, ThisStr.length() + 1);
  for (int i=0; i<Size; i++) AddThisChar(Long, charBuf[i]);
}

void GetStringAt(bool Long, int Addr, bool Infos) {
  unsigned int flash_address = 0;
  if (!Long) {
    if (!Infos) flash_address = pgm_read_word(&StringVars[Addr]);
    if (Infos) flash_address = pgm_read_word(&StringInfos[Addr]);
  }
  if (Long) flash_address = pgm_read_word(&StringDesc[Addr]);

  for (int i=0; i < 20; i++) {
    char c = (char) pgm_read_byte(flash_address++);
    if ((int) c != 0) AddThisChar(Long, c);
    if ((int) c == 0) i += 20;
  }
}

void AddThisChar(bool Long, char This) {
  //Serial.println(String(This));
  if (!Long) {
    if (CurrentBufferIndex < 10) {
      StringBuffer[CurrentBufferIndex] = This;
      CurrentBufferIndex++;
    }
  }
  if (Long) {
    if (CurrentBufferIndex < 20) {
      StringBufferLong[CurrentBufferIndex] = This;
      CurrentBufferIndex++;
    }
  }
}
