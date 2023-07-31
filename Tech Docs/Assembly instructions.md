- Remove the backside of the Ribba Picture Frame.
- Take the passepartout and cut out the exact dimensions of the 7 segment displays.
- Glue the displays with a glue gun to the backside of the passepartout:
![IMG_0085](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/b80e2824-63c6-4492-b90e-241433148755)

- Mount the TPIC6C596 Large Digit Driver Driver with doubled sided tape to the backside of each display: 
![IMG_0086](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/7dbeb451-653f-4299-ad17-d1d50ec8e2aa)
- if you suffer from erratic behaviour on the displays, you can add decoupling capacitors of 100 nF between ground an 5V (see picture above).
  
- connect all TPIC6C596 Large Digit Driver Drivers with 6 pin Female-Female Dupont cables:
  
![IMG_0087](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/3e5c3118-16dc-4459-b419-f9761e4b784a)

- connect the outputs of the TPIC6C596 Large Digit Driver Driver to the corresponding pins of the display.
- **PLEASE NOTE**: Because the DP is only one led (the other segments are 5 leds). A 1k resistor (or similar) must be inserted between the dp connection on the pcb and the display. Failing to do so will burn out the DP led!

![IMG_0088](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/52aa3d7c-cbd4-4f13-a60b-4ed9238325d2)

Check whether the input circuit produces a voltage around 9 volts for the 4 inch displays and around 10.5 for the 5 inch displays. Check whether the 5V pin of the ESP8266 socket is 5V. 
Program the ESP8266 and mount this on the control pcb or connect it to the power supply.
Check via USB that the ESP8266 is working.

Connect the ESP8266 with the rightmost display. I have made a control PCB for that, but you could also use individual Female-Female Dupont wires:

![IMG_0089](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/a459d1b5-8848-4b56-99bb-7780aaee2879)

If you want to be very carefull, you can decouple the other displays by disconnecting the left 6pin wire of the rightmost display.

in the picture you see at the left top a 7805 voltage regulator with 2x100nF decoupling capacitors. Directly below you see a buck converter to regulat the incoming voltage from the power supply. I have added that to reduce flickering in the Led displays due to the number of segments that are illuminated. You can start without that and at it when needed.In the right top you see the 3.5 mm entry to fit a DS18B20 temperature sensor.
Just above the display, in the middle, you see the wires towards the push buttons for the stopwatch function.

When everything works OK, you can add the optional temperature sensor and/or the optional stopwatch push buttons.

As a last activity: mount the backside to the picture frame. This can be done with an alluminum L-profile, or with L-shaped brackets, for example L form 2020, which should have m4 thread, but I received these with M5 thread. I drilled one side with a drill of 6.5 mm to be able to use a wood screw:

![IMG_0090](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/15e7f65d-7957-4ac2-8088-c239942cc328)
![IMG_0091 (2)](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/0ba314a6-bf45-4f83-8c4d-547fc7f18401)


