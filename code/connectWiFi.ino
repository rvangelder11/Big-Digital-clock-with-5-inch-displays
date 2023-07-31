void connectWiFi() {
  WiFi.mode(WIFI_STA);                  // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;                       // WiFiManager to start as AP to enter WiFi credentials
  wm.setCountry("nl");                  // default is china, they have other WiFi channels
  bool res = wm.autoConnect(HostName);  // open AP
  if (!res) {
    Serial.println("Failed to connect");
    WifiConnected = false;
    WiFi.mode(WIFI_AP);  //Set AccessPoint only
    delay(2000);
    Serial.println(WiFi.softAP(String(HostName) + "_AP") ? "Ready" : "Failed!");
    delay(250);
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
    
    if (!WifiConnected) state = 3;  //if there is no wificonnection, go to stopwatch reset mode
  } else {
    Serial.println("connected...yeey :)");  // if you get here you have connected to the WiFi
    delay(500);
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
    WifiConnected = true;
  }
}
