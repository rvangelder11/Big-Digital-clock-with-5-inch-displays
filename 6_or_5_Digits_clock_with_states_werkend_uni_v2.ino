/* This program is used in combination with a number of large displays. This is indicated in Nr_Displays
    It has multiple states:
    All states can be set via the webpage that can be found on <HostName>.local. Its IP is shown in the serial terminal
    0 = clock function, 24 hours, connected via NTP and selected in the countries Timezone
    1 = Countdown to the time as stored in CountDownTimeTo.
    2 = Countdown from a time as stored in CountDownFrom.
    3 = resetfunction for the stopwatch function. Time is set to zero.
    4 = Stopwatch run, Stopwatch runs and shows the time.
    5 = Stopwatch keeps running in the background, but laptime is shown still. Each time this is selected, the new laptime is shown

It gets input from a webpage:
Input1 = time in hh:mm:ss to countdown from
Input2 = time in hh:mm:ss to countdown to
Input3 = Start stopwatch
Input4 = Show laptime on stopwatch
Input5 = Reset stopwatch
Input6 = show clock

There are currently three CLOCKTYPES:
a 5 inch 6 Digits clock, named 6Digitsclock
a 4 inch 5 digits clock with stopwatsch buttons, named 5Digitsclock
a 6 Digits clock with minitrons, called Minitronclock

CLOCKTYPE, hostname and number of displays need to be set in 3 #define statement indicated below
*/
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ezTime.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESPAsyncTCP.h>
#define WEBSERVER_H
#include <ESPAsyncWebServer.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>        // Include the mDNS library
#include <OneWire.h>            // needed for one wire sensors
#include <DallasTemperature.h>  // needed for DS18x20 sensors (which is a one wire sensor)
#define TEMPERATURE_PRECISION 12
#define TEMP_SENSOR_PIN 0  // optional temperature sensors are on D3, which is pin 0
//=======fill in specs here=====
#define MINITRON                      // choose MINITRON or LED
#define HOSTNAME "minitronclock"  // choose hostname and OTA name
#define NR_DISPLAYS 6            // enter number of displays here
//==================================================================
#ifdef MINITRON                                                                                                                                                                                                    // minitron PCB works with inserse logic.
const byte seg[] = { B11000000, B11111001, B10100100, B10110000, B10011001, B10010010, B10000010, B11111000, B10000000, B10010000, B11111111, B10011110, B10001100, B10011111, B10111111, B11000110, B10011100 };  // 7-segment patterns for 0 to 9; 10th elm  = space, letters t,r,e kloppen niet, daarna C, degree symbol; order: dp gfedcba;                           // define the array of segmentpatterns
const byte dp = B10000000;                                                                                                                                                                                         //decimal point
#else
const byte seg[] = { B1111011, B1100000, B1011101, B1110101, B1100110, B0110111, B0111111, B1100001, B1111111, B1110111, B0000000, B0011110, B0001100, B0011111, B0000100, B0011011, B1000111 };  // 7-segment patterns for 0 to 9; 10th elm  = space, rest is the letters t,r,e, C, degree symbol; order: dp bcdegfa
const byte dp = B10000000;                                                                                                                                                                        //decimal point
#endif
//GPIO declarations Adapted for ESP8266
//--------------------------------
boolean TemperatureSensor = false;
boolean WifiConnected = false;
const byte segmentClock = D6;  // volgorde aangepast aan PCB ontwerp
const byte segmentLatch = D7;
const byte segmentData = D5;


const long hour_ms = 3600000;  // 3600000 milliseconds in an hour
const long minute_ms = 60000;  // 60000 milliseconds in a minute
const long second_ms = 1000;   // 1000 milliseconds in a second

char* HostName;
byte Nr_Displays = NR_DISPLAYS;                          // need it in a variable
AsyncWebServer server(80);                               // Create AsyncWebServer object on port 8080
const char* PARAM_INPUT_1 = "input1";                    // 1st message from GET
const char* PARAM_INPUT_2 = "input2";                    // 2nd message from GET
const char* PARAM_INPUT_3 = "input3";                    // 3rd message from GET
const char* PARAM_INPUT_4 = "input4";                    // 4th message from GET
const char* PARAM_INPUT_5 = "input5";                    // 5th message from GET
const char* PARAM_INPUT_6 = "input6";                    // 6th message from GET
long CountDownTime, CountDownTimeFrom, CountDownTimeTo;  // contains the startvalue of the countdowntimer
int state = 0;                                           //contains the state of the clock
int secs = 0;
int oneWireCount = 0;
unsigned long millis_since_start;  // millis() is used to count the time. This value contains the start value (t = 0 on the stopwatch)
Timezone myTZ;
int TimeNumber;
boolean lapstate = false;
OneWire oneWire(TEMP_SENSOR_PIN);         // Set up a OneWire instance to communicate with OneWire devices
DallasTemperature tempSensors(&oneWire);  // Create an instance of the temperature sensor class



