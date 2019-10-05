#include <Arduino.h>



unsigned long _SensorInterval;
unsigned long _HomieInitInterval;

float _tempOffset=0;
float _hygroOffset=0;

String _location ="Undef";


unsigned long actSensorInterval(){
return _SensorInterval;
}

float actTempOffset(){
return _tempOffset;
}

float actHygroOffset(){
return _hygroOffset;
}

String actLocation(){
return _location;
}

void initSensorInterval(unsigned long Sensorinterval){
_SensorInterval=Sensorinterval;

}



void processMessages(String &topic, String &payload){
Serial.println("incoming: " + topic + " - " + payload);

if(topic.indexOf("sensorinterval/set") > 0){
_SensorInterval = atol(payload.c_str());;


}

if(topic.indexOf("tempoffset/set") > 0){
_tempOffset = atof(payload.c_str());
Serial.print("Tempoffset set to_");
Serial.println(_tempOffset);
}

if(topic.indexOf("hygrooffset/set") > 0){
_hygroOffset = atof(payload.c_str());
}

if(topic.indexOf("location/set") > 0){
_location = payload.c_str();
}
}