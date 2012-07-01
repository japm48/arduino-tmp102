
//This sketch prints to the serial port the content of all TMP102 registers.
//It also switches between 12-bit and extended 13-bit modes.


#include <Wire.h>
#include <tmp102.h>

const byte sensorAddress = 0x90;
tmp102 *thermometer = new tmp102(&Wire);

void setup()
{
  Serial.begin(9600); //USB
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  
  thermometer->init(sensorAddress);
  
  //Set default config.
  thermometer->writeConf(TMP102_DEFAULT_CONF);
}

void loop()
{
  int temperature = 0;
  
  if(thermometer->readTemp(temperature))
  {
    Serial.print(F("Temperature: "));
    Serial.println(temperature*0.0625);
  } else {
    Serial.println(F("Temp read failed!!"));
  }
  
  if(thermometer->getTLimit(true,temperature))
  {
    Serial.print(F("T_high: "));
    Serial.println(temperature*0.0625);
  } else {
    Serial.println(F("T_high read failed!!"));
  }
  
  if(thermometer->getTLimit(false,temperature))
  {
    Serial.print(F("T_Low: "));
    Serial.println(temperature*0.0625);
  } else {
    Serial.println(F("T_Low read failed!!"));
  }
  
  if(thermometer->readConf())
  {
    Tmp102ConfFormat conf;
    thermometer->getConf(conf);
    Serial.println(F("Conf read:"));
    printConf(conf);
  } else {
    Serial.println(F("Conf read failed!!"));
  }
  
  //Switch 12/13-bit mode.
  Tmp102ConfFormat conf;
  thermometer->getConf(conf);
  conf.extended13 = !conf.extended13;
  thermometer->writeConf(conf);
  
  //Wait half a second, to make the output readable.
  delay(500);
}


void printConf(Tmp102ConfFormat conf)
{
  Serial.print(F("  - OS: "));
  Serial.print(conf.oneShot, BIN);
  Serial.print(F("  - Ri: "));
  Serial.print(conf.resolution, BIN);
  Serial.print(F("  - Fi: "));
  Serial.print(conf.fault_queue, BIN);
  Serial.print(F(" - POL: "));
  Serial.print(conf.al_polarity, BIN);
  Serial.print(F(" - TM: "));
  Serial.print(conf.thermostat, BIN);
  Serial.print(F("  - SD: "));
  Serial.print(conf.shutdown_m, BIN);
  Serial.println(F(""));
  
  Serial.print(F("  - CRi: "));
  Serial.print(conf.conver_rate, BIN);
  Serial.print(F(" - A: "));
  Serial.print(conf.alert, BIN);
  Serial.print(F(" - EM: "));
  Serial.print(conf.extended13, BIN);
  Serial.print(F("  - Rsi: "));
  Serial.print(conf.reserved, BIN);
  Serial.println(F(""));
}

