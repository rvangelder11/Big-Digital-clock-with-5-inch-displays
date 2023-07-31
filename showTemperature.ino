//---------------------------------------------
// this function shows the current temperature

void showTemperature() {
  int oldNrDisplays;
  tempSensors.requestTemperatures();                // start new temperature measurement if there are DS sensors detected
  double temp = tempSensors.getTempCByIndex(0);     // read temperature
  Serial.println("temperature = " + String(temp));  // print temperature
  temp *= 100;
  postNumber(15, false);  // letter C
  postNumber(16, false);  // degree symbol
  oldNrDisplays = Nr_Displays;
  Nr_Displays = 4;  // to get the temperature on the left 4 positions, such that degree celsius fits there after
  showNumber((int)temp, false);
  Nr_Displays = oldNrDisplays;

  digitalWrite(segmentLatch, LOW);   // make low to enable raising edge
  digitalWrite(segmentLatch, HIGH);  // Data transfers to the shift register on the rising edge of segmentClock (SRCK)
  delay(3100);
}
