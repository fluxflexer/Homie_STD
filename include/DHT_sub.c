#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2         //Pin2 <=> D4 on the NodeMCU
#define DHTTYPE DHT22    //Sensortype
DHT_Unified dht(DHTPIN, DHTTYPE); //initialize DHT22


float TempCalibration = 0;
float HygroCalibration  = 0;

sensor_t sensor;

struct Climate {    //Struct to hold the Climate Data
  String temperature;
  String humidity;
};

float temperature;
float humidity;



struct Climate climateData(){
    
struct Climate result;

sensors_event_t event;
dht.temperature().getEvent(&event);
result.temperature=event.temperature;

dht.humidity().getEvent(&event);
result.humidity=event.relative_humidity;

  return  result;

}

void initDHT22(){
dht.begin();


};