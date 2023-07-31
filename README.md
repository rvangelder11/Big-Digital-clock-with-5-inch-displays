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

As an option, it is  possible to connect three push buttons for the stopwatch functions Start, Reset and Lap.

An optional DS18B20 temperature sensor can be added that will display the temperature every 30 seconds.

Optionally, the brightness can be dimmed when it gets darker via an LDR (for use in a bedroom).

A printed circuit has been made for the control function and separate PCB’s have been made to accommodate the shift registers that control the displays.
The displays are glued in a precisely cut passepartout and put in a picture frame of IKEA, type RIBBA, 50x23 for the 4 inch displays and 50x70 for the 5 inch displays. If you only use 4 displays of 4 inch, you could use a 30x40 picture frame. The PCB’s are put in the back of the picture frame. The clock can be used standing or hanging.

## 6 Digits Time Display:
![6DigitsTime](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/a51ce6e8-8521-432c-a2b2-5d95c8d3e93e)

## 6 Digits Temperature Display:
![6DigitsTemp](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/53d1362f-3731-4e34-8a96-9a86dece53f5)

## 5 Digits Time display:
![5DigitsTime](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/92d311b0-9635-4361-b641-07ed481a9d74)

## inside picture of the first version:
![04E3923D-DB4A-49AA-984C-2F95C857FE4E](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/0a4e813a-29f3-410e-afdc-8e5e89cf550d)

