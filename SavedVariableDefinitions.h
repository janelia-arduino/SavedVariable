// ----------------------------------------------------------------------------
// SavedVariableDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SAVED_VARIABLE_DEFINITIONS_H
#define SAVED_VARIABLE_DEFINITIONS_H


template<typename T>
SavedVariable::SavedVariable(const T & default_value)
{
  array_element_size_ = 0;
  array_length_ = 0;
  array_length_max_ = 0;
  array_length_max_at_construction_ = 0;
  size_ = sizeof(default_value);
  default_value_ptr_ = &default_value;
  eeprom_index_ = s_eeprom_index;
  s_eeprom_index += getSize();
}

template<typename T, size_t N>
SavedVariable::SavedVariable(const T (&default_value)[N])
{
  array_element_size_ = sizeof(T);
  array_length_ = N;
  array_length_max_ = N;
  array_length_max_at_construction_ = N;
  size_ = array_element_size_*N;
  default_value_ptr_ = default_value;
  eeprom_index_ = s_eeprom_index;
  s_eeprom_index += getSize();
}

template<typename T>
size_t SavedVariable::getDefaultValue(T & value)
{
  size_t i = 0;
  if (sizeof(value) == size_)
  {
    byte * p = (byte *)(void *)&value;
    byte * q = (byte *)(void *)default_value_ptr_;
    for (i=0; i<size_; ++i)
    {
      *p++ = *q++;
    }
  }
  return i;
}

template<typename T>
size_t SavedVariable::getDefaultElementValue(const size_t element_index, T & value)
{
  size_t i = 0;
  if ((sizeof(value) == array_element_size_) &&
      (element_index < array_length_))
  {
    byte * p = (byte *)(void *)&value;
    byte * q = (byte *)(void *)default_value_ptr_ + element_index*array_element_size_;
    for (i=0; i<array_element_size_; ++i)
    {
      if (i < size_)
      {
        *p++ = *q++;
      }
    }
  }
  return i;
}

template<typename T>
bool SavedVariable::setDefaultValue(const T & default_value)
{
  if (sizeof(default_value) == size_)
  {
    default_value_ptr_ = &default_value;
    return true;
  }
  return false;
}

template<typename T, size_t N>
bool SavedVariable::setDefaultValue(const T (&default_value)[N])
{
  if ((N <= array_length_max_at_construction_) &&
      (sizeof(T) == array_element_size_))
  {
    array_length_ = N;
    array_length_max_ = N;
    size_ = array_element_size_*N;
    default_value_ptr_ = default_value;
    return true;
  }
  return false;
}

#ifndef ARDUINO_SAM_DUE
template<typename T>
size_t SavedVariable::setValue(const T & value)
{
  size_t i = 0;
  if (sizeof(value) == size_)
  {
    const byte * p = (const byte *)(const void *)&value;
    size_t ee = eeprom_index_;
    for (i=0; i<size_; ++i)
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
  return i;
}

template<typename T>
size_t SavedVariable::setElementValue(const size_t element_index, const T & value)
{
  size_t i = 0;
  if ((sizeof(value) == array_element_size_) &&
      (element_index < array_length_))
  {
    const byte * p = (const byte *)(const void *)&value;
    size_t ee = eeprom_index_ + element_index*array_element_size_;
    for (i=0; i<array_element_size_; ++i)
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
  }
  return i;
}

template<typename T>
size_t SavedVariable::getValue(T & value)
{
  size_t i = 0;
  if (sizeof(value) == size_)
  {
    byte* p = (byte *)(void *)&value;
    size_t ee = eeprom_index_;
    for (i=0; i<size_; ++i)
    {
      *p++ = EEPROM.read(ee++);
    }
  }
  return i;
}

template<typename T>
size_t SavedVariable::getElementValue(const size_t element_index, T & value)
{
  size_t i = 0;
  if ((sizeof(value) == array_element_size_) &&
      (element_index < array_length_))
  {
    byte * p = (byte *)(void *)&value;
    size_t ee = eeprom_index_ + element_index*array_element_size_;
    for (i=0; i<array_element_size_; ++i)
    {
      if (i < size_)
      {
        *p++ = EEPROM.read(ee++);
      }
    }
  }
  return i;
}
#else

template<typename T>
size_t SavedVariable::setValue(const T & value)
{
  size_t i = 0;
  return i;
}

template<typename T>
size_t SavedVariable::setElementValue(const size_t element_index, const T & value)
{
  size_t i = 0;
  return i;
}

template<typename T>
size_t SavedVariable::getValue(T & value)
{
  return getDefaultValue(value);
}

template<typename T>
size_t SavedVariable::getElementValue(const size_t element_index, T & value)
{
  return getDefaultElementValue(element_index,value);
}

#endif

#endif
