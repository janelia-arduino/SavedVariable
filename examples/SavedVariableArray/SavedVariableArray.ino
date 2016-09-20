#include "Arduino.h"
#include "Streaming.h"
#ifndef ARDUINO_SAM_DUE
#include <EEPROM.h>
#endif
#include "SavedVariable.h"

const int BAUDRATE = 9600;

const int EEPROM_INITIALIZED_VALUE = 44;

const int ONE_D_ARRAY_ELEMENT_COUNT = 4;
const int ONE_D_ARRAY_DEFAULT_VALUE[ONE_D_ARRAY_ELEMENT_COUNT] = {10,11,12,13};

void setup()
{
  while (!Serial);

  Serial.begin(BAUDRATE);
  Serial.flush();

  SavedVariable eeprom_initialized_sv(EEPROM_INITIALIZED_VALUE);

  SavedVariable one_d_array_sv(ONE_D_ARRAY_DEFAULT_VALUE,
                               ONE_D_ARRAY_ELEMENT_COUNT);

  SavedVariable one_d_array_doubled_sv(ONE_D_ARRAY_DEFAULT_VALUE,
                                       ONE_D_ARRAY_ELEMENT_COUNT);

  int bytes_copied = 0;
  int bytes_written = 0;
  int one_d_array_element;

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
      one_d_array_doubled_sv.setDefaultValue();
    }
    else
    {
      Serial << "Default values already set!" << endl;
    }

    Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      bytes_copied = one_d_array_sv.getElementValue(one_d_array_element,i);
      Serial << "bytes copied = " << bytes_copied << "\n";
      Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be >= " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
    }

    int one_d_array_copy[ONE_D_ARRAY_ELEMENT_COUNT];
    bytes_copied = one_d_array_sv.getValue(one_d_array_copy);
    Serial << "bytes copied = " << bytes_copied << "\n";
    Serial << "one_d_array_copy = [";
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << one_d_array_copy[i];
    }
    Serial << "]\n";

    int one_d_array_doubled_element;
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      one_d_array_doubled_element = 2*one_d_array_copy[i];
      bytes_written = one_d_array_doubled_sv.setElementValue(one_d_array_doubled_element,i);
      Serial << "bytes written = " << bytes_written << "\n";
    }
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      one_d_array_doubled_sv.getElementValue(one_d_array_doubled_element,i);
      Serial << "one_d_array_doubled[" << i << "] = " << one_d_array_doubled_element << " should be = " << 2*one_d_array_copy[i] << endl;
    }

    int one_d_array_default_value_copy[ONE_D_ARRAY_ELEMENT_COUNT];
    bytes_copied = one_d_array_sv.getDefaultValue(one_d_array_default_value_copy);
    Serial << "bytes copied = " << bytes_copied << "\n";
    Serial << "one_d_array_default_value_copy = [";
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << one_d_array_default_value_copy[i];
    }
    Serial << "]\n";

    int one_d_array_default_value_element;
    Serial << "one_d_array_default_value_element_by_element = [";
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      bytes_copied = one_d_array_sv.getDefaultElementValue(one_d_array_default_value_element,i);
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << one_d_array_default_value_element;
    }
    Serial << "]\n";

    Serial << endl;

    int one_d_array_doubled_copy[ONE_D_ARRAY_ELEMENT_COUNT];
    bytes_copied = one_d_array_doubled_sv.getValue(one_d_array_doubled_copy);
    bytes_written = one_d_array_sv.setValue(one_d_array_doubled_copy);

    delay(4000);
  }
  for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
  {
    bytes_copied = one_d_array_sv.getElementValue(one_d_array_element,i);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
  }
  bool one_d_array_is_default = one_d_array_sv.valueIsDefault();
  Serial << "one_d_array_is_default = " << one_d_array_is_default << "\n";
  one_d_array_sv.setDefaultValue();
  for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
  {
    bytes_copied = one_d_array_sv.getElementValue(one_d_array_element,i);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
  }
  one_d_array_is_default = one_d_array_sv.valueIsDefault();
  Serial << "one_d_array_is_default = " << one_d_array_is_default << "\n";
}


void loop()
{
}
