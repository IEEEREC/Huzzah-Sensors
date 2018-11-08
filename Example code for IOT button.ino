// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "ssid";
char wifiPassword[] = "pass";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "Mqtt Username";
char password[] = "Mqtt Password";
char clientID[] = "Mqtt clientID";

unsigned long lastMillis = 0;
static int uptime;

byte nuidPICC[4];
int tagToCompare;

void setup() {
	Serial.begin(115200);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(0,OUTPUT);


  nuidPICC[0] = 0xB5;
  nuidPICC[1] = 0xB6;
  nuidPICC[2] = 0xB7;
  nuidPICC[3] = 0xB8;
  
  tagToCompare = nuidPICC[0] + nuidPICC[1] + nuidPICC[2] + nuidPICC[3];
}

void loop() {
	Cayenne.loop();
 
  if(millis() - lastMillis > 2500) {
    lastMillis = millis();
    uptime = uptime + 2.5;
    

    // Publish the TMP36 temperature data to Cayenne on Channel 0.
    
    Cayenne.virtualWrite(7, tagToCompare);
    Cayenne.virtualWrite(0, uptime);
  }
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
	// Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
	// Cayenne.virtualWrite(0, millis());
	// Some examples of other functions you can use to send data.
	//Cayenne.celsiusWrite(1, 22.0);
	//Cayenne.luxWrite(2, 700);
	//Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

CAYENNE_IN(V5){
  int buttonstate = !(getValue.asInt());
    Serial.println(buttonstate);
  digitalWrite (0,buttonstate);
}
