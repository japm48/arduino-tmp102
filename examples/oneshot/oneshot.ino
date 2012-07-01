
//This sketch shows an example of how to use the "ONE-SHOT/CONVERSION READY" feature
//to minimize the sensor power consumption.

#include <Wire.h>
#include <tmp102.h>

//Assuming ADDR0 -> GND. Change this if you needed.
const byte sensorAddress = 0x90;

//Our tmp102 object.
tmp102 *thermometer = new tmp102(&Wire);


Tmp102ConfFormat conf;

void setup()
{
  Serial.begin(9600); //USB
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  //Read configuration and put the sensor in shutdown mode.
  thermometer->init(sensorAddress);
  thermometer->readConf();
  
  thermometer->getConf(conf);
  conf.shutdown_m = true;
  thermometer->writeConf(conf);
  
  conf.oneShot = true;
}

int temperature = 0;

void loop()
{
  thermometer->writeConf(conf);
  
  if(thermometer->readTemp(temperature))
  {
    Serial.print(F("Temperature: "));
    Serial.println(temperature*0.0625);
  } else {
    Serial.println(F("Temp read failed!!"));
  }
  
  //Uncomment this to re-check the configuration.
  /*
  if(thermometer->readConf())
  {
    Tmp102ConfFormat conf;
    thermometer->getConf(conf);
    Serial.print(F("  - OS: "));
    Serial.print(conf.oneShot, BIN); // MUST read always as 0.
    Serial.print(F("  - SD: "));
    Serial.println(conf.shutdown_m, BIN);
  } else {
    Serial.println(F("Conf read failed!!"));
  }
  //*/
  
  
  delay(500);
}


