#ifndef _map_cpp
#define _map_cpp

#include "Map.h"

template <typename KeyType, typename ValueType>
Map<KeyType,ValueType>::Map() {
   root = NULL;
   nodeCount = 0;
   cmpp = new TemplateComparator< less<KeyType> >(less<KeyType>());
}

template <typename KeyType, typename ValueType>
Map<KeyType,ValueType>::~Map() {
   if (cmpp != NULL) delete cmpp;
   deleteTree(root);
}

template <typename KeyType, typename ValueType>
int Map<KeyType,ValueType>::size() const {
   return nodeCount;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType,ValueType>::isEmpty() const {
   return nodeCount == 0;
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::put(const KeyType & key,
                                 const ValueType & value) {
   bool dummy;
   *addNode(root, key, dummy) = value;
}

template <typename KeyType, typename ValueType>
ValueType Map<KeyType,ValueType>::get(const KeyType & key) const {
   ValueType *vp = findNode(root, key);
   if (vp == NULL) return ValueType();
   return *vp;
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::remove(const KeyType & key) {
   removeNode(root, key);
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::clear() {
   deleteTree(root);
   root = NULL;
   nodeCount = 0;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType,ValueType>::containsKey(const KeyType & key) const {
   return findNode(root, key) != NULL;
}

template <typename KeyType, typename ValueType>
ValueType & Map<KeyType,ValueType>::operator[](const KeyType & key) {
   bool dummy;
   return *addNode(root, key, dummy);
}

template <typename KeyType, typename ValueType>
ValueType Map<KeyType,ValueType>::operator[](const KeyType & key) const {
   return get(key);
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::mapAll(void (*fn)(KeyType, ValueType)) const {
   mapAll(root, fn);
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::mapAll(void (*fn)(const KeyType &,
                                               const ValueType &)) const {
   mapAll(root, fn);
}

template <typename KeyType, typename ValueType>
template <typename FunctorType>
void Map<KeyType,ValueType>::mapAll(FunctorType fn) const {
   mapAll(root, fn);
}

template <typename KeyType, typename ValueType>
std::string Map<KeyType,ValueType>::toString() {
   ostringstream os;
   os << *this;
   return os.str();
}

/*
 * Implementation notes: << and >>
 * -------------------------------
 * The insertion and extraction operators use the template facilities in
 * strlib.h to read and write generic values in a way that treats strings
 * specially.
 */

template <typename KeyType, typename ValueType>
std::ostream & operator<<(std::ostream & os,
                          const Map<KeyType,ValueType> & map) {
   os << "{";
   typename Map<KeyType,ValueType>::iterator begin = map.begin();
   typename Map<KeyType,ValueType>::iterator end = map.end();
   typename Map<KeyType,ValueType>::iterator it = begin;
   while (it != end) {
      if (it != begin) os << ", ";
      writeGenericValue(os, *it, false);
      os << ":";
      writeGenericValue(os, map[*it], false);
      ++it;
   }
   return os << "}";
}

template <typename KeyType, typename ValueType>
std::istream & operator>>(std::istream & is, Map<KeyType,ValueType> & map) {
   char ch;
   is >> ch;
   if (ch != '{') error("operator >>: Missing {");
   map.clear();
   is >> ch;
   if (ch != '}') {
      is.unget();
      while (true) {
         KeyType key;
         readGenericValue(is, key);
         is >> ch;
         if (ch != ':') error("operator >>: Missing colon after key");
         ValueType value;
         readGenericValue(is, value);
         map[key] = value;
         is >> ch;
         if (ch == '}') break;
         if (ch != ',') {
            error(std::string("operator >>: Unexpected character ") + ch);
         }
      }
   }
   return is;
}

#endif