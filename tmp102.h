
#ifndef __LIB_TMP102_H__
#define __LIB_TMP102_H__

#include "Arduino.h"


//FIXME: I had terrible problems trying to include Wire.h so I had to make up 
//       this awful hack.
#ifdef __LIB_TMP102_TWI_AUX_HACK_
#include "twi_aux.inc"
#endif


//The fields must appear inverted.
typedef struct {
  //LSB
  byte reserved     : 4;
  bool extended13   : 1;
  bool alert        : 1;
  bool conver_rate  : 2;
  
  //MSB
  bool shutdown_m   : 1;
  bool thermostat   : 1;
  bool al_polarity  : 1;
  byte fault_queue  : 2;
  byte resolution   : 2;
  bool oneShot      : 1;
} Tmp102ConfFormat;


typedef union {Tmp102ConfFormat bf; uint16_t i;} Tmp102ConfFormatConverter;


class tmp102 {
  public:
    tmp102(TwoWire* Wire);
    ~tmp102();
    
    void init(byte address, bool loadconf = false);
    bool readTemp(int &iRead); //El valor devuelto hay que dividirlo entre 16.
    
    bool readConf();
    bool writeConf(Tmp102ConfFormat conf);
    void getConf(Tmp102ConfFormat &conf);
    
    bool getTLimit(bool T_high, int & data);
    bool setTLimit(bool T_high, int data);
    
    static int translateFromTmpFormat(int16_t tmp_f, bool ext13);
    //static int16_t translateToTmpFormat(int tmp_in, bool ext13);
    
  private:
    bool rawRead2(byte & data1, byte & data2);
    bool rawRead2(int16_t & data, bool reverse = false);
    bool selectRegister(byte reg, bool force = false);
    
    bool rawWrite2(int16_t data, bool reverse = false);
    
    byte currentRegPointer;
    byte address;
    TwoWire* Wire;
    
    Tmp102ConfFormat currConf;
    
};

const Tmp102ConfFormat TMP102_DEFAULT_CONF = {0,0,1,2,0,0,0,0,3,0};

#define TMP102_REG_TEMP   0
#define TMP102_REG_CONF   1
#define TMP102_REG_T_LOW  2
#define TMP102_REG_T_HIGH 3


#endif

