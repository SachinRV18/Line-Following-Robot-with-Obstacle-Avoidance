#include <ESP8266WiFi.h>;

#include <WiFiClient.h>;

#include <ThingSpeak.h>;

const char* ssid = "Nish"; //Your Network SSID

const char* password = "12345678"; //Your Network Password

WiFiClient client;

unsigned long myChannelNumber = 2038673; //Your Channel Number (Without Brackets)

const char * myWriteAPIKey = "P9YIGFAU48HHO59D"; //Your Write API Key

int alldata1;
String data;



void setup() {

WiFi.begin(ssid, password);

ThingSpeak.begin(client);
// Open serial communications and wait for port to open:
Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over
if (Serial.available()) {
Serial.write(Serial.read());
 alldata1= Serial.read();

}
if(alldata1 < 25)
{
  data = "Stop";
}


ThingSpeak.writeField(myChannelNumber, 1, alldata1, myWriteAPIKey); //Update in ThingSpeak
ThingSpeak.writeField(myChannelNumber, 2, data, myWriteAPIKey); //Update in ThingSpeak


}
