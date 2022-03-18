#include <iostream>
#include "RCPtr.h"
#include "RCObject.h"
#include "String.h"

int main()
{
	String a, b, c, d, e;
	a = b = c = d = e = "Hello";  // convert char* to String first
								  // then call String::operator=
	
	const String f = a;
	char letter = f[4];
	a[4] = 'a';
	std::cin >> b;    // type "test\n"
	std::cout << b;   

	String s1 = "Hello";
	char *p = &s1[1];
	String s2 = s1;
	*p = 'x';   // modifies both s1 and s2!

	String s4, s5; 
	s4 = s5 = f;
	std::cout << s4[5];
	s5[5] = 'x';
	s4[3] = s5[8]; 

	const String s3 = "ABCD";
	//char *p1 = &s3[0];	// error!
	//*p1 = 'a';
	return 1;
}