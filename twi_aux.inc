
#ifndef __LIB_TMP102_TWIAUX_H__

#define __LIB_TMP102_TWIAUX_H__

class TwoWire {
public:
  TwoWire();
  void begin();
  void begin(uint8_t);
  void begin(int);
  void beginTransmission(uint8_t);
  void beginTransmission(int);
  uint8_t endTransmission(void);
  uint8_t endTransmission(uint8_t);
  uint8_t requestFrom(uint8_t, uint8_t);
  uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
  uint8_t requestFrom(int, int);
  uint8_t requestFrom(int, int, int);
  
  size_t write(uint8_t);
  size_t write(const uint8_t *, size_t);
  int available(void);
  int read(void);
  int peek(void);
  void flush();
  
  
  int getWriteError();
  void clearWriteError();
  size_t write(const char *str);
  
  size_t print(const __FlashStringHelper *);
  size_t print(const String &);
  size_t print(const char[]);
  size_t print(char);
  size_t print(unsigned char, int = DEC);
  size_t print(int, int = DEC);
  size_t print(unsigned int, int = DEC);
  size_t print(long, int = DEC);
  size_t print(unsigned long, int = DEC);
  size_t print(double, int = 2);
  size_t print(const Printable&);
  size_t println(const __FlashStringHelper *);
  size_t println(const String &s);
  size_t println(const char[]);
  size_t println(char);
  size_t println(unsigned char, int = DEC);
  size_t println(int, int = DEC);
  size_t println(unsigned int, int = DEC);
  size_t println(long, int = DEC);
  size_t println(unsigned long, int = DEC);
  size_t println(double, int = 2);
  size_t println(const Printable&);
  size_t println(void);
};

#endif
