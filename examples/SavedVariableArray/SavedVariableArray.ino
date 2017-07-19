#include "Arduino.h"
#include "Streaming.h"
#ifndef ARDUINO_SAM_DUE
#include <EEPROM.h>
#endif
#include "SavedVariable.h"

const size_t BAUDRATE = 115200;

const size_t EEPROM_INITIALIZED_VALUE = 44;

const size_t ONE_D_ARRAY_ELEMENT_COUNT = 4;
const size_t ONE_D_ARRAY_DEFAULT_VALUE[ONE_D_ARRAY_ELEMENT_COUNT] = {10,11,12,13};
const size_t ONE_D_ARRAY_NEW_DEFAULT_VALUE[ONE_D_ARRAY_ELEMENT_COUNT] = {100,110,120,130};

void setup()
{
  while (!Serial);

  Serial.begin(BAUDRATE);
  Serial.flush();

  SavedVariable eeprom_initialized_sv(EEPROM_INITIALIZED_VALUE);

  SavedVariable one_d_array_sv(ONE_D_ARRAY_DEFAULT_VALUE);

  SavedVariable one_d_array_doubled_sv(ONE_D_ARRAY_DEFAULT_VALUE);

  size_t bytes_copied = 0;
  size_t bytes_written = 0;
  size_t one_d_array_element;

  for (size_t i=0;i<2;++i)
  {
    size_t eeprom_initial_value;
    eeprom_initialized_sv.getValue(eeprom_initial_value);
    Serial << "eeprom_intial_value = " << eeprom_initial_value << " should be = " << EEPROM_INITIALIZED_VALUE << endl;
    if (eeprom_initial_value != EEPROM_INITIALIZED_VALUE)
    {
      Serial << "Default values set for the first time!" << endl;
      eeprom_initialized_sv.setValueToDefault();
      one_d_array_sv.setValueToDefault();
      one_d_array_doubled_sv.setValueToDefault();
    }
    else
    {
      Serial << "Default values already set!" << endl;
    }

    Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
    for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
      Serial << "bytes copied = " << bytes_copied << "\n";
      Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be >= " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
    }

    size_t array_length_test = 2;
    Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
    Serial << "one_d_array_sv.getArrayLengthMax() = " << one_d_array_sv.getArrayLengthMax() << endl;
    Serial << "one_d_array_sv.setArrayLength(" << array_length_test << ")" << endl;
    one_d_array_sv.setArrayLength(array_length_test);
    Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
    for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
    {
      bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
      Serial << "bytes copied = " << bytes_copied << "\n";
      Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be >= " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
    }
    Serial << "one_d_array_sv.setArrayLengthToMax()" << endl;
    one_d_array_sv.setArrayLengthToMax();
    Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;

    size_t one_d_array_copy[ONE_D_ARRAY_ELEMENT_COUNT];
    bytes_copied = one_d_array_sv.getValue(one_d_array_copy);
    Serial << "bytes copied = " << bytes_copied << "\n";
    Serial << "one_d_array_copy = [";
    for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << one_d_array_copy[i];
    }
    Serial << "]\n";

    size_t one_d_array_doubled_element;
    for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      one_d_array_doubled_element = 2*one_d_array_copy[i];
      bytes_written = one_d_array_doubled_sv.setElementValue(i,one_d_array_doubled_element);
      Serial << "bytes written = " << bytes_written << "\n";
    }
    for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      one_d_array_doubled_sv.getElementValue(i,one_d_array_doubled_element);
      Serial << "one_d_array_doubled[" << i << "] = " << one_d_array_doubled_element << " should be = " << 2*one_d_array_copy[i] << endl;
    }

    size_t one_d_array_default_value_copy[ONE_D_ARRAY_ELEMENT_COUNT];
    bytes_copied = one_d_array_sv.getDefaultValue(one_d_array_default_value_copy);
    Serial << "bytes copied = " << bytes_copied << "\n";
    Serial << "one_d_array_default_value_copy = [";
    for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << one_d_array_default_value_copy[i];
    }
    Serial << "]\n";

    size_t one_d_array_default_value_element;
    Serial << "one_d_array_default_value_element_by_element = [";
    for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      bytes_copied = one_d_array_sv.getDefaultElementValue(i,one_d_array_default_value_element);
      if (i != 0)
      {
        Serial << ",";
      }
      Serial << one_d_array_default_value_element;
    }
    Serial << "]\n";

    Serial << endl;

    size_t one_d_array_doubled_copy[ONE_D_ARRAY_ELEMENT_COUNT];
    bytes_copied = one_d_array_doubled_sv.getValue(one_d_array_doubled_copy);
    bytes_written = one_d_array_sv.setValue(one_d_array_doubled_copy);

    delay(4000);
  }
  for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
  {
    bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
  }
  bool one_d_array_is_default = one_d_array_sv.valueIsDefault();
  Serial << "one_d_array_is_default = " << one_d_array_is_default << "\n";
  one_d_array_sv.setValueToDefault();
  for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
  {
    bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
  }
  one_d_array_is_default = one_d_array_sv.valueIsDefault();
  Serial << "one_d_array_is_default = " << one_d_array_is_default << "\n";

  Serial << "set new default value for one_d_array_sv\n";
  one_d_array_sv.setDefaultValue(ONE_D_ARRAY_NEW_DEFAULT_VALUE);

  one_d_array_is_default = one_d_array_sv.valueIsDefault();
  Serial << "one_d_array_is_default = " << one_d_array_is_default << "\n";

  Serial << "set value to default for one_d_array_sv\n";
  one_d_array_sv.setValueToDefault();

  one_d_array_is_default = one_d_array_sv.valueIsDefault();
  Serial << "one_d_array_is_default = " << one_d_array_is_default << "\n";

  for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
  {
    bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be = " << ONE_D_ARRAY_NEW_DEFAULT_VALUE[i] << endl;
  }

  size_t one_d_array_doubled_element;
  for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
  {
    one_d_array_doubled_sv.getElementValue(i,one_d_array_doubled_element);
    Serial << "one_d_array_doubled[" << i << "] = " << one_d_array_doubled_element << endl;
  }
  Serial << "one_d_array_doubled_sv.setElementValueToDefault(1)" << endl;
  Serial << "one_d_array_doubled_sv.setElementValueToDefault(3)" << endl;
  one_d_array_doubled_sv.setElementValueToDefault(1);
  one_d_array_doubled_sv.setElementValueToDefault(3);
  for (size_t i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
  {
    one_d_array_doubled_sv.getElementValue(i,one_d_array_doubled_element);
    Serial << "one_d_array_doubled[" << i << "] = " << one_d_array_doubled_element << endl;
  }
}


void loop()
{
}
