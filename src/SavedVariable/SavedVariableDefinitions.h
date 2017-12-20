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
  array_length_default_ = 0;
  array_length_max_ = 0;
  array_length_max_at_construction_ = 0;
  default_value_ptr_ = &default_value;
  eeprom_index_ = s_eeprom_index;
  size_ = sizeof(default_value);
  s_eeprom_index += size_;
}

template<typename T, size_t N>
SavedVariable::SavedVariable(const T (&default_value)[N],
                             const size_t array_length_default)
{
  array_element_size_ = sizeof(T);
  array_length_default_ = array_length_default;
  if (array_length_default_ > N)
  {
    array_length_default_ = N;
  }
  array_length_max_ = N;
  array_length_max_at_construction_ = N;
  default_value_ptr_ = default_value;
  eeprom_index_ = s_eeprom_index;
  size_ = array_element_size_*getArrayLength();
  s_eeprom_index += array_element_size_*N + sizeof(array_length_default_);
}

template<typename T>
size_t SavedVariable::getDefaultValue(T & default_value)
{
  size_t byte_count = 0;
  if (sizeof(default_value) == size_)
  {
    byte * p = (byte *)(void *)&default_value;
    byte * q = (byte *)(void *)default_value_ptr_;
    for (byte_count=0; byte_count<size_; ++byte_count)
    {
      *p++ = *q++;
    }
  }
  return byte_count;
}

template<typename T, size_t N>
size_t SavedVariable::getDefaultValue(T (&default_value)[N])
{
  size_t element_count = 0;
  if (sizeof(T) == array_element_size_)
  {
    element_count = min(N,array_length_default_);
    byte * p = (byte *)(void *)&default_value;
    for (size_t element_index=0; element_index<element_count; ++element_index)
    {
      byte * q = (byte *)(void *)default_value_ptr_ + element_index*array_element_size_;
      for (size_t i=0; i<array_element_size_; ++i)
      {
        *p++ = *q++;
      }
    }
  }
  return element_count;
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
bool SavedVariable::setDefaultValue(const T (&default_value)[N],
                                    const size_t array_length_default)
{
  if ((N <= array_length_max_at_construction_) &&
      (sizeof(T) == array_element_size_))
  {
    array_length_max_ = N;
    setArrayLengthDefault(array_length_default);
    default_value_ptr_ = default_value;
    size_ = array_element_size_*getArrayLength();
    return true;
  }
  return false;
}

template<typename T>
size_t SavedVariable::getDefaultElementValue(const size_t element_index,
                                             T & default_element_value)
{
  size_t byte_count = 0;
  if ((sizeof(default_element_value) == array_element_size_) &&
      (element_index < array_length_default_))
  {
    byte * p = (byte *)(void *)&default_element_value;
    byte * q = (byte *)(void *)default_value_ptr_ + element_index*array_element_size_;
    for (byte_count=0; byte_count<array_element_size_; ++byte_count)
    {
      *p++ = *q++;
    }
  }
  return byte_count;
}

template<typename T>
size_t SavedVariable::getValue(T & value)
{
  size_t byte_count = 0;
  if (sizeof(value) == size_)
  {
    byte* p = (byte *)(void *)&value;
    size_t ee = eeprom_index_;
    for (byte_count=0; byte_count<size_; ++byte_count)
    {
      *p++ = EEPROM.read(ee++);
    }
  }
  return byte_count;
}

template<typename T, size_t N>
size_t SavedVariable::getValue(T (&value)[N])
{
  size_t element_count = 0;
  if (sizeof(T) == array_element_size_)
  {
    element_count = min(N,getArrayLength());
    byte * p = (byte *)(void *)&value;
    for (size_t element_index=0; element_index<element_count; ++element_index)
    {
      size_t ee = eeprom_index_ + element_index*array_element_size_;
      for (size_t i=0; i<array_element_size_; ++i)
      {
        *p++ = EEPROM.read(ee++);
      }
    }
  }
  return element_count;
}

template<typename T>
size_t SavedVariable::setValue(const T & value)
{
  size_t byte_count = 0;
  if (sizeof(value) == size_)
  {
    const byte * p = (const byte *)(const void *)&value;
    size_t ee = eeprom_index_;
    for (byte_count=0; byte_count<size_; ++byte_count)
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
  return byte_count;
}

template<typename T, size_t N>
size_t SavedVariable::setValue(const T (&value)[N],
                               const size_t array_length)
{
  size_t element_count = 0;
  if ((array_length == getArrayLength()) &&
      (sizeof(T) == array_element_size_))
  {
    element_count = array_length;
    byte * p = (byte *)(void *)&value;
    for (size_t element_index=0; element_index<element_count; ++element_index)
    {
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
  return element_count;
}

template<typename T>
size_t SavedVariable::getElementValue(const size_t element_index,
                                      T & element_value)
{
  size_t byte_count = 0;
  if ((sizeof(element_value) == array_element_size_) &&
      (element_index < getArrayLength()))
  {
    byte * p = (byte *)(void *)&element_value;
    size_t ee = eeprom_index_ + element_index*array_element_size_;
    for (byte_count=0; byte_count<array_element_size_; ++byte_count)
    {
      *p++ = EEPROM.read(ee++);
    }
  }
  return byte_count;
}

template<typename T>
size_t SavedVariable::setElementValue(const size_t element_index,
                                      const T & element_value)
{
  size_t byte_count = 0;
  if ((sizeof(element_value) == array_element_size_) &&
      (element_index < getArrayLength()))
  {
    const byte * p = (const byte *)(const void *)&element_value;
    size_t ee = eeprom_index_ + element_index*array_element_size_;
    for (byte_count=0; byte_count<array_element_size_; ++byte_count)
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
  return byte_count;
}

#endif
