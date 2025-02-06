
#include <cstdio>
#include <typeinfo>
#include "exception.hpp"

const char* Error::Runtime::getClass() const
{
	return typeid(*this).name();
}

