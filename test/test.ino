// and the Grove LED Socket is connected to pin D4.

/*macro definitions of PIR motion sensor pin and LED pin*/
#define PIR_MOTION_SENSOR 4 //Use pin D4 to receive the signal from the module
#define LED 7 //the Grove - LED is connected to D7 of Arduino


void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    pinMode(PIR_MOTION_SENSOR, INPUT);
    pinMode(LED,OUTPUT);
}

void loop()
{
    if(isPeopleDetected())//if it detects the moving people?
    {
        digitalWrite(LED, HIGH);
        Serial.println("People detected");
        delay(1000);
    }
    else
    {
        Serial.println("NO People detected");
        digitalWrite(LED, LOW);
        delay(1000);
    }
}


/***************************************************************/
/*Function: Detect whether anyone moves in it's detecting range*/
/*Return:-boolean, true is someone detected.*/
boolean isPeopleDetected()
{
    int sensorValue = digitalRead(PIR_MOTION_SENSOR);
    Serial.println(sensorValue);
    if(sensorValue == HIGH)//if the sensor value is HIGH?
    { 
        Serial.println(sensorValue);
        return true;//yes,return true
    }
    else
    {
        Serial.println(sensorValue);
        return false;//no,return false
    }
}
