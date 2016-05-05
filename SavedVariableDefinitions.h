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
SavedVariable::SavedVariable(const T &default_value)
{
  array_element_size_ = 0;
  array_length_ = 0;
  size_ = sizeof(default_value);
  default_value_ptr_ = &default_value;
  eeprom_index_ = s_eeprom_index;
  s_eeprom_index += getSize();
}

template<typename T>
SavedVariable::SavedVariable(const T default_value[],
                             const unsigned int array_length)
{
  array_element_size_ = sizeof(T);
  array_length_ = array_length;
  size_ = array_length*array_element_size_;
  default_value_ptr_ = default_value;
  eeprom_index_ = s_eeprom_index;
  s_eeprom_index += getSize();
}

template<typename T>
int SavedVariable::getDefaultValue(T &value)
{
  int i = 0;
  if (sizeof(value) == size_)
  {
    byte* p = (byte*)(void*)&value;
    byte* q = (byte*)(void*)default_value_ptr_;
    for (i = 0; i < size_; i++)
    {
      *p++ = *q++;
    }
  }
  return i;
}

template<typename T>
int SavedVariable::getDefaultValue(T &value, unsigned int array_index)
{
  int i = 0;
  if ((sizeof(value) == array_element_size_) && (array_index < array_length_))
  {
    byte* p = (byte*)(void*)&value;
    byte* q = (byte*)(void*)default_value_ptr_ + array_index*array_element_size_;
    for (i = 0; i < array_element_size_; i++)
    {
      if (i < size_)
      {
        *p++ = *q++;
      }
    }
  }
  return i;
}

#ifndef ARDUINO_SAM_DUE
template<typename T>
int SavedVariable::setValue(const T &value)
{
  int i = 0;
  if (sizeof(value) == size_)
  {
    const byte* p = (const byte*)(const void*)&value;
    int ee = eeprom_index_;
    for (i = 0; i < size_; i++)
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
int SavedVariable::setValue(const T &value, const unsigned int array_index)
{
  int i = 0;
  if ((sizeof(value) == array_element_size_) && (array_index < array_length_))
  {
    const byte* p = (const byte*)(const void*)&value;
    int ee = eeprom_index_ + array_index*array_element_size_;
    for (i = 0; i < array_element_size_; i++)
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
int SavedVariable::getValue(T &value)
{
  int i = 0;
  if (sizeof(value) == size_)
  {
    byte* p = (byte*)(void*)&value;
    int ee = eeprom_index_;
    for (i = 0; i < size_; i++)
    {
      *p++ = EEPROM.read(ee++);
    }
  }
  return i;
}

template<typename T>
int SavedVariable::getValue(T &value, unsigned int array_index)
{
  int i = 0;
  if ((sizeof(value) == array_element_size_) && (array_index < array_length_))
  {
    byte* p = (byte*)(void*)&value;
    int ee = eeprom_index_ + array_index*array_element_size_;
    for (i = 0; i < array_element_size_; i++)
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
int SavedVariable::setValue(const T &value)
{
  int i = 0;
  return i;
}

template<typename T>
int SavedVariable::setValue(const T &value, const unsigned int array_index)
{
  int i = 0;
  return i;
}

template<typename T>
int SavedVariable::getValue(T &value)
{
  return getDefaultValue(value);
}

template<typename T>
int SavedVariable::getValue(T &value, unsigned int array_index)
{
  return getDefaultValue(value,array_index);
}

#endif

#endif