// HTML web page to handle 1 input field (input1)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Count Down Timer</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    countdownFrom time: <input type="time" name="input1" step = "1" value = "00:00:00"><br>
    countdownTo time: <input type="time" name="input2" step = "1" value = "00:00:00">
    <input type="submit" value="Submit"><br>
    <input type="radio" id="start" name="input3" value="Start">
  <label for="start">Start</label><br>
  <input type="radio" id="laptime" name="input4" value="Laptime">
  <label for="laptime">Lap Time</label><br>
  <input type="radio" id="reset" name="input5" value="Reset">
  <label for="reset">reset</label><br>
  <input type="radio" id="clock" name="input6" value="Clock">
  <label for="clock">clock</label><br><br>
  <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

//--------------------------------------------------
void setup() {
  
  HostName = HOSTNAME;
  pinMode(D2, INPUT);  // pushbutton for reset
  pinMode(D1, INPUT);  // pushbutton for lap
  pinMode(D4, INPUT);  // pushbutton for start
  // define pins for serial connection with shift registers
  pinMode(segmentClock, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(segmentLatch, OUTPUT);
  digitalWrite(segmentClock, LOW);
  digitalWrite(segmentData, LOW);
  digitalWrite(segmentLatch, LOW);
  showNumber(888888, false);  // test all segments. This will remain visible until WiFi connection has been made
  Serial.begin(115200);
  Serial.println();
  delay(5000);
  if (digitalRead(D4) != 0) {  // if Reset is pushed at the start, no connection will be made to Wifi
    Serial.print("Connecting");
    //ESP.eraseConfig();  // enable to erase all Wifi info, disable when done
    connectWiFi();  // start WiFi connection brings up an A/P on 192.168.4.1 on accesspoint with the name as set in  <HostName>
    delay(200);
    if (WifiConnected) {
      Serial.println("Wait for time sync");  // for accurate clock:
      showNumber(0, false);                  // means waiting for timesync
      //delay(500);
      millis_since_start = millis();
      while (!waitForSync(20)) Serial.println("Reconnecting...");
      Serial.println("time synced");
      Serial.print("it took: ");
      unsigned long delta = millis() - millis_since_start;
      Serial.print(delta);
      Serial.println(" ms");
      Serial.println(myTZ.dateTime("H:i:s"));
      //if (!myTZ.setCache(0))
      myTZ.setLocation(F("NL"));  // set to Dutch time incl DST

      if (!MDNS.begin(HostName)) {  // Start the mDNS responder for <HostName>.local
        Serial.println("Error setting up MDNS responder!");
      }
      Serial.println("mDNS responder started");
      Serial.println(HostName);
      ArduinoOTA.setHostname(HostName);  // give the OTA port an understandable name
      ArduinoOTA.begin();                // enable OTA for easy update via WiFi

      // Send web page with input fields to client
      server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send_P(200, "text/html", index_html);  // send get request
      });

      // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
      server.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
        String inputMessage1, inputMessage2, inputMessage3, inputMessage4, inputMessage5, inputMessage6;  // expect 6 input messages from the client

        // check for each parameter

        if (request->hasParam(PARAM_INPUT_1)) {                       // If inputparameter 1 was returned, do:
          inputMessage1 = request->getParam(PARAM_INPUT_1)->value();  // read first parameter from get time as a string hh:mm:ss
          Serial.println(inputMessage1);
          int Hr = inputMessage1.substring(0, 2).toInt();   // filter out the hours
          int Min = inputMessage1.substring(3, 5).toInt();  // filter out the minutes
          int Sec = inputMessage1.substring(6, 8).toInt();  // filter out the seconds
          CountDownTimeTo = Hr * 3600 + Min * 60 + Sec;     // convert to seconds
          if (CountDownTimeTo > 0) {
            state = 1;
            CountDownTime = CountDownTimeTo;
            secs = 0;
            Serial.println(CountDownTime);
          }
        }

        if (request->hasParam(PARAM_INPUT_2)) {                       // If inputparameter 2 was returned, do:
          inputMessage2 = request->getParam(PARAM_INPUT_2)->value();  // read first parameter from get time as a string hh:mm:ss
          Serial.println(inputMessage2);
          int Hr = inputMessage2.substring(0, 2).toInt();   // filter out the hours
          int Min = inputMessage2.substring(3, 5).toInt();  // filter out the minutes
          int Sec = inputMessage2.substring(6, 8).toInt();  // filter out the seconds
          CountDownTimeFrom = Hr * 3600 + Min * 60 + Sec;   // convert to seconds
          if (CountDownTimeFrom != 0) {
            state = 2;
            Hr -= myTZ.hour();  // substract current hours
            Min -= myTZ.minute();
            Sec -= myTZ.second();
            CountDownTime = Hr * 3600 + Min * 60 + Sec;  // convert to seconds
          }
        }

        if (request->hasParam(PARAM_INPUT_3)) {                       // If inputparameter 3 was returned, do:
          inputMessage3 = request->getParam(PARAM_INPUT_3)->value();  // read startstop
          Serial.println(inputMessage3);
          if (inputMessage3 == "Start") state = 4;
        }

        if (request->hasParam(PARAM_INPUT_4)) {                       // If inputparameter 4 was returned, do:
          inputMessage4 = request->getParam(PARAM_INPUT_4)->value();  // read laptime
          Serial.println(inputMessage4);
          if (inputMessage4 == "Laptime") {
            state = 5;
            showNumber(TimeNumber, false);
            Serial.println(TimeNumber);
          }
        }

        if (request->hasParam(PARAM_INPUT_5)) {                       // If inputparameter 4 was returned, do:
          inputMessage5 = request->getParam(PARAM_INPUT_5)->value();  // read reset
          Serial.println(inputMessage5);
          if (inputMessage5 == "Reset") {
            state = 3;
            secs = 0;
          }
        }

        if (request->hasParam(PARAM_INPUT_6)) {                       // If inputparameter 4 was returned, do:
          inputMessage6 = request->getParam(PARAM_INPUT_6)->value();  // read reset
          Serial.println(inputMessage6);
          if (inputMessage6 == "Clock") state = 0;
        }
        request->send(200, "text/html", "HTTP GET request sent to your ESP with messagefields 1 to 6: <br>" + inputMessage1 + "<br>" + inputMessage2 + "<br>" + inputMessage3 + "<br>" + inputMessage4 + "<br>" + inputMessage5 + "<br>" + inputMessage6 + "<br>" + CountDownTime + "<br><a href=\"/\">Return to Home Page</a>");  // answer from webpage
      });
      server.onNotFound(notFound);  // error handling
      server.begin();               // initialize connection
    }
  }
  millis_since_start = millis();                                                        // reset timer to 0 at the beginning
  showNumber(0, true);                                                                  // show the number 0 on the display
  tempSensors.begin();                                                                  // start temperature sensor
  oneWireCount = tempSensors.getDeviceCount();                                          // find the number of connected sensors
  Serial.println(" There are: " + String(oneWireCount) + " temperaturesensors found");  // check whether a temperature sensor has been detected
  TemperatureSensor = (oneWireCount != 0) ? true : false;
}

