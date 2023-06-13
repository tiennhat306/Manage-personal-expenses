/*
 * File: vector.h
 * --------------
 * This file exports the Vector class, which provides an efficient, safe,
 * convenient replacement for the array type in C++.
 */
#pragma once
#ifndef _vector_h
#define _vector_h


#include <iostream>
#include <sstream>
#include <string>


/*
 * Class: Vector<ValueType>
 * ------------------------
 * This class stores an ordered list of values similar to an array.  It
 * supports traditional array selection using square brackets, but also
 * supports inserting and deleting elements.  It is similar in function to
 * the STL vector type, but is simpler both to use and to implement.
 */

template <typename ValueType>
class Vector 
{

public:

   Vector();
   Vector(int n, ValueType value = ValueType());
   virtual ~Vector();
   int size() const;
   bool isEmpty() const;
   void clear();
    const ValueType & get(int index) const;

   void set(int index, const ValueType & value);

   void insert(int index, ValueType value);

   void erase(int index);
   void add(ValueType value);
   void push_back(ValueType value);
   ValueType & operator[](int index);
   const ValueType & operator[](int index) const;
   //Vector operator+(const Vector & v2) const;
   //Vector & operator+=(const Vector & v2);
   Vector & operator+=(const ValueType & value);
   //std::string toString();
//    void mapAll(void (*fn)(ValueType)) const;
//    void mapAll(void (*fn)(const ValueType &)) const;

//    template <typename FunctorType>
//    void mapAll(FunctorType fn) const;

private:

   ValueType *elements;        /* A dynamic array of the elements   */
   int capacity;               /* The allocated size of the array   */
   int count;                  /* The number of elements in use     */


   void expandCapacity();
   void deepCopy(const Vector & src);

public:

   Vector(const Vector & src);
   Vector & operator=(const Vector & src);

   Vector & operator,(const ValueType & value);

};



#endif