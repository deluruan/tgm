
#ifndef HEADER_MY 
#define HEADER_MY 
#include <string> 
#include <sstream> 
template<class T> 
T fromString(const std::string &s) 
{ 
    std::istringstream is(s); 
    T t; 
    is>>t; 
    return t; 
} 
template<class T> 
std::string toString(const T &s) 
{ 
    std::ostringstream t; 
    t<<s; 
    return t.str(); 
} 
  
#endif 

