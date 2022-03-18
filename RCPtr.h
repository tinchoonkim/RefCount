// RCPtr.h
#pragma once
#ifndef RCPtr__H
#define RCPtr__H

template<class T>                       // template class for smart
class RCPtr {                           // pointers-to-T objects; T
public:                                 // must inherit from RCObject
	RCPtr(T* realPtr = 0);
	RCPtr(const RCPtr& rhs);
	~RCPtr();

	RCPtr& operator=(const RCPtr& rhs);

	T* operator->() const;
	T& operator*() const; 
		
private:
	T* pointee;

	void init();
};

/////////////////////
// Implementation of RCPtr

template<class T>
void RCPtr<T>::init()
{
	if( pointee == 0 ) 
		return;
	if( pointee->isShareable() == false ) 
	{
		pointee = new T(*pointee);
	}
	pointee->addReference();
}

template<class T>
RCPtr<T>::RCPtr(T* realPtr) : pointee(realPtr)
{ 
	init(); 
}

template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs) : pointee(rhs.pointee)			
{ init(); }

template<class T>
RCPtr<T>::~RCPtr()
{ 
	if( pointee )
		pointee->removeReference(); 
}

template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
	if( pointee != rhs.pointee ) 
	{
		if( pointee ) 
			pointee->removeReference();
		pointee = rhs.pointee;
		init();
	}
	return *this;
}

template<class T>
T* RCPtr<T>::operator->() const 
{ return pointee; }

template<class T>
T& RCPtr<T>::operator*() const 
{ return *pointee; }

#endif  // RCPtr__H