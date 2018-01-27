#ifndef vector_h
#define vector_h
#include "Arduino.h"

template <typename T>
class Vector
{
  private:

	size_t v_size;
	T *v_data; 
  public:
	Vector() : v_size(0),v_data(0) {};
	size_t size() const { return v_size; }; 
    void push_back( const T &x){ v_data[v_size++]=x; };
	T const &operator[](size_t idx) const { return v_data[idx]; };
    T &operator[](size_t idx) { return v_data[idx]; }; 
};

#endif
