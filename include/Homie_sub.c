#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MQTT.h>


String DeviceAddress(String &DeviceID){

String DeviceAddress="homie/" + DeviceID;
return DeviceAddress;

}

void sendMessage(bool retain, String Topic, String Payload){




client.publish(Topic, Payload, retain,2);

} 


void subscribeTopic(String &Topic){
client.subscribe(Topic);

}



 String initHomie(String &DeviceType, String &DeviceID){
String Prefix="";

Prefix=DeviceAddress(DeviceID);


if (DeviceType=="STH"){

sendMessage(true, Prefix+ "/$homie","3.0.1");
sendMessage(true,Prefix + "/$name",DeviceID);
sendMessage(true,Prefix + "/$nodes","DHT22");
sendMessage(true,Prefix + "/$extensions","");
sendMessage(true,Prefix + "/$implementation","exp8266");
sendMessage(true,Prefix + "/$state","ready");

sendMessage(true,Prefix + "/DHT22/$name","DHT22");
sendMessage(true,Prefix + "/DHT22/$type","DHT22Sensor");
sendMessage(true,Prefix + "/DHT22/$properties","temperature,hygro,tempoffset,hygrooffset,location");

sendMessage(true,Prefix + "/DHT22/temperature/$name","Temp");
sendMessage(true,Prefix + "/DHT22/temperature/$unit","°C");
sendMessage(true,Prefix + "/DHT22/temperature/$datatype","float");

sendMessage(true,Prefix + "/DHT22/hygro/$name","Hygro");
sendMessage(true,Prefix + "/DHT22/hygro/$unit","%");
sendMessage(true,Prefix + "/DHT22/hygro/$datatype","float");

sendMessage(true,Prefix + "/DHT22/tempoffset/$name","TempOffset");
sendMessage(true,Prefix + "/DHT22/tempoffset/$datatype","float");
sendMessage(true,Prefix + "/DHT22/tempoffset/$retained","true");
sendMessage(true,Prefix + "/DHT22/tempoffset/$setable","true");


sendMessage(true,Prefix + "/DHT22/hygrooffset/$name","HygroOffset");
sendMessage(true,Prefix + "/DHT22/hygrooffset/$datatype","float");
sendMessage(true,Prefix + "/DHT22/hygrooffset/$retained","true");
sendMessage(true,Prefix + "/DHT22/hygrooffset/$setable","true");


sendMessage(true,Prefix + "/DHT22/sensorinterval/$name","SensorIntervall");
sendMessage(true,Prefix + "/DHT22/sensorinterval/$datatype","integer");
sendMessage(true,Prefix + "/DHT22/sensorinterval/$retained","true");
sendMessage(true,Prefix + "/DHT22/sensorinterval/$setable","true");


sendMessage(true,Prefix + "/DHT22/location/$name","Location");
sendMessage(true,Prefix + "/DHT22/location/$datatype","string");
sendMessage(true,Prefix + "/DHT22/location/$retained","true");
sendMessage(true,Prefix + "/DHT22/location/$setable","true");



subscribeTopic(Prefix + "/DHT22/tempoffset/set");
subscribeTopic(Prefix + "/DHT22/hygrooffset/set");
subscribeTopic(Prefix + "/DHT22/sensorinterval/set");
subscribeTopic(Prefix + "/DHT22/location/set");
}

return Prefix;
}

void SendValue(String &DeviceID, String NodeID, String Value){
String Prefix="";

Prefix=DeviceAddress(DeviceID);
Prefix = Prefix  + NodeID;
sendMessage(true,Prefix,Value);

}





