// RCObject.cpp
#include <iostream>   // istream, ostream
#include "RCPtr.h"
#include "RCObject.h"

/////////////////////
// Implementation of RCObject

RCObject::RCObject()
: refCount(0), shareable(true) {}

RCObject::RCObject(const RCObject&)
: refCount(0), shareable(true) {}

RCObject& RCObject::operator=(const RCObject&)
{ return *this; }

RCObject::~RCObject() {}               // virtual dtors must always
                                       // be implemented, even if
                                       // they are pure virtual
                                       // and do nothing (see also
                                       // Item 33 and Item E14)

void RCObject::addReference() 
{ ++refCount; }
	
void RCObject::removeReference()
{ 
	if (--refCount == 0) 
		delete this; 
}

void RCObject::markUnshareable()
{ shareable = false; }

bool RCObject::isShareable() const
{ return shareable; }

bool RCObject::isShared() const
{ return refCount > 1; }		
