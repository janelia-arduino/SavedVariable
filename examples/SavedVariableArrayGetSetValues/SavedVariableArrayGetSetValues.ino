#include <Arduino.h>
#include <Streaming.h>
#include <EEPROM.h>
#include <SavedVariable.h>
#include <Array.h>


const long BAUD = 115200;

const size_t ONE_D_ARRAY_DEFAULT_ELEMENT_COUNT = 4;
const size_t ONE_D_ARRAY_DEFAULT_VALUE[ONE_D_ARRAY_DEFAULT_ELEMENT_COUNT] = {100,110,120,130};
const size_t ONE_D_ARRAY_DEFAULT_LENGTH = 3;
const size_t ONE_D_ARRAY_ELEMENT_COUNT = 2;
const size_t ONE_D_ARRAY_VALUE[ONE_D_ARRAY_ELEMENT_COUNT] = {77,66};

void setup()
{
  while (!Serial);

  Serial.begin(BAUD);
  Serial.flush();

  SavedVariable one_d_array_sv(ONE_D_ARRAY_DEFAULT_VALUE,ONE_D_ARRAY_DEFAULT_LENGTH);

  size_t size;
  size_t array_length;
  size_t array_length_max;

  Serial << "Setting values to default!" << endl;
  one_d_array_sv.setValueToDefault();

  size = one_d_array_sv.getSize();
  array_length = one_d_array_sv.getArrayLength();
  array_length_max = one_d_array_sv.getArrayLengthMax();
  Serial << "one_d_array_sv.getSize() = " << size << endl;
  Serial << "one_d_array_sv.getArrayLength() = " << array_length << endl;
  Serial << "one_d_array_sv.getArrayLengthMax() = " << array_length_max << endl;
  size_t default_value[ONE_D_ARRAY_DEFAULT_ELEMENT_COUNT];
  size_t element_count = one_d_array_sv.getDefaultValue(default_value);
  Serial << "element_count = " << element_count << endl;
  for (size_t i=0; i<element_count; ++i)
  {
    Serial << "default_value[" << i << "] = " << default_value[i] << " should be == " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
  }
  Array<size_t,ONE_D_ARRAY_DEFAULT_ELEMENT_COUNT> default_value_array;
  default_value_array.assign(element_count,default_value);
  Serial << "default_value_array = " << default_value_array << endl;
  Serial << endl;

  Serial << "one_d_array_sv.setValue(ONE_D_ARRAY_VALUE)" << endl;
  one_d_array_sv.setValue(ONE_D_ARRAY_VALUE);
  size = one_d_array_sv.getSize();
  array_length = one_d_array_sv.getArrayLength();
  array_length_max = one_d_array_sv.getArrayLengthMax();
  Serial << "one_d_array_sv.getSize() = " << size << endl;
  Serial << "one_d_array_sv.getArrayLength() = " << array_length << endl;
  Serial << "one_d_array_sv.getArrayLengthMax() = " << array_length_max << endl;

  size_t value[ONE_D_ARRAY_DEFAULT_ELEMENT_COUNT];
  element_count = one_d_array_sv.getValue(value);
  Serial << "element_count = " << element_count << endl;
  for (size_t i=0; i<element_count; ++i)
  {
    Serial << "value[" << i << "] = " << value[i] << " should be != " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
  }
  Array<size_t,ONE_D_ARRAY_DEFAULT_ELEMENT_COUNT> value_array;
  value_array.assign(element_count,value);
  Serial << "value_array = " << value_array << endl;
  Serial << endl;

  Serial << "one_d_array_sv.setArrayLength(" << ONE_D_ARRAY_ELEMENT_COUNT << ")" << endl;
  one_d_array_sv.setArrayLength(ONE_D_ARRAY_ELEMENT_COUNT);
  Serial << "one_d_array_sv.setValue(ONE_D_ARRAY_VALUE)" << endl;
  one_d_array_sv.setValue(ONE_D_ARRAY_VALUE);
  size = one_d_array_sv.getSize();
  array_length = one_d_array_sv.getArrayLength();
  array_length_max = one_d_array_sv.getArrayLengthMax();
  Serial << "one_d_array_sv.getSize() = " << size << endl;
  Serial << "one_d_array_sv.getArrayLength() = " << array_length << endl;
  Serial << "one_d_array_sv.getArrayLengthMax() = " << array_length_max << endl;

  element_count = one_d_array_sv.getValue(value);
  Serial << "element_count = " << element_count << endl;
  for (size_t i=0; i<element_count; ++i)
  {
    Serial << "value[" << i << "] = " << value[i] << " should be == " << ONE_D_ARRAY_VALUE[i] << endl;
  }
  value_array.assign(element_count,value);
  Serial << "value_array = " << value_array << endl;
  Serial << endl;

}


void loop()
{
}
