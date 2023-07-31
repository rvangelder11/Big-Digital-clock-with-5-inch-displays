# Big, bigger, biggest? 7 segment LED clock

There are various examples of 7 segment LED clocks on the internet, but I wanted to use the biggest displays I could buy. I found 4 inch and 5 inch displays on AliExpress. The 4 inch were cheaper when I bought five and from the 5 inch I bought six.
To control these I use an ESP8266 that connects to NTP via Wifi, to assure the correct time.
The 4 inch clock shows hours and minutes, the 5 inch clock shows hours, minutes and seconds. I use the decimal point to separate these.

The clock has also a web interface with the following functions:
•	Countdown from a preset time in hh:mm:ss
•	Countup to a preset time in hh:mm:ss
•	Start a stopwatch function in mm:ss:ms
•	Show the lap time (display freezes, but stopwatch keeps running)
•	Reset the stopwatch to zero
•	Go back to clock function

 
As an option, it is also possible to connect three push buttons for the stopwatch functions Start, Reset and Lap.
A printed circuit has been made for the control function and separate PCB’s have been made to accommodate the shift registers that control the displays.
The displays are glued in a precisely cut passepartout and put in a picture frame of IKEA, type RIBBA, 50x23 for the 4 inch displays and 50x70 for the 5 inch displays. If you only use 4 displays of 4 inch, you could use a 30x40 picture frame. The PCB’s are put in the back of the picture frame. The clock can be used standing or hanging. 
