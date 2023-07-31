//---------------------------------------------------
//wemos sends out LSD first, meaning that the digits are pushed from left to right
// this routine shifts out a single digit to the display. Decimal can be on (true) of off (false) 
void postNumber(byte number, boolean decimal) {         // Given a number, shifts it out to the display
  byte segments = seg[number];                          // array seg[] contains the 7-segment pattern per digit
  if (decimal) segments ^= dp;                          // add decimal point
  for (byte x = 0 ; x < 8 ; x++) {                      // Clock these 8 bits out to the shift register
    digitalWrite(segmentClock, LOW);                    // make low to enable raising edge
    digitalWrite(segmentData, segments & 1 << (7 - x)); // send data
    digitalWrite(segmentClock, HIGH);                   // Data transfers to the shift register on the rising edge of segmentClock (SRCK)
  }
}
