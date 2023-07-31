//--------------------------------------------------
//this routine gets a value in and shows it in its number of digits on the display.
//If blink is true it shows a blinking cursor on pos 3 and 5 from the right (to imitate a clock)
// this version pushes digits from Left to right
// rightpos shows the final position from right to left: 543210 for 6 digits, 43210 for 5 digits
// The 5 display clock show a blank on the most left position, followed by hh.mm
// The 6 digits clock shows hh.mm.ss

void showNumber(int value, boolean Blink) {  // Takes a number and displays x numbers. Displays absolute value (no negatives). Blink = true show a blinking dp at displays 3 and 5 from the right
  byte minus = (value < 0) ? 1 : 0;          // set minus to 1 for negative values
  int number = abs(value);                   // Remove negative signs and any decimals
  boolean Before10 = false;                  // placeholder for before 10 o'clock to add an extra space
  byte rightpos;                             // placeholder for the position of the digit, calculated from  right to left
  boolean dp;                                // placeholder to contain whether a dp shpuld be shown or not
  if (Nr_Displays == 6 and number < 95959) Before10 = true;
  if (Nr_Displays == 5 and number < 959) Before10 = true;
  rightpos = Nr_Displays - minus;        // rightpos is nr _displays for positive values, NR_DISPLAYS - 1 for negative values
  for (byte x = 0; x < rightpos; x++) {  // for all 7-segment displays
    int remainder = number % 10;         // calculate the Least significant digit
    if (x == 2 or x == 4) {
      if (now() % 2 and Blink) dp = false;                                             // If Blink is true, show a blinking dp on 3rd digit or 5th digit from the right,
      else dp = true;                                                                  // else dp is permanently on
    } else dp = false;                                                                 // all other values are shown w/o dp
    if (x < rightpos - 2) postNumber(remainder, dp);                                   // push the value in the shift register with the dp value as set before, except for the two leftmost position
    else {                                                                             // in the leftmost position
      if (remainder == 0 and state == 0 and x == rightpos - 1) postNumber(10, false);  // if leftmost char is 0, blank this digit by writing a space
      else if (remainder == 0 and state == 0 and x == rightpos - 2 and Before10) postNumber(10, false);
      else postNumber(remainder, dp);  // else write the number
    }
    number /= 10;  // by dividing by ten, the next digit (from the right) can be calculated
  }
  if (minus == 1) postNumber(14, false);  // write a minus sign
  digitalWrite(segmentLatch, LOW);        // make low to enable raising edge
  digitalWrite(segmentLatch, HIGH);       // Data transfers to the shift register on the rising edge of segmentClock (SRCK)
}
