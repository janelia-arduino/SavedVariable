// ----------------------------------------------------------------------------
// SavedVariable.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef SAVED_VARIABLE_H
#define SAVED_VARIABLE_H
#include <EEPROM.h>
#include <Arduino.h>


class SavedVariable
{
public:
  SavedVariable();
  template<typename T>
  SavedVariable(const T & default_value);
  template<typename T,
    size_t N>
  SavedVariable(const T (&default_value)[N],
    size_t array_length_default=N);

  template<typename T>
  size_t getDefaultValue(T & default_value);
  template<typename T,
    size_t N>
  size_t getDefaultValue(T (&default_value)[N]);
  template<typename T>
  bool setDefaultValue(const T & default_value);
  template<typename T,
    size_t N>
  bool setDefaultValue(const T (&default_value)[N],
    size_t array_length_default=N);

  template<typename T>
  size_t getDefaultElementValue(size_t element_index,
    T & default_element_value);

  template<typename T>
  size_t getValue(T & value);
  template<typename T,
    size_t N>
  size_t getValue(T (&value)[N]);
  template<typename T>
  size_t setValue(const T &value);
  template<typename T,
    size_t N>
  size_t setValue(const T (&value)[N],
    size_t array_length=N);

  template<typename T>
  size_t getElementValue(size_t element_index,
    T & element_value);
  template<typename T>
  size_t setElementValue(size_t element_index,
    const T & element_value);

  void setValueToDefault();
  bool valueIsDefault();

  void setElementValueToDefault(size_t element_index);

  size_t getSize();
  size_t getArrayElementSize();

  size_t getArrayLength();
  bool setArrayLength(size_t array_length);

  size_t getArrayLengthMax();
  void setArrayLengthToMax();

  size_t getArrayLengthDefault();
  void setArrayLengthDefault(size_t array_length_default);
  void setArrayLengthToDefault();

private:
  static size_t s_eeprom_index;
  size_t eeprom_index_;
  size_t size_;
  const void * default_value_ptr_;
  size_t array_length_default_;
  size_t array_length_max_;
  size_t array_length_max_at_construction_;
  size_t array_element_size_;
};
#include "SavedVariable/SavedVariableDefinitions.h"
#endif
