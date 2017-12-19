#include <Arduino.h>
#include <Streaming.h>
#include <EEPROM.h>
#include <SavedVariable.h>
#include <ConstantVariable.h>


const long BAUDRATE = 115200;

union SubsetMemberType
{
  const long l;
  ConstantString * const cs_ptr;
};

const int EEPROM_INITIALIZED_VALUE = 98;

enum{MODE_SUBSET_LENGTH=3};
CONSTANT_STRING(mode_rising,"RISING");
CONSTANT_STRING(mode_falling,"FALLING");
CONSTANT_STRING(mode_change,"CHANGE");
const SubsetMemberType mode_ptr_subset[MODE_SUBSET_LENGTH] =
  {
    {.cs_ptr=&mode_rising},
    {.cs_ptr=&mode_falling},
    {.cs_ptr=&mode_change},
  };
const ConstantString * const mode_ptr_default = &mode_rising;

void setup()
{
  while (!Serial);

  Serial.begin(BAUDRATE);
  Serial.flush();

  SavedVariable eeprom_initialized_sv(EEPROM_INITIALIZED_VALUE);

  SavedVariable mode_ptr_sv(mode_ptr_default);

  for (int i=0; i<4; ++i)
  {
    int eeprom_initial_value;
    eeprom_initialized_sv.getValue(eeprom_initial_value);
    Serial << "eeprom_intial_value = " << eeprom_initial_value << " should be = " << EEPROM_INITIALIZED_VALUE << endl;
    if (eeprom_initial_value != EEPROM_INITIALIZED_VALUE)
    {
      Serial << "Default values set for the first time!" << endl;
      eeprom_initialized_sv.setValueToDefault();
      mode_ptr_sv.setValueToDefault();
    }
    else
    {
      Serial << "Default values already set!" << endl;
    }

    const ConstantString *read_mode_ptr;
    mode_ptr_sv.getValue(read_mode_ptr);
    Serial << "initial mode value = " << *read_mode_ptr << endl;
    mode_ptr_sv.getDefaultValue(read_mode_ptr);
    Serial << "default mode value = " << *read_mode_ptr << endl;
    Serial << endl;

    for (int j=0; j<MODE_SUBSET_LENGTH; ++j)
    {
      const ConstantString * const write_mode_ptr = mode_ptr_subset[j].cs_ptr;
      mode_ptr_sv.setValue(write_mode_ptr);
      mode_ptr_sv.getValue(read_mode_ptr);
      Serial << "mode value = " << *read_mode_ptr << " should be = " << *write_mode_ptr << endl;

      Serial << endl;

      delay(1000);
    }
    delay(2000);
  }
}


void loop()
{
}
