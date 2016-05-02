#include "Arduino.h"
#include "Streaming.h"
#include "Flash.h"
#include "ConstantVariable.h"
#ifndef ARDUINO_SAM_DUE
#include <EEPROM.h>
#endif
#include "SavedVariable.h"

const int BAUDRATE = 9600;

CONSTANT_STRING(eeprom_initialized,"eeprom_initialized");
CONSTANT_STRING(one_d_array,"one_d_array");
CONSTANT_STRING(one_d_array_doubled,"one_d_array_doubled");

const int EEPROM_INITIALIZED_VALUE = 44;

const int ONE_D_ARRAY_ELEMENT_COUNT = 4;
const int ONE_D_ARRAY_DEFAULT_VALUE[ONE_D_ARRAY_ELEMENT_COUNT] = {10,11,12,13};

void setup()
{
  while (!Serial);

  Serial.begin(BAUDRATE);
  Serial.flush();

  int eeprom_index = 0;

  SavedVariable eeprom_initialized_sv(eeprom_initialized,
                                      eeprom_index,
                                      EEPROM_INITIALIZED_VALUE);
  eeprom_index += eeprom_initialized_sv.getSize();

  SavedVariable one_d_array_sv(one_d_array,
                               eeprom_index,
                               ONE_D_ARRAY_DEFAULT_VALUE,
                               ONE_D_ARRAY_ELEMENT_COUNT);
  eeprom_index += one_d_array_sv.getSize();

  SavedVariable one_d_array_doubled_sv(one_d_array,
                                       eeprom_index,
                                       ONE_D_ARRAY_DEFAULT_VALUE,
                                       ONE_D_ARRAY_ELEMENT_COUNT);
  eeprom_index += one_d_array_sv.getSize();

  for (int i=0;i<2;++i)
  {
    int eeprom_initial_value;
    eeprom_initialized_sv.getValue(eeprom_initial_value);
    Serial << "eeprom_intial_value = " << eeprom_initial_value << " should be = " << EEPROM_INITIALIZED_VALUE << endl;
    if (eeprom_initial_value != EEPROM_INITIALIZED_VALUE)
    {
      Serial << "Default values set for the first time!" << endl;
      eeprom_initialized_sv.setDefaultValue();
      one_d_array_sv.setDefaultValue();
    }
    else
    {
      Serial << "Default values already set!" << endl;
    }

    int one_d_array_value[ONE_D_ARRAY_ELEMENT_COUNT];
    Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      one_d_array_sv.getValue(one_d_array_value,i);
      if (i == 0)
      {
        Serial << "one_d_array_value[" << i << "] = " << one_d_array_value[i] << " should be >= " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
      }
      else
      {
        Serial << "one_d_array_value[" << i << "] = " << one_d_array_value[i] << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
      }
    }

    int one_d_array_value_copied[ONE_D_ARRAY_ELEMENT_COUNT];
    int bytes_copied = one_d_array_sv.getValue(one_d_array_value_copied);
    Serial << "bytes copied = " << bytes_copied << "\n";
    Serial << "one_d_array_value_copied = [";
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << one_d_array_value_copied[i];
    }
    Serial << "]\n";

    int one_d_array_value_doubled[ONE_D_ARRAY_ELEMENT_COUNT];
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      one_d_array_value_doubled[i] = 2*one_d_array_value[i];
    }
    int bytes_written = one_d_array_doubled_sv.setValue(one_d_array_value_doubled);
    Serial << "bytes written = " << bytes_written << "\n";
    int one_d_array_value_doubled_copy[ONE_D_ARRAY_ELEMENT_COUNT];
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      one_d_array_doubled_sv.getValue(one_d_array_value_doubled_copy,i);
      Serial << "one_d_array_value_doubled_copy[" << i << "] = " << one_d_array_value_doubled_copy[i] << " should be = " << 2*one_d_array_value[i] << endl;
    }

    int one_d_array_default_value_copied[ONE_D_ARRAY_ELEMENT_COUNT];
    bytes_copied = one_d_array_sv.getDefaultValue(one_d_array_default_value_copied);
    Serial << "bytes copied = " << bytes_copied << "\n";
    Serial << "one_d_array_default_value_copied = [";
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << one_d_array_default_value_copied[i];
    }
    Serial << "]\n";

    int one_d_array_default_value_copied2[ONE_D_ARRAY_ELEMENT_COUNT];
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      bytes_copied = one_d_array_sv.getDefaultValue(one_d_array_default_value_copied2,i);
      Serial << "bytes copied = " << bytes_copied << "\n";
    }
    Serial << "one_d_array_default_value_copied2 = [";
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << one_d_array_default_value_copied2[i];
    }
    Serial << "]\n";

    Serial << endl;

    int p = 0;
    one_d_array_value[p] += 1;
    one_d_array_sv.setValue(one_d_array_value,p);

    delay(4000);
  }
}


void loop()
{
}
