# Big, bigger, biggest? 7 segment LED clock

There are various examples of 7 segment LED clocks on the internet, but I wanted to use the biggest displays I could buy. I found 4 inch and 5 inch displays on AliExpress. The 4 inch were cheaper when I bought five and from the 5 inch I bought six.
To control these I use an ESP8266 that connects to NTP via Wifi, to assure the correct time.
The 4 inch clock shows hours and minutes, the 5 inch clock shows hours, minutes and seconds. I use the decimal point to separate these.

The clock has a web interface with the following functions:

- Countdown from a preset time in hh:mm:ss
- Countup to a preset time in hh:mm:ss
- Start a stopwatch function in mm:ss:ms
- Show the lap time (display freezes, but stopwatch keeps running)
- Reset the stopwatch to zero
- Go back to clock function

![Inside 6 digits display](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/d76a12e9-9b08-444d-879d-8efd1917c493)
 
As an option, it is  possible to connect three push buttons for the stopwatch functions Start, Reset and Lap.

An optional DS18B20 temperature sensor can be added that will display the temperature every 30 seconds.

A printed circuit has been made for the control function and separate PCB’s have been made to accommodate the shift registers that control the displays.
The displays are glued in a precisely cut passepartout and put in a picture frame of IKEA, type RIBBA, 50x23 for the 4 inch displays and 50x70 for the 5 inch displays. If you only use 4 displays of 4 inch, you could use a 30x40 picture frame. The PCB’s are put in the back of the picture frame. The clock can be used standing or hanging.

## 6 Digits Time Display:
![6DigitsTime](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/a0f3204d-f64c-49c1-ad91-7e9fe9fb2973)

## 6 Digits Temperature Display:
![6DigitsTemp](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/98fc21ce-9cca-4ef3-ae99-019a1ba920a0)

## 5 Digits Time display:
![5DigitsTime](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/13aed81f-8734-4943-9268-e9f4336f618a)

## inside picture of the first version:
![04E3923D-DB4A-49AA-984C-2F95C857FE4E](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/90b241ce-252c-43e6-af24-74f1e56b5de8)