//--------------------------------------------

time_t Startsec;
int secOld, secNow;
unsigned long Start_ms = millis();

void loop() {
  events();  // to enable syncing
  if (WifiConnected) secNow = myTZ.second();

  if (timeStatus() != 2) Serial.print("Time is not synced!");
  if (digitalRead(D2) == 0 and state >= 4) {
    showNumber(TimeNumber, false);
    Serial.println(TimeNumber);
    state = 5;
    Serial.println("state = 5");
  }
  if (digitalRead(D1) == 0 and state >= 3) {
    state = 4;
    Serial.println("state = 4");
  }
  if (digitalRead(D4) == 0) {
    state = 3;
    Serial.println("state = 3");
  }
  switch (state) {
    Serial.print("huidige state is: ");
    Serial.println(state);

    case 0:
      if (secNow != secOld) {
        showClock();
        if (secNow % 30 == 0 && TemperatureSensor) showTemperature();
        secOld = secNow;
      }
      break;
    case 1:                         // count from set time down to zero
      if (secs != CountDownTime) {  // if a new CountDown time has been entered do:
        secs = CountDownTime;       // set the new countdown time
        Startsec = now();
      }
      if (millis() >= Start_ms + 1000) {
        Start_ms = millis();
        CountDownFunction();
      }
      break;
    case 2:                         // count down to set time
      if (secs != CountDownTime) {  // if a new CountDown time has been entered do:
        secs = CountDownTime;       // set the new countdown time
        Startsec = now();
      }
      if (millis() >= Start_ms + 1000) {
        Start_ms = millis();
        CountDownFunction();
      }
      break;
    case 3:                           // reset stopwatch
      millis_since_start = millis();  // stopwatch needs to be set to zero by taking a new offset compared to the number of ms since the start of the arduino
      showNumber(0, false);
      break;
    case 4:
      StopWatchFunction();
      break;
    case 5:
      StopWatchFunction();
      break;
  }
}
