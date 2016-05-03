#include "Arduino.h"
#include "Streaming.h"
#include <EEPROM.h>
#include "SavedVariable.h"

const int BAUDRATE = 9600;

const int eeprom_initialized_value = 111;
const int simple_int_default_value = 4567;
const double simple_double_default_value = 3.1415;
struct Product
{
  int weight;
  double price;
  boolean sold;
  Product() {};
  Product(int weight,double price,boolean sold) : weight(weight),price(price),sold(sold) {};
};
const Product complex_struct_default_value(100,1.25,true);
const int one_d_array_element_count = 4;
const int one_d_array_default_value[one_d_array_element_count] = {10,11,12,13};
const int two_d_array_element_count_a = 3;
const int two_d_array_element_count_b = 2;
const int two_d_array_default_value[two_d_array_element_count_a][two_d_array_element_count_b] =
  {{6,7},{16,17},{26,27}};

void setup()
{
  Serial.begin(BAUDRATE);
  Serial.flush();
  delay(1000);

  int eeprom_index = 0;

  SavedVariable eeprom_initialized(eeprom_index,
                                   eeprom_initialized_value);
  eeprom_index += eeprom_initialized.getSize();

  SavedVariable simple_int(eeprom_index,
                           simple_int_default_value);
  eeprom_index += simple_int.getSize();

  SavedVariable simple_double(eeprom_index,
                              simple_double_default_value);
  eeprom_index += simple_double.getSize();

  SavedVariable complex_struct(eeprom_index,
                               complex_struct_default_value);
  eeprom_index += complex_struct.getSize();

  SavedVariable one_d_array(eeprom_index,
                            one_d_array_default_value,
                            one_d_array_element_count);
  eeprom_index += one_d_array.getSize();

  SavedVariable two_d_array(eeprom_index,
                            two_d_array_default_value,
                            two_d_array_element_count_a);
  eeprom_index += two_d_array.getSize();

  int eeprom_initial_value;
  eeprom_initialized.getValue(eeprom_initial_value);
  Serial << "eeprom_intial_value = " << eeprom_initial_value << endl;
  if (eeprom_initial_value != eeprom_initialized_value)
  {
    Serial << "Default values set for the first time!" << endl;
    eeprom_initialized.setDefaultValue();
    simple_int.setDefaultValue();
    complex_struct.setDefaultValue();
    simple_double.setDefaultValue();
    one_d_array.setDefaultValue();
    two_d_array.setDefaultValue();
  }
  else
  {
    Serial << "Default values already set!" << endl;
  }

  eeprom_initialized.getValue(eeprom_initial_value);
  Serial << "eeprom_intial_value = " << eeprom_initial_value << endl;

  int simple_int_value;
  simple_int.getValue(simple_int_value);
  Serial << "simple_int.getSize() = " << simple_int.getSize() << endl;
  Serial << "simple_int_value = " << simple_int_value << endl;

  double simple_double_value;
  simple_double.getValue(simple_double_value);
  Serial << "simple_double.getSize() = " << simple_double.getSize() << endl;
  Serial << "simple_double_value = " << simple_double_value << endl;

  Product complex_struct_value;
  complex_struct.getValue(complex_struct_value);
  Serial << "complex_struct.getSize() = " << complex_struct.getSize() << endl;
  Serial << "complex_struct_value.weight = " << complex_struct_value.weight << endl;
  Serial << "complex_struct_value.price = " << complex_struct_value.price << endl;
  Serial << "complex_struct_value.sold = " << complex_struct_value.sold << endl;
  complex_struct_value.price += 0.10;
  complex_struct.setValue(complex_struct_value);

  int one_d_array_value[one_d_array_element_count];
  Serial << "one_d_array.getSize() = " << one_d_array.getSize() << endl;
  for (int i=0; i<one_d_array_element_count; ++i)
  {
    one_d_array.getValue(one_d_array_value,i);
    Serial << "one_d_array_value[" << i << "] = " << one_d_array_value[i] << endl;
  }
  int p = 0;
  one_d_array_value[p] += 1;
  one_d_array.setValue(one_d_array_value,p);

  int two_d_array_value[two_d_array_element_count_a][two_d_array_element_count_b];
  Serial << "two_d_array.getSize() = " << two_d_array.getSize() << endl;
  for (int i=0; i<two_d_array_element_count_a; ++i)
  {
    two_d_array.getValue(two_d_array_value,i);
    for (int j=0; j<two_d_array_element_count_b; ++j)
    {
      Serial << "two_d_array_value[" << i << "][" << j << "] = "<< two_d_array_value[i][j] << endl;
    }
  }
  int q = 0;
  int r = 1;
  two_d_array_value[q][r] += 1;
  two_d_array.setValue(two_d_array_value,q);

}


void loop()
{
}
