
#define __LIB_TMP102_TWI_AUX_HACK_
#include "tmp102.h"

tmp102::tmp102(TwoWire *Wire)
{
  currentRegPointer = 0;
  this->Wire = Wire;
  currConf = TMP102_DEFAULT_CONF;
}

tmp102::~tmp102()
{
  ;
}

void tmp102::init(byte address, bool loadconf)
{
  this->address = (address >> 1);
  Wire->begin();
  currentRegPointer = 0;
  if(loadconf)
  {
    readConf();
  }
}


bool tmp102::readConf()
{
  if(!selectRegister(TMP102_REG_CONF)) return false;
  
  int16_t tmp;
	if(!rawRead2(tmp))
  {
    return false;
  }
  Tmp102ConfFormatConverter conv;
  conv.i = tmp;
  currConf = conv.bf;
  return true;
}

bool tmp102::writeConf(Tmp102ConfFormat conf)
{
  if(!selectRegister(TMP102_REG_CONF)) return false;
  
  Tmp102ConfFormatConverter conv;
  conv.bf = conf;
  
  
  Wire->beginTransmission(address);
  Wire->write(TMP102_REG_CONF);
  Wire->write( (uint8_t) ( ((conv.i) >> 8) & 0xff ) );
  Wire->write( (uint8_t) ( (conv.i) & 0xff ) );
  Wire->endTransmission();
  //TODO: check bytes written.
  
  currConf = conf;
  return true;
}

void tmp102::getConf(Tmp102ConfFormat &conf)
{
  conf = currConf;
}



bool tmp102::getTLimit(bool T_high, int & data)
{
  if(T_high) { if(!selectRegister(TMP102_REG_T_HIGH)) return false; }
  else       { if(!selectRegister(TMP102_REG_T_LOW)) return false; }
  
  
  int16_t tmp;
	if(!rawRead2(tmp))
  {
    return false;
  }
  
  data = translateFromTmpFormat(tmp, currConf.extended13);
  
  return true;
  
}


bool tmp102::setTLimit(bool T_high, int data)
{
  
  Wire->beginTransmission(address);
  
  if(T_high) { Wire->write(TMP102_REG_T_HIGH); }
  else       { Wire->write(TMP102_REG_T_LOW);  }
  
  Wire->write( (uint8_t) ( ((data) >> 8) & 0xff ) );
  Wire->write( (uint8_t) ( (data) & 0xff ) );
  Wire->endTransmission();
  
  //TODO: check bytes written.
  
  return true;
}



bool tmp102::readTemp(int &iRead)
{
  
  if(!selectRegister(TMP102_REG_TEMP)) return false;
  
  int16_t tmp;
	if(!rawRead2(tmp))
  {
    return false;
  }
  
  iRead = translateFromTmpFormat(tmp, currConf.extended13);
  
  return true;
  
}


bool tmp102::selectRegister(byte reg, bool force)
{
  if( (uint8_t)reg < (uint8_t)4 )
  {
    if(currentRegPointer == reg && !force) return true;
    
    Wire->beginTransmission(address);
    if(Wire->write((uint8_t)reg) != 1) { Wire->endTransmission(); return false; }
    Wire->endTransmission();
    
    currentRegPointer = reg;
    return true;
  }
  
  return false;
  
}

bool tmp102::rawRead2(int16_t & data, bool reverse)
{
  byte msb, lsb;
  
  if(!rawRead2(msb, lsb))
  {
    return false;
  }
  
  if(!reverse)
  {
    data = (msb<<8) | lsb;
  } else {
    data = (lsb<<8) | msb;
  }
  return true;
}

bool tmp102::rawRead2(byte & data1, byte & data2)
{
  Wire->requestFrom( (uint8_t)address , (uint8_t)2);
  if (2 >= Wire->available())
  {
    data1 = Wire->read();
    data2 = Wire->read();
    return true;
  }
  return false;
}

    
int tmp102::translateFromTmpFormat(int16_t tmp, bool ext13)
{
  int iRead;
  if(!ext13)
	{
	  tmp >>= 4;
    if(tmp & (1<<(12-1) ) )
    {
      iRead = - ((int) (tmp ^ (1<<(12-1))) );
    } else {
      iRead = tmp;
    }
  } else {
    tmp >>= 3;
    if(tmp & (1<<(13-1) ) )
    {
        iRead = - ((int) (tmp ^ (1<<(13-1))) );
    } else {
      iRead = tmp;
    }
  }
  
  return iRead;
}


/*
int16_t tmp102::translateToTmpFormat(int tmp_in, bool ext13)
{
  return 0;
}
*/

