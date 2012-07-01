TMP102 library for Arduino
=============
This is an Arduino library created to simplify the manipulation of the
Texas Instruments TMP102 Temperature Sensor connected to TWI/I2C ports (SCL and SDA).

This aims to help the use some features like:
* Switch to extended 13-bit mode.
* Shutdown mode and one-shot measure.
* Configure ALERT pin output.

Tested on an Arduino Leonardo board.

Installation and usage
----------------------

To install it, you just have to copy this to your libraries directory.

To use this in your sketch you have to add these lines:
    
    #include <Wire.h>
    #include <tmp102.h>

To start using the tmp102 class you can copy these lines:
  
    tmp102 TMP102(&Wire);
    
    //This assumes you have ADD0 tied to GND. If you want other address, consult the datasheet.
    const byte TMP102_ADDRESS = 0x90;
    
    void setup()
    {
      // ...
      TMP102.init(TMP102_ADDRESS);
      // ...
    }
  
  
