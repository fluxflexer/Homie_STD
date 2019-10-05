#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MQTT.h>
#include <logic_sub.c>


WiFiClient net;
MQTTClient client;

const char wlanssid[] = "wlan6_2";
const char wlanpass[] = "c000c888c000";
const char MQTTusername[] = "homehub";
const char MQTTpass[] = "mos6510";
const char MQTTserver[]="192.168.1.200";
char ClientName[] = "NodeMCU";



boolean WifiConnected(){

return client.connected();

}




void messageReceived(String &topic, String &payload) {
  
  processMessages(topic,payload);
}






void connect(String DeviceID) {

const char *ClientName = DeviceID.c_str();


  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nWIFI connected!\nconnecting MQTT...");
  



  while (!client.connect(ClientName, MQTTusername, MQTTpass)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nMQTT connected!");

client.subscribe("/hello");

}



String initWIFI(String DeviceType){
 
 String DeviceID ="";

  WiFi.begin(wlanssid, wlanpass);


  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin(MQTTserver, net);
  client.onMessage(messageReceived);


 
String Shortmac = DeviceID=WiFi.macAddress().substring(9);
Shortmac.replace(":","");
  DeviceID=DeviceType+Shortmac;
connect(DeviceID); 

return DeviceID;

}