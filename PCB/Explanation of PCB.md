The ESP8266 module can be directly connected to the 7 segment displays as explained in the Assembly Instructions, however, it is possible to use a dedicated PCCB for this. I ordered 5 of them at <https://jlcpcb.com/> for only 2 dollars and a few dollars shipping cost and I received them within a few weeks.

![PCB_Layout](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/15401b4d-0a4d-47fe-b95f-9bd33685a60c)

Minimally you need to install:
- 2x8 female headers for the ESP8266 (assuming that you installed the male part on the ESP8266).
- U3 7805 and its two decoupling capacitors C1 and C2, each 100 nF to produce 5V for the ESP8266.
- R4, R5 and R6 pull up resistors of 10k, even if you do not install the stopwatch push buttons. (You could leave out R4, because the D4 input has an internal pull-up).
- I recommend mounting the 6 pin header U1 and the power input connector DC2, but you could omit this by directly soldering the wires to the PCB.
- With the power supply I used, I found that the brightness of the display varied depending on the number of segments that were illuminated. therefor I added the buck converter LM2596. If you have a very stable power supply, you might not need this. You can then solder a wire between GND in and out and between Vin and VCC. If you install a buck converter, make sure to set it on the right output voltage. For 4 inch displays around 9V, for 5 inch displays around 10,5 V.
- If you want to show the temperature, you need to install J1. You can then connect a DS18B20 via a 3.5 mm plug. The DS18B20 signal wire (yellow) goes to the tip of the connector, VCC (red) to the ring and Gnd (black) to the sleeve
  
![TRS-Pinout](https://github.com/rvangelder11/Big-Digital-clock-with-5-inch-displays/assets/90907092/004c4dec-6084-4cdd-8022-9772c7394c51)
