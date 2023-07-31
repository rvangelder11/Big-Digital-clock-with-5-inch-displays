//---------------------------------------------
// this function shows the current time

void showClock() {
  ArduinoOTA.handle();
  if (Nr_Displays == 6) {
    long TimeNumber = myTZ.hour() * 10000 + myTZ.minute() * 100 + myTZ.second();
    showNumber(TimeNumber, false);
  } else {
    long TimeNumber = myTZ.hour() * 100 + myTZ.minute();
    showNumber(TimeNumber, false);
  }
}
