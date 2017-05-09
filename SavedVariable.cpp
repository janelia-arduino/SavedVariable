// ----------------------------------------------------------------------------
// SavedVariable.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "SavedVariable.h"


size_t SavedVariable::s_eeprom_index = 0;

SavedVariable::SavedVariable()
{
}

#ifndef ARDUINO_SAM_DUE
void SavedVariable::setValueToDefault()
{
  const byte* p = (const byte *)(const void *)default_value_ptr_;
  int ee = eeprom_index_;
  for (size_t i=0; i<size_; ++i)
  {
    if(EEPROM.read(ee) == *p)
    {
      ee++;
      p++;
    }
    else
    {
      EEPROM.write(ee++,*p++);
    }
  }
}

void SavedVariable::setElementValueToDefault(const size_t element_index)
{
  if (element_index < array_length_)
  {
    byte * p = (byte *)(void *)default_value_ptr_ + element_index*array_element_size_;
    int ee = eeprom_index_ + element_index*array_element_size_;
    for (size_t i=0; i<array_element_size_; ++i)
    {
      if(EEPROM.read(ee) == *p)
      {
        ee++;
        p++;
      }
      else
      {
        EEPROM.write(ee++,*p++);
      }
    }
  }
}

bool SavedVariable::valueIsDefault()
{
  const byte* p = (const byte *)(const void *)default_value_ptr_;
  int ee = eeprom_index_;
  for (size_t i=0; i<size_; ++i)
  {
    if(EEPROM.read(ee) == *p)
    {
      ee++;
      p++;
    }
    else
    {
      return false;
    }
  }
  return true;
}
#else
void SavedVariable::setValueToDefault()
{
}

void SavedVariable::setElementValueToDefault()
{
}

bool SavedVariable::valueIsDefault()
{
  return true;
}
#endif

size_t SavedVariable::getSize()
{
  return size_;
}

size_t SavedVariable::getArrayLength()
{
  return array_length_;
}

void SavedVariable::setArrayLength(const size_t array_length)
{
  if ((array_length >= 1) && (array_length <= array_length_max_))
  {
    array_length_ = array_length;
    size_ = array_element_size_*array_length;
  }
}

size_t SavedVariable::getArrayLengthMax()
{
  return array_length_max_;
}

void SavedVariable::setArrayLengthToMax()
{
  setArrayLength(array_length_max_);
}

size_t SavedVariable::getArrayElementSize()
{
  return array_element_size_;
}
