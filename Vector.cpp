#pragma once
#ifndef _vector_cpp
#define _vector_cpp
/*
 * File: vector.h
 * --------------
 * This file exports the Vector class, which provides an efficient, safe,
 * convenient replacement for the array type in C++.
 */


#include "Vector.h"


//extern void error(std::string msg);

template <typename ValueType>
Vector<ValueType>::Vector() {
   count = capacity = 0;
   elements = NULL;
}

template <typename ValueType>
Vector<ValueType>::Vector(int n, ValueType value) {
   count = capacity = n;
   elements = (n == 0) ? NULL : new ValueType[n];
   for (int i = 0; i < n; i++) {
      elements[i] = value;
   }
}

template <typename ValueType>
Vector<ValueType>::~Vector() {
   if (elements != NULL) delete[] elements;
}


template <typename ValueType>
int Vector<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool Vector<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void Vector<ValueType>::clear() {
   if (elements != NULL) delete[] elements;
   count = capacity = 0;
   elements = NULL;
}

template <typename ValueType>
const ValueType & Vector<ValueType>::get(int index) const {
   if (index < 0 || index >= count) std::cout << "get: index out of range";
   return elements[index];
}

template <typename ValueType>
void Vector<ValueType>::set(int index, const ValueType & value) {
   if (index < 0 || index >= count) std::cout << "set: index out of range";
   elements[index] = value;
}


template <typename ValueType>
void Vector<ValueType>::insert(int index, ValueType value) {
   if (count == capacity) expandCapacity();
   if (index < 0 || index > count) {
      std::cout << "insert: index out of range" ;
   }
   for (int i = count; i > index; i--) {
      elements[i] = elements[i - 1];
   }
   elements[index] = value;
   count++;
}

template <typename ValueType>
void Vector<ValueType>::erase(int index) {
   if (index < 0 || index >= count) std::cout << "remove: index out of range" ;
   for (int i = index; i < count - 1; i++) {
      elements[i] = elements[i + 1];
   }
   count--;
}

template <typename ValueType>
void Vector<ValueType>::add(ValueType value) {
   insert(count, value);
}

template <typename ValueType>
void Vector<ValueType>::push_back(ValueType value) {
   insert(count, value);
}

template <typename ValueType>
ValueType & Vector<ValueType>::operator[](int index) {
   if (index < 0 || index >= count) std::cout << "Selection index out of range";
   return elements[index];
}
template <typename ValueType>
const ValueType & Vector<ValueType>::operator[](int index) const {
   if (index < 0 || index >= count) std::cout << "Selection index out of range";
   return elements[index];
}

// template <typename ValueType>
// Vector<ValueType> Vector<ValueType>::operator+(const Vector & v2) const {
//    Vector<ValueType> vec = *this;
//    foreach (ValueType value in v2) {
//       vec.add(value);
//    }
//    return vec;
// }

// template <typename ValueType>
// Vector<ValueType> & Vector<ValueType>::operator+=(const Vector & v2) {
//    foreach (ValueType value in v2) {
//       *this += value;
//    }
//    return *this;
// }

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator+=(const ValueType & value) {
   this->add(value);
   return *this;
}

// template <typename ValueType>
// std::string Vector<ValueType>::toString() {
//    ostringstream os;
//    os << *this;
//    return os.str();
// }

template <typename ValueType>
Vector<ValueType>::Vector(const Vector & src) {
   deepCopy(src);
}

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator=(const Vector & src) {
   if (this != &src) {
      if (elements != NULL) delete[] elements;
      deepCopy(src);
   }
   return *this;
}

template <typename ValueType>
void Vector<ValueType>::deepCopy(const Vector & src) {
   count = capacity = src.count;
   elements = (capacity == 0) ? NULL : new ValueType[capacity];
   for (int i = 0; i < count; i++) {
      elements[i] = src.elements[i];
   }
}

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator,(const ValueType & value) {
   this->add(value);
   return *this;
}
// template <typename ValueType>
// void Vector<ValueType>::mapAll(void (*fn)(ValueType)) const {
//    for (int i = 0; i < count; i++) {
//       fn(elements[i]);
//    }
// }

// template <typename ValueType>
// void Vector<ValueType>::mapAll(void (*fn)(const ValueType &)) const {
//    for (int i = 0; i < count; i++) {
//       fn(elements[i]);
//    }
// }

// template <typename ValueType>
// template <typename FunctorType>
// void Vector<ValueType>::mapAll(FunctorType fn) const {
//    for (int i = 0; i < count; i++) {
//       fn(elements[i]);
//    }
// }

template <typename ValueType>
void Vector<ValueType>::expandCapacity() {
   capacity = (1 < capacity * 2)? (capacity * 2) : 1;
   ValueType *array = new ValueType[capacity];
   for (int i = 0; i < count; i++) {
      array[i] = elements[i];
   }
   if (elements != NULL) delete[] elements;
   elements = array;
}


template <typename ValueType>
std::ostream & operator<<(std::ostream & os, const Vector<ValueType> & vec) {
   os << "{";
   int len = vec.size();
   for (int i = 0; i < len; i++) {
      if (i > 0) os << ", ";
      writeGenericValue(os, vec[i], true);
   }
   return os << "}";
}

template <typename ValueType>
std::istream & operator>>(std::istream & is, Vector<ValueType> & vec) {
   char ch;
   is >> ch;
   if (ch != '{') std::cout << "operator >>: Missing {";
   vec.clear();
   is >> ch;
   if (ch != '}') {
      is.unget();
      while (true) {
         ValueType value;
         readGenericValue(is, value);
         vec += value;
         is >> ch;
         if (ch == '}') break;
         if (ch != ',') {
            std::string str =  "operator >>: Unexpected character " + ch;
            std::cout << str;
         }
      }
   }
   return is;
}

#endif