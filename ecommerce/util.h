#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <iostream>
#include <set>

std::string convToLower(std::string src); //Convert string to all lower case and returns it?
std::set<std::string> parseStringToWords(std::string line); //Parses string into keywords that can be used as index (keywords for a given ADT)

template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> result;
  for(typename std::set<T>::iterator it = s1.begin();
      it != s1.end();
      ++it){
    if(s2.find(*it) != s2.end()){
      result.insert(*it);
    }
  }
  return result;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> result = s2;
  for(typename std::set<T>::iterator it = s1.begin();
      it != s1.end();
      ++it){
    if(result.find(*it) == result.end()){
      result.insert(*it);
    }
  }
  return result;
}

#endif
