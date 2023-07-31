The software is written for the Arduino IDE, but can probaly also used in other environments bij changing .ino in .cpp.
The code is split in parts for easy maintenance. All files need to be in the same folder. The main program is 6_or_5_Digits_clock_with_states_werkend_uni_v2.ino. If that file is opened, the other modules will be loaded (when the Arduino IDE is used)
The module 6_or_5_Digits_clock_with_states_werkend_uni_v2.ino contains a few lines that might need changing, depending on the location and the number of displays used:
Line 41 should read LED. (I have a Minitron clock, but I don't think anybody else will have that. The minitron clock works with negative logic for the displays and the segments are differenly wired, hence I have include lines 45 upto 48)
Line 42 defines the hostname as used in the Arduino OTA and on the local network. This can by anything you like.
Line 43 needs to indicate how many displays are in use.
Line 127 enables the stopwatch function without connection to the internet, by keeping the puhbutton on D4 pushed for more than 5 seconds at the beginning.
Line 145 sets the loaction to NL. This can be changed to any choice as indicated at <https://en.wikipedia.org/wiki/List_of_tz_database_time_zones>.
Further details of the timing functions can be found at <https://github.com/ropg/ezTime>
