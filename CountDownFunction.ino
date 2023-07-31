//---------------------------------------------------
// This function starts a counter from a given start value to countdown to zero, started from the webpage
 
void CountDownFunction() {
  int TimeNumber, SecLeft;
  //if ((now() - Startsec) <= secs) {                                               // now() - startsec counts up until the coutdown value has been reached. The formula below inverts that to counting down.
    ArduinoOTA.handle();                                                          // check for OTA request
    SecLeft = secs - now() + Startsec;                                            // invert the value to enable countdown
    int nr_hours = SecLeft / 3600;                                                // 3600 seconds in an hour
    int nr_minutes = (SecLeft % 3600) / 60 ;                                      // the remainder from hours division  divided by minutes, gives the full minutes, and so on...
    int nr_seconds = ((SecLeft % 3600) % 60);
    TimeNumber = nr_hours * 10000 + nr_minutes * 100 + nr_seconds;             // decimal disply, so minutes are shown as 10.000's in the 1st display from left, seconds as 100's and 1/100 as single
    showNumber(TimeNumber, false);                                                 // show countdown time with non blinking dp
  //}
  if (SecLeft == 0) {                                                              // when countdown is complete:
    ArduinoOTA.handle();                                                           // check for OTA request
    showNumber(0, false);                                                          // show 0 on display
  }
}
