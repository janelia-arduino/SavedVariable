#include <Arduino.h>
#include <Streaming.h>
#include <EEPROM.h>
#include <SavedVariable.h>


const long BAUDRATE = 115200;

const size_t EEPROM_INITIALIZED_VALUE = 123;

const size_t ONE_D_ARRAY_ELEMENT_COUNT = 4;
const size_t ONE_D_ARRAY_DEFAULT_VALUE[ONE_D_ARRAY_ELEMENT_COUNT] = {10,11,12,13};
const size_t ONE_D_ARRAY_DEFAULT_LENGTH = 3;

void setup()
{
  while (!Serial);

  Serial.begin(BAUDRATE);
  Serial.flush();

  SavedVariable eeprom_initialized_sv(EEPROM_INITIALIZED_VALUE);

  SavedVariable one_d_array_sv(ONE_D_ARRAY_DEFAULT_VALUE,ONE_D_ARRAY_DEFAULT_LENGTH);

  size_t bytes_copied = 0;
  size_t one_d_array_element;

  Serial << "Setting values to default!" << endl;
  eeprom_initialized_sv.setValueToDefault();
  one_d_array_sv.setValueToDefault();

  for (size_t i=0;i<2;++i)
  {
    size_t eeprom_initial_value;
    eeprom_initialized_sv.getValue(eeprom_initial_value);
    Serial << "eeprom_intial_value = " << eeprom_initial_value << " should be = " << EEPROM_INITIALIZED_VALUE << endl;
    if (eeprom_initial_value != EEPROM_INITIALIZED_VALUE)
    {
      Serial << "Setting values to default!" << endl;
      eeprom_initialized_sv.setValueToDefault();
      one_d_array_sv.setValueToDefault();
    }
    else
    {
      Serial << "Default values already set!" << endl;
    }

    Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
    Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
    Serial << "one_d_array_sv.getArrayLengthMax() = " << one_d_array_sv.getArrayLengthMax() << endl;
    for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
    {
      bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
      Serial << "bytes copied = " << bytes_copied << "\n";
      Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be >= " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
    }

    size_t array_length_test = 2;
    if (i == 1)
    {
      array_length_test = 0;
    }
    Serial << "one_d_array_sv.setArrayLength(" << array_length_test << ")" << endl;
    one_d_array_sv.setArrayLength(array_length_test);
    Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
    for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
    {
      bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
      Serial << "bytes copied = " << bytes_copied << "\n";
      Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be >= " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
    }

    delay(4000);
  }

  size_t array_length_default_new = 1;
  Serial << "one_d_array_sv.setArrayLengthDefault(" << array_length_default_new << ")" << endl;
  one_d_array_sv.setArrayLengthDefault(array_length_default_new);
  Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;
  Serial << "one_d_array_sv.setArrayLengthToDefault()" << endl;
  one_d_array_sv.setArrayLengthToDefault();
  Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;

  for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
  {
    bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
  }

  Serial << "one_d_array_sv.setArrayLengthToMax()" << endl;
  one_d_array_sv.setArrayLengthToMax();
  Serial << "one_d_array_sv.getArrayLength() = " << one_d_array_sv.getArrayLength() << endl;

  for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
  {
    bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
  }

  bool one_d_array_is_default = one_d_array_sv.valueIsDefault();
  Serial << "one_d_array_is_default = " << one_d_array_is_default << "\n";
  one_d_array_sv.setValueToDefault();
  for (size_t i=0; i<one_d_array_sv.getArrayLength(); ++i)
  {
    bytes_copied = one_d_array_sv.getElementValue(i,one_d_array_element);
    Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
  }
  one_d_array_is_default = one_d_array_sv.valueIsDefault();
  Serial << "one_d_array_is_default = " << one_d_array_is_default << "\n";

}


void loop()
{
}
