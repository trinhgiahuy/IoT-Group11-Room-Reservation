/*
  Web client

 This sketch connects to a website (http://www.reza.com)
 using a WiFi shield.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * WiFi shield attached

 created 30 March 2022
 by dlf (Metodo2 srl)
 modified 30 March 2022
 by Huy Trinh
 */


#include <SPI.h>
#include <WiFi101.h>
#include "arduino_secrets.h" 
#define PIR_MOTION_SENSOR 4 //Use pin D4 to receive the signal from the module
#define LED 7 //the Grove - LED is connected to D7 of Arduino


///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.reza.com";    // name address for Reza  (using DNS)

String PATH_NAME = "";

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() {

  //Get PIR sensor value
  
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(PIR_MOTION_SENSOR, INPUT);
  pinMode(LED, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  Serial.println("Checking for wifi hardware...");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  Serial.println("Wifi shield found!");

  // attempt to connect to WiFi network:
  Serial.println("Attempting to connect to Wifi network");
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");

    //Build data in questryString format (for GET request)
    //and additional other format: Json, XML, image(for POST request)
    int sensorValue = digitalRead(PIR_MOTION_SENSOR);
    String data = String(sensorValue);
    data = "?reserved=" + data;
    //data += "\r\n";
    /*
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();

    */

    
    Serial.println("Posting sensor data...");

    //TODO: Define phpScript"
    /*
    client.print("POST ");
    //client.print(phpScript);
    client.println(" HTTP/1.1");
    */

    //CODE FOR GET REQUEST METHOD
    client.print("GET " + PATH_NAME + data + " HTTP/1.1\n");
    client.println("Host: "+String(server));
    client.println("Connection: close");
    client.println(); //end HTTP header

    //CODE FOR GET POST METHOD
    //HTTP POST requests may change the server state.
    /*    
    client.print("GET " + PATH_NAME+ " HTTP/1.1\n");
    client.println("Host: "+String(server));
    client.println("Connection: close");
    client.println(); //end HTTP header

    //Send HTTP body
    client.println(data);
     */

    
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}


void printWiFiStatus() {
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
