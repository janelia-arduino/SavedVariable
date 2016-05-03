#include "Arduino.h"
#include "Streaming.h"
#ifndef ARDUINO_SAM_DUE
#include <EEPROM.h>
#endif
#include "SavedVariable.h"

const int BAUDRATE = 9600;

const int EEPROM_INITIALIZED_VALUE = 99;
const int SIMPLE_INT_DEFAULT_VALUE = 4567;
const double SIMPLE_DOUBLE_DEFAULT_VALUE = 3.1415;
struct Product
{
  int weight;
  double price;
  boolean sold;
  Product() {};
  Product(int weight,double price,boolean sold) : weight(weight),price(price),sold(sold) {};
};
const int WEIGHT_DEFAULT_VALUE = 100;
const double PRICE_DEFAULT_VALUE = 1.25;
const boolean SOLD_DEFAULT_VALUE = true;
const Product COMPLEX_STRUCT_DEFAULT_VALUE(WEIGHT_DEFAULT_VALUE,PRICE_DEFAULT_VALUE,SOLD_DEFAULT_VALUE);
const int ONE_D_ARRAY_ELEMENT_COUNT = 4;
const int ONE_D_ARRAY_DEFAULT_VALUE[ONE_D_ARRAY_ELEMENT_COUNT] = {10,11,12,13};
const int TWO_D_ARRAY_ELEMENT_COUNT_A = 3;
const int TWO_D_ARRAY_ELEMENT_COUNT_B = 2;
const int TWO_D_ARRAY_DEFAULT_VALUE[TWO_D_ARRAY_ELEMENT_COUNT_A][TWO_D_ARRAY_ELEMENT_COUNT_B] =
  {{6,7},{16,17},{26,27}};

void setup()
{
  while (!Serial);

  Serial.begin(BAUDRATE);
  Serial.flush();

  SavedVariable eeprom_initialized(EEPROM_INITIALIZED_VALUE);

  SavedVariable simple_int(SIMPLE_INT_DEFAULT_VALUE);

  SavedVariable simple_double(SIMPLE_DOUBLE_DEFAULT_VALUE);

  SavedVariable complex_struct(COMPLEX_STRUCT_DEFAULT_VALUE);

  SavedVariable one_d_array(ONE_D_ARRAY_DEFAULT_VALUE,
                            ONE_D_ARRAY_ELEMENT_COUNT);

  SavedVariable two_d_array(TWO_D_ARRAY_DEFAULT_VALUE,
                            TWO_D_ARRAY_ELEMENT_COUNT_A);

  for (int i=0;i<2;++i)
  {
    int eeprom_initial_value;
    eeprom_initialized.getValue(eeprom_initial_value);
    Serial << "eeprom_intial_value = " << eeprom_initial_value << " should be = " << EEPROM_INITIALIZED_VALUE << endl;
    if (eeprom_initial_value != EEPROM_INITIALIZED_VALUE)
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

    int simple_int_value;
    simple_int.getValue(simple_int_value);
    Serial << "simple_int.getSize() = " << simple_int.getSize() << endl;
    Serial << "simple_int_value = " << simple_int_value << " should be = " << SIMPLE_INT_DEFAULT_VALUE << endl;

    double simple_double_value;
    simple_double.getValue(simple_double_value);
    Serial << "simple_double.getSize() = " << simple_double.getSize() << endl;
    Serial << "simple_double_value = " << simple_double_value << " should be >= " << SIMPLE_DOUBLE_DEFAULT_VALUE << endl;
    simple_double_value += 0.10;
    simple_double.setValue(simple_double_value);

    Product complex_struct_value;
    complex_struct.getValue(complex_struct_value);
    Serial << "complex_struct.getSize() = " << complex_struct.getSize() << endl;
    Serial << "complex_struct_value.weight = " << complex_struct_value.weight << " should be = " << WEIGHT_DEFAULT_VALUE << endl;
    Serial << "complex_struct_value.price = " << complex_struct_value.price << " should be >= " << PRICE_DEFAULT_VALUE << endl;
    Serial << "complex_struct_value.sold = " << complex_struct_value.sold << " should be = " << SOLD_DEFAULT_VALUE << endl;
    complex_struct_value.price += 0.10;
    complex_struct.setValue(complex_struct_value);

    int one_d_array_value[ONE_D_ARRAY_ELEMENT_COUNT];
    Serial << "one_d_array.getSize() = " << one_d_array.getSize() << endl;
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      one_d_array.getValue(one_d_array_value,i);
      if (i == 0)
      {
        Serial << "one_d_array_value[" << i << "] = " << one_d_array_value[i] << " should be >= " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
      }
      else
      {
        Serial << "one_d_array_value[" << i << "] = " << one_d_array_value[i] << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
      }
    }
    int p = 0;
    one_d_array_value[p] += 1;
    one_d_array.setValue(one_d_array_value,p);

    int two_d_array_value[TWO_D_ARRAY_ELEMENT_COUNT_A][TWO_D_ARRAY_ELEMENT_COUNT_B];
    Serial << "two_d_array.getSize() = " << two_d_array.getSize() << endl;
    for (int i=0; i<TWO_D_ARRAY_ELEMENT_COUNT_A; ++i)
    {
      two_d_array.getValue(two_d_array_value,i);
      for (int j=0; j<TWO_D_ARRAY_ELEMENT_COUNT_B; ++j)
      {
        if ((i == 0) && (j == 1))
        {
          Serial << "two_d_array_value[" << i << "][" << j << "] = "<< two_d_array_value[i][j] << " should be >= " << TWO_D_ARRAY_DEFAULT_VALUE[i][j] << endl;
        }
        else
        {
          Serial << "two_d_array_value[" << i << "][" << j << "] = "<< two_d_array_value[i][j] << " should be = " << TWO_D_ARRAY_DEFAULT_VALUE[i][j] << endl;
        }
      }
    }
    int q = 0;
    int r = 1;
    two_d_array_value[q][r] += 1;
    two_d_array.setValue(two_d_array_value,q);

    Serial << endl;

    delay(4000);
  }
}


void loop()
{
}
