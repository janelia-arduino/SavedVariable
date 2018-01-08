#include <Arduino.h>
#include <Streaming.h>
#include <EEPROM.h>
#include <SavedVariable.h>


const long BAUD = 115200;

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

  Serial.begin(BAUD);
  Serial.flush();

  SavedVariable eeprom_initialized_sv(EEPROM_INITIALIZED_VALUE);

  SavedVariable simple_int_sv(SIMPLE_INT_DEFAULT_VALUE);

  SavedVariable simple_double_sv(SIMPLE_DOUBLE_DEFAULT_VALUE);

  SavedVariable complex_struct_sv(COMPLEX_STRUCT_DEFAULT_VALUE);

  SavedVariable one_d_array_sv(ONE_D_ARRAY_DEFAULT_VALUE);

  SavedVariable two_d_array_sv(TWO_D_ARRAY_DEFAULT_VALUE);

  for (int i=0;i<2;++i)
  {
    int eeprom_initial_value;
    eeprom_initialized_sv.getValue(eeprom_initial_value);
    Serial << "eeprom_intial_value = " << eeprom_initial_value << " should be = " << EEPROM_INITIALIZED_VALUE << endl;
    if (eeprom_initial_value != EEPROM_INITIALIZED_VALUE)
    {
      Serial << "Default values set for the first time!" << endl;
      eeprom_initialized_sv.setValueToDefault();
      simple_int_sv.setValueToDefault();
      complex_struct_sv.setValueToDefault();
      simple_double_sv.setValueToDefault();
      one_d_array_sv.setValueToDefault();
      two_d_array_sv.setValueToDefault();
    }
    else
    {
      Serial << "Default values already set!" << endl;
    }

    int simple_int_value;
    simple_int_sv.getValue(simple_int_value);
    Serial << "simple_int_sv.getSize() = " << simple_int_sv.getSize() << endl;
    Serial << "simple_int_value = " << simple_int_value << " should be = " << SIMPLE_INT_DEFAULT_VALUE << endl;

    double simple_double_value;
    simple_double_sv.getValue(simple_double_value);
    Serial << "simple_double_sv.getSize() = " << simple_double_sv.getSize() << endl;
    Serial << "simple_double_value = " << simple_double_value << " should be >= " << SIMPLE_DOUBLE_DEFAULT_VALUE << endl;
    simple_double_value += 0.10;
    simple_double_sv.setValue(simple_double_value);

    Product complex_struct_value;
    complex_struct_sv.getValue(complex_struct_value);
    Serial << "complex_struct_sv.getSize() = " << complex_struct_sv.getSize() << endl;
    Serial << "complex_struct_value.weight = " << complex_struct_value.weight << " should be = " << WEIGHT_DEFAULT_VALUE << endl;
    Serial << "complex_struct_value.price = " << complex_struct_value.price << " should be >= " << PRICE_DEFAULT_VALUE << endl;
    Serial << "complex_struct_value.sold = " << complex_struct_value.sold << " should be = " << SOLD_DEFAULT_VALUE << endl;
    complex_struct_value.price += 0.10;
    complex_struct_sv.setValue(complex_struct_value);

    int one_d_array_element;
    Serial << "one_d_array_sv.getSize() = " << one_d_array_sv.getSize() << endl;
    for (int i=0; i<ONE_D_ARRAY_ELEMENT_COUNT; ++i)
    {
      one_d_array_sv.getElementValue(i,one_d_array_element);
      if (i == 0)
      {
        Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be >= " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
      }
      else
      {
        Serial << "one_d_array[" << i << "] = " << one_d_array_element << " should be = " << ONE_D_ARRAY_DEFAULT_VALUE[i] << endl;
      }
    }
    int p = 0;
    one_d_array_sv.getElementValue(p,one_d_array_element);
    one_d_array_element += 1;
    one_d_array_sv.setElementValue(p,one_d_array_element);

    int two_d_array_element[TWO_D_ARRAY_ELEMENT_COUNT_B];
    Serial << "two_d_array_sv.getSize() = " << two_d_array_sv.getSize() << endl;
    for (int i=0; i<TWO_D_ARRAY_ELEMENT_COUNT_A; ++i)
    {
      two_d_array_sv.getElementValue(i,two_d_array_element);
      for (int j=0; j<TWO_D_ARRAY_ELEMENT_COUNT_B; ++j)
      {
        if ((i == 0) && (j == 1))
        {
          Serial << "two_d_array[" << i << "][" << j << "] = "<< two_d_array_element[j] << " should be >= " << TWO_D_ARRAY_DEFAULT_VALUE[i][j] << endl;
        }
        else
        {
          Serial << "two_d_array[" << i << "][" << j << "] = "<< two_d_array_element[j] << " should be = " << TWO_D_ARRAY_DEFAULT_VALUE[i][j] << endl;
        }
      }
    }
    int q = 0;
    int r = 1;
    two_d_array_sv.getElementValue(q,two_d_array_element);
    two_d_array_element[r] += 1;
    two_d_array_sv.setElementValue(q,two_d_array_element);

    Serial << endl;

    delay(4000);
  }
}


void loop()
{
}
