#include "Arduino.h"
#include "Streaming.h"
#ifndef ARDUINO_SAM_DUE
#include <EEPROM.h>
#endif
#include "SavedVariable.h"
#include "ConstantVariable.h"

const int BAUDRATE = 9600;

const int EEPROM_INITIALIZED_VALUE = 99;
CONSTANT_STRING(constant_string,"AbCdEfG");
ConstantString * const CONSTANT_STRING_PTR_DEFAULT = &constant_string;

void setup()
{
  while (!Serial);

  Serial.begin(BAUDRATE);
  Serial.flush();

  SavedVariable eeprom_initialized_sv(EEPROM_INITIALIZED_VALUE);

  SavedVariable constant_string_ptr_sv(CONSTANT_STRING_PTR_DEFAULT);

  for (int i=0;i<2;++i)
  {
    int eeprom_initial_value;
    eeprom_initialized_sv.getValue(eeprom_initial_value);
    Serial << "eeprom_intial_value = " << eeprom_initial_value << " should be = " << EEPROM_INITIALIZED_VALUE << endl;
    if (eeprom_initial_value != EEPROM_INITIALIZED_VALUE)
    {
      Serial << "Default values set for the first time!" << endl;
      eeprom_initialized_sv.setDefaultValue();
      constant_string_ptr_sv.setDefaultValue();
    }
    else
    {
      Serial << "Default values already set!" << endl;
    }

    ConstantString *constant_string_ptr;
    constant_string_ptr_sv.getValue(constant_string_ptr);
    Serial << "constant_string_ptr_sv.getSize() = " << constant_string_ptr_sv.getSize() << endl;
    Serial << "constant_string_value = " << *constant_string_ptr << " should be = " << constant_string << endl;

    Serial << endl;

    delay(4000);
  }
}


void loop()
{
}
