// ----------------------------------------------------------------------------
// SavedVariable.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "../SavedVariable.h"


size_t SavedVariable::s_eeprom_index = 0;

SavedVariable::SavedVariable()
{
}

#ifndef ARDUINO_SAM_DUE
void SavedVariable::setValueToDefault()
{
  setArrayLengthToDefault();
  const byte* p = (const byte *)(const void *)default_value_ptr_;
  size_t ee = eeprom_index_;
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
  if ((element_index >= getArrayLength()) &&
      (element_index < array_length_default_))
  {
    setArrayLength(array_length_default_);
  }
  if (element_index < getArrayLength())
  {
    byte * p = (byte *)(void *)default_value_ptr_ + element_index*array_element_size_;
    size_t ee = eeprom_index_ + element_index*array_element_size_;
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
  bool is_default = true;
  if (getArrayLength() != array_length_default_)
  {
    return !is_default;
  }
  const byte* p = (const byte *)(const void *)default_value_ptr_;
  size_t ee = eeprom_index_;
  for (size_t i=0; i<size_; ++i)
  {
    if(EEPROM.read(ee) == *p)
    {
      ee++;
      p++;
    }
    else
    {
      return !is_default;
    }
  }
  return is_default;
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
  size_t array_length = 0;
  if (array_length_max_at_construction_ > 0)
  {
    byte * p = (byte *)(void *)&array_length;
    size_t ee = eeprom_index_ + array_length_max_at_construction_*array_element_size_;
    for (size_t i=0; i<sizeof(array_length_default_); ++i)
    {
      *p++ = EEPROM.read(ee++);
    }
  }
  if (array_length > array_length_max_)
  {
    array_length = array_length_max_;
  }
  return array_length;
}

bool SavedVariable::setArrayLength(const size_t array_length)
{
  bool success = false;
  if ((array_length_max_at_construction_ > 0) &&
      (array_length <= array_length_max_))
  {
    const byte * p = (const byte *)(const void *)&array_length;
    size_t ee = eeprom_index_ + array_length_max_at_construction_*array_element_size_;
    for (size_t i=0; i<sizeof(array_length_default_); ++i)
    {
      if(EEPROM.read(ee)==*p)
      {
        ee++;
        p++;
      }
      else
      {
        EEPROM.write(ee++,*p++);
      }
    }
    size_ = array_element_size_*array_length;
    success = true;
  }
  return success;
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

size_t SavedVariable::getArrayLengthDefault()
{
  return array_length_default_;
}

void SavedVariable::setArrayLengthDefault(const size_t array_length_default)
{
  array_length_default_ = array_length_default;
  if (array_length_default_ > array_length_max_)
  {
    array_length_default_ = array_length_max_;
  }
}

void SavedVariable::setArrayLengthToDefault()
{
  setArrayLength(array_length_default_);
}
