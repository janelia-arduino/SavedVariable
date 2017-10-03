// ----------------------------------------------------------------------------
// SavedVariable.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SAVED_VARIABLE_H
#define SAVED_VARIABLE_H

#ifndef ARDUINO_SAM_DUE
#include <EEPROM.h>
#endif

#include <Arduino.h>


class SavedVariable
{
public:
  SavedVariable();
  template<typename T>
  SavedVariable(const T & default_value);
  template<typename T, size_t N>
  SavedVariable(const T (&default_value)[N]);
  template<typename T>
  size_t getDefaultValue(T & value);
  template<typename T>
  size_t getDefaultElementValue(const size_t element_index, T & value);
  template<typename T>
  size_t setValue(const T &value);
  template<typename T>
  size_t setElementValue(const size_t element_index, const T & value);
  template<typename T>
  size_t getValue(T & value);
  template<typename T>
  size_t getElementValue(const size_t element_index, T & value);
  void setValueToDefault();
  void setElementValueToDefault(const size_t element_index);
  bool valueIsDefault();
  template<typename T>
  bool setDefaultValue(const T & default_value);
  template<typename T, size_t N>
  bool setDefaultValue(const T (&default_value)[N]);
  size_t getSize();
  size_t getArrayLength();
  bool setArrayLength(const size_t array_length);
  size_t getArrayLengthMax();
  void setArrayLengthToMax();
  size_t getArrayElementSize();
private:
  static size_t s_eeprom_index;
  size_t eeprom_index_;
  size_t size_;
  const void * default_value_ptr_;
  size_t array_length_;
  size_t array_length_max_;
  size_t array_length_max_at_construction_;
  size_t array_element_size_;
};
#include "SavedVariable/SavedVariableDefinitions.h"
#endif
