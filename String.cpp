// String.cpp
#include <stdexcept>  // domain_error
#include <string>	  // strcpy, strlen, string
#include <iostream>   // istream, ostream
#include "RCPtr.h"
#include "RCObject.h"
#include "String.h"

/////////////////////////
// Implementation of String::StringValue

void String::StringValue::init(const char *initValue)
{
	data = new char[strlen(initValue) + 1];
	strcpy(data, initValue);
}

String::StringValue::StringValue(const char* initValue)
{ init(initValue); }

String::StringValue::StringValue(const StringValue& rhs)
{ init(rhs.data); }

String::StringValue::~StringValue()
{ delete [] data; }


/////////////////////////
// Implementation of String

String::String(const char *initValue)
: value( new StringValue(initValue) )
{}

String::String(const String& rhs)
{
	if( rhs.value->isShared() ) {
		value = rhs.value;
	}
	else {
		value = new StringValue(rhs.value->data);
	}
}

String::~String()
{}

String& String::operator=(const String& rhs)
{
	if(value->data == rhs.value->data ) {   // do nothing if the values
		return *this;						// are already the same;
	} 
	if( rhs.value->isShareable() ) {
		value = rhs.value;		// have *this share rhs's
	}
	else {
		value = new StringValue(rhs.value->data);
	}
	return *this;
}

//char& String::operator[]( int index )    // for non-const String
//{ 
//	if( static_cast<size_t>(index) >= strlen(value->data) ) 
//		throw std::domain_error("String::operator[] index out of range"); 
//
//	// if we're sharing a value with other String objects,
//	// break off a separate copy of the value for ourselves
//	if( value->isShared() ) 
//	{
//		value->removeReference(); // decrement current value's
//                                  // refCount, because we won't
//                                  // be using that value any more
//
//		value =                            // make a copy of the
//			new StringValue(value->data);  // value for ourselves
//	}
//	value->markUnshareable();
//	// return a reference to a character inside our
//	// unshared StringValue object
//	return value->data[index];
//}


//const char& String::operator[]( int index ) const // for const String
//{ 
//	return index < static_cast<int>( strlen(value->data) ) ? 
//		value->data[index] : 
//	    throw std::domain_error("const String::operator[] index out of range"); 
//}

/////////////////////////
// Implementation of String::CharProxy
String::CharProxy::CharProxy(String& str, int index)
: theString(str), charIndex(index) {}

const String::CharProxy String::operator[](int index) const
{
	return CharProxy(const_cast<String&>(*this), index);
}

String::CharProxy String::operator[](int index)
{
	return CharProxy(*this, index);
}

String::CharProxy& String::CharProxy::operator=(const CharProxy& rhs) 
{	// lvalue uses
	// if the string is sharing a value with other String objects,
	// break off a separate copy of the value for this string only
	if (theString.value->isShared()) {
		theString.value = new StringValue(theString.value->data);
	}

	// now make the assignment: assign the value of the char
	// represented by rhs to the char represented by *this
	theString.value->data[charIndex] =
		rhs.theString.value->data[rhs.charIndex];
	return *this;
}

String::CharProxy& String::CharProxy::operator=(char c)	// lvalue uses
{
	if (theString.value->isShared()) {
		theString.value = new StringValue(theString.value->data);
	}
	theString.value->data[charIndex] = c;
	return *this;
}

String::CharProxy::operator char() const	// rvalue uses
{
	return theString.value->data[charIndex];
}

const char* String::CharProxy::operator&() const  // rvalue uses
{
	return &( theString.value->data[charIndex] );
}

char* String::CharProxy::operator&() // lvalue uses
{
	// make sure the character to which this function returns
	// a pointer isn't shared by any other String objects
	if (theString.value->isShared()) {
		theString.value = new StringValue(theString.value->data);
	}
	// we don't know how long the pointer this function
	// returns will be kept by clients, so the StringValue
	// object can never be shared
	theString.value->markUnshareable();

	return &(theString.value->data[charIndex]);
}

// friend functions
std::istream& operator>>(std::istream& input, String& r)
{
	std::string temp;
	input >> temp;
	r = String( temp.c_str() );
	return input; 
}

std::ostream& operator<<(std::ostream& output, const String& r)
{
	return output << (r.value)->data << std::endl;
}
