#include <M5StickCPlus.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "arduino_secrets.h" 

#define PIR_GROVE_PIN 33
#define LED_PIN 10

#define LED_ON LOW
#define LED_OFF HIGH

#define CONNECTION_TIMEOUT 10

const char* ssid = "BumBeo";
const char* password = "38636300";
const char* server = "https://reza1234.free.beeceptor.com/update-sensor";
//IPAddress server(45,93,137,105); 
const char* PATH_NAME = "";



/* After M5StickC Plus is started or reset
  the program in the setUp () function will be run, and this part will only be run once.

*/
void setup(){
  M5.begin();             //Init M5StickC plus
  
  M5.Lcd.setRotation(3);
  WiFi.begin(ssid, password); //Connect wifi and return connection status. 
  Serial.println("Attempting to connect to Wifi network");
  int timeout_counter=0;
  while (WiFi.status() != WL_CONNECTED) { //If the wifi connection fails.
    /*      
    if(status == WL_DISCONNECTED){
      Serial.println("status = WL_DISCONNECTED");
    }
    Serial.print("Wifi.begin: ");
    Serial.println(status);
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    Serial.print("Wifi.status: ");
    Serial.println(WiFi.status());  
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    */
    delay(1000);
    M5.lcd.print(".");

    /*
    timeout_counter++;
    if(timeout_counter >= CONNECTION_TIMEOUT*10){
      Serial.println("Restarting ESP");
      ESP.restart();
    }
    */
    
  }
  Serial.println("Connected to wifi");
  //printWiFiStatus();

  //---------------------------------------- M5 part
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(20, 15);
  M5.Lcd.println("PIR motion test");
  M5.Lcd.setCursor(30, 30);
  M5.Lcd.println(" Person dected?");

  pinMode(PIR_GROVE_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);
  
  // check for the presence of the shield:
  Serial.println("Checking for wifi hardware...");
  /*
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  */
  //Serial.println("Wifi shield found!");

  //WiFi.mode(WIFI_STA);
  /*
  Serial.println("\nStarting connection to server...");
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
  */
}

void loop(){
  //static float tmp = 0;
  int motionVal = digitalRead(PIR_GROVE_PIN);
  
  if(motionVal)
    digitalWrite(LED_PIN,LED_ON);
  else
    digitalWrite(LED_PIN,LED_OFF);
  
  M5.Lcd.setCursor(80, 60);
  M5.Lcd.printf("%3d",motionVal);

  //--------------------Client code
  HTTPClient http;
  String data = String(motionVal);
  data = "?reserved=" + data;
  String serverPath = server + data;      //https://reza1234.free.beeceptor.com/update-sensor?reserved=1
  
  //Serial.println("http.begin(serverPath.cstr())");
  http.begin(serverPath.c_str());
  
  // Send HTTP GET request
  Serial.println("Send GET sensor data...");
  int httpResponseCode = http.GET();
  
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
  }
      // Free resources
      http.end();
      /*
  client.print("GET " + PATH_NAME + data + " HTTP/1.1\n");
  client.println("Host: "+String(server));
  client.println("Connection: close");
  client.println();
  */
  
  delay(1000);         //Delay 1s
}

void printWiFiStatus(){
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
