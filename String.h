// String.h
#pragma once
#ifndef STRING__H
#define STRING__H

// forward declaration
class domain_error;
class ostream;
class istream;
template<class T> class RCPtr;
class RCObject;

class String {
public:
	String( const char* initValue = "" );  
	String( const String& rhs );
	~String();                                    
     
	String& operator=( const String& rhs );

	operator char*() const
	{ return value->data; }
	
	operator const char*() const
	{ return value->data; }

	class CharProxy {    // proxies for string chars
	public:
		CharProxy(String& str, int index); // creation
		CharProxy& operator=(const CharProxy& rhs); // lvalue
		CharProxy& operator=(char c);               // uses
		operator char() const;                      // rvalue
													// use
		char* operator&();				// lvalue use
		const char* operator&() const;  // rvalue use
	private:
		String& theString;  // string this proxy pertains to
		int charIndex;      // char within that string
							// this proxy stands for
	};
	// continuation of String class
	const CharProxy	operator[](int index) const; // for const Strings
	CharProxy operator[](int index);			 // for non-const Strings

//	char& operator[]( int index ) throw( domain_error );            // for non-const String
//	const char& operator[]( int index ) const throw( domain_error ); // for const String

private:
	struct StringValue : public RCObject {      
		char* data;          // a string value      
		StringValue(const char* initValue);
		StringValue(const StringValue& rhs);
		void init(const char* initValue);
		~StringValue();
	};
    
	RCPtr<StringValue> value;         

friend class CharProxy;
friend std::istream& operator>>(std::istream& input, String& r);
friend std::ostream& operator<<(std::ostream& output, const String& r);
};

#endif  // STRING__H
