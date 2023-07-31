//--------------------------------------
// this function facilitates a stopwatch function (triggered from the webpage)

void StopWatchFunction() {
  ArduinoOTA.handle();
  int MillisPassed = millis() - millis_since_start;                             // Set startpoint for stopwatch as an offset from millis since start
  int nr_minutes = (MillisPassed % hour_ms) / minute_ms ;                       // the remainder from minutes division (in milliseconds) divided by minutes_ms, gives the full minutes, and so on...
  int nr_seconds = ((MillisPassed % hour_ms) % minute_ms) / second_ms;
  int nr_hundreths = (((MillisPassed % hour_ms) % minute_ms) % second_ms) / 10;
  TimeNumber = nr_minutes * 10000 + nr_seconds * 100 + nr_hundreths;        // decimal display, so minutes are shown as 10.000's in the 1st display from left, seconds as 100's and 1/100 as single
  if (state == 4)showNumber(TimeNumber, false);                               // show live time as long as lap is not selected. If lap is selected, the time freezes on the display, but the timer continues
}
