const String  DegChar = "\xDF";

String GetLAMBA() {
  String Str = "";
  if (UseLAMBA == 1) Str = "LAMBA";
  if (UseLAMBA == 0) Str = "AFR";
  return Str;
}

String GetWBType() {
  String Str = "";
  if (WBType == 0) Str = "OEM";
  return Str;
}

String GetO2Str() {
  String Str = "";
  if (O2Input == 0) Str = "O2";
  if (O2Input == 1) Str = "ELD";
  if (O2Input == 2) Str = "EGR";
  if (O2Input == 3) Str = "B6";
  return Str;
}

String GetMapStr() {
  String Str = "";
  if (MapValue == 0) Str = "mBar";
  if (MapValue == 1) Str = "Bar";
  if (MapValue == 2) Str = "inHg";
  if (MapValue == 3) Str = "PSI";
  if (MapValue == 4) Str = "kPa";
  return Str;
}

String GetTempCelcius() {
  String Str = "";
  if (UseCelcius == 1) Str = DegChar + "C";
  if (UseCelcius == 0) Str = DegChar + "F";
  return Str;
}

String GetKMH() {
  String Str = "";
  if (UseKMH == 1) Str = "kmh";
  if (UseKMH == 0) Str = "mph";
  return Str;
}
