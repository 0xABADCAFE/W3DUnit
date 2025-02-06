
#include "headers.hpp"
#include <cstdio>

const char* Param::DEFAULT_LOGFILE  = "RAM:W3DUnitLog.txt";
const char* Param::DEFAULT_TEMPLATE = "L=LOGFILE/K,W=WIDTH/N,H=HEIGHT/N";

void Param::ItemDefaulter::readParams(Item* items, const char* tmpl)
{
	rdArgs = ::IDOS->ReadArgs(tmpl, (int32*)items, 0);
}
Param::ItemDefaulter::~ItemDefaulter()
{
	if (rdArgs) {
		::IDOS->FreeArgs(rdArgs);
	}
}
