#include <Arduino.h>
#include <DHT_sub.c>
#include <Wifi_sub.c>
#include <ESP8266WiFi.h>
#include <MQTT.h>
#include <Homie_sub.c>





/* 
types:
Sensors:
STH = Sensor Thermo Hygro


Bridges:
BRC = Bridge Remote Controlled



 */
String DeviceType ="STH"; 
String DeviceID="";
String Prefix="";

unsigned long HomieInitInterval = 600000;

unsigned long SensorInterval=5000;
unsigned long lastSensorInterval=5000;
float tempOffset=0;
float lasttempOffset=0;
float hygroOffset=0;
float lasthygroOffset=0;
float akttemp=0;
float akthygro=0;

unsigned long lastValueSend = 0;
unsigned long lastHomieInit = 0;

String location="Undef";

  
void setup(){
Serial.begin(115200);
DeviceID=initWIFI(DeviceType);


initDHT22();
initSensorInterval(SensorInterval);


Prefix = initHomie(DeviceType,DeviceID);



}


void loop(){

struct Climate result;


if (SensorInterval != actSensorInterval()){
SensorInterval= actSensorInterval();
SendValue(DeviceID,"/DHT22/sensorintervall",String(SensorInterval) );
}


if(tempOffset != actTempOffset()){
  tempOffset = actTempOffset();
  SendValue(DeviceID,"/DHT22/tempoffset",String(tempOffset) );
  Serial.println("New TempOffset");
};

if(hygroOffset != actHygroOffset()){
  hygroOffset = actHygroOffset();
  SendValue(DeviceID,"/DHT22/hygrooffset",String(hygroOffset) );
};

if (location != actLocation()){
  location = actLocation();
  SendValue(DeviceID,"/DHT22/location",location );
}

if (millis() - lastValueSend > SensorInterval){
  Serial.println(WifiConnected());


  if (!WifiConnected()) {
    Serial.println("Not connected");
    connect(DeviceID);
  }

lastValueSend= millis();
result=climateData();

akttemp = result.temperature.toFloat();
akttemp += tempOffset;

akthygro = result.humidity.toFloat();
akthygro+=hygroOffset;



SendValue(DeviceID,"/DHT22/temperature",String(akttemp));
SendValue(DeviceID,"/DHT22/hygro",String(akthygro));
SendValue(DeviceID,"/DHT22/location",String(location));

Serial.print("Temp=");
Serial.println(String(akttemp));

Serial.print("Hygro=");
Serial.println(String(akthygro));


}

// if (millis() - lastHomieInit > HomieInitInterval){

// lastHomieInit= millis();

// initHomie(DeviceType,DeviceID);
// SendValue(DeviceID,"/DHT22/location",location );

// }
}







