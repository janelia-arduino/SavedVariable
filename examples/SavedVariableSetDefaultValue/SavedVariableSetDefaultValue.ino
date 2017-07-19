#include "Arduino.h"
#include "Streaming.h"
#ifndef ARDUINO_SAM_DUE
#include <EEPROM.h>
#endif
#include "SavedVariable.h"

const size_t BAUDRATE = 115200;

const size_t ONE_D_ARRAY_DEFAULT_VALUE_0[] = {10,11,12,13};
const size_t ONE_D_ARRAY_DEFAULT_VALUE_1[] = {100,110};
const size_t ONE_D_ARRAY_DEFAULT_VALUE_2[] = {333,666,999};
const size_t ONE_D_ARRAY_DEFAULT_VALUE_3[] = {5,4,3,2,1};

void setup()
{
  while (!Serial);

  Serial.begin(BAUDRATE);
  Serial.flush();

  SavedVariable one_d_array_sv(ONE_D_ARRAY_DEFAULT_VALUE_0);
  one_d_array_sv.setValueToDefault();

  size_t one_d_array_element;
  size_t one_d_array_element_default;


  Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
  Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
  for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
  {
    one_d_array_sv.getElementValue(i,one_d_array_element);
    one_d_array_sv.getDefaultElementValue(i,one_d_array_element_default);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be == " << one_d_array_element_default << endl;
  }

  Serial << endl;
  delay(1000);

  bool set_default_value = one_d_array_sv.setDefaultValue(ONE_D_ARRAY_DEFAULT_VALUE_1);
  Serial << "set_default_value = " << set_default_value << endl;
  one_d_array_sv.setArrayLengthToMax();
  one_d_array_sv.setValueToDefault();

  Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
  Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
  for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
  {
    one_d_array_sv.getElementValue(i,one_d_array_element);
    one_d_array_sv.getDefaultElementValue(i,one_d_array_element_default);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be == " << one_d_array_element_default << endl;
  }

  Serial << endl;

  one_d_array_sv.setArrayLength(1);
  Serial << "one_d_array_sv.setArrayLength(1)" << endl;
  Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
  Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
  for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
  {
    one_d_array_sv.getElementValue(i,one_d_array_element);
    one_d_array_sv.getDefaultElementValue(i,one_d_array_element_default);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be == " << one_d_array_element_default << endl;
  }

  Serial << endl;
  delay(1000);

  set_default_value = one_d_array_sv.setDefaultValue(ONE_D_ARRAY_DEFAULT_VALUE_2);
  Serial << "set_default_value = " << set_default_value << endl;
  one_d_array_sv.setArrayLengthToMax();
  one_d_array_sv.setValueToDefault();

  Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
  Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
  for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
  {
    one_d_array_sv.getElementValue(i,one_d_array_element);
    one_d_array_sv.getDefaultElementValue(i,one_d_array_element_default);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be == " << one_d_array_element_default << endl;
  }

  Serial << endl;

  one_d_array_sv.setArrayLength(1);
  Serial << "one_d_array_sv.setArrayLength(1)" << endl;
  Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
  Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
  for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
  {
    one_d_array_sv.getElementValue(i,one_d_array_element);
    one_d_array_sv.getDefaultElementValue(i,one_d_array_element_default);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be == " << one_d_array_element_default << endl;
  }

  Serial << endl;
  delay(1000);

  set_default_value = one_d_array_sv.setDefaultValue(ONE_D_ARRAY_DEFAULT_VALUE_3);
  Serial << "set_default_value = " << set_default_value << endl;
  one_d_array_sv.setArrayLengthToMax();
  one_d_array_sv.setValueToDefault();

  Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
  Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
  for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
  {
    one_d_array_sv.getElementValue(i,one_d_array_element);
    one_d_array_sv.getDefaultElementValue(i,one_d_array_element_default);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be == " << one_d_array_element_default << endl;
  }

  Serial << endl;

}


void loop()
{
}
