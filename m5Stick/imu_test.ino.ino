#include <M5StickCPlus.h>
#define PIR_GROVE_PIN 33
#define LED_PIN 10

#define LED_ON LOW
#define LED_OFF HIGH

/* After M5StickC Plus is started or reset
  the program in the setUp () function will be run, and this part will only be run once.

*/
void setup(){
  M5.begin();             //Init M5StickC plus
  Serial.begin(9600);
  
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(20, 15);
  M5.Lcd.println("PIR motion test");
  M5.Lcd.setCursor(30, 30);
  M5.Lcd.println(" Person dected?");

  pinMode(PIR_GROVE_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);
  
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
  delay(1000);         //Delay 1s
}
