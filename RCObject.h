// RCObject.h
#pragma once
#ifndef RCOBJECT__H
#define RCOBJECT__H

// forward declaration


class RCObject {                       // base class for reference-
public:                                // counted objects
	void addReference();
	void removeReference();

	void markUnshareable();
	bool isShareable() const;

	bool isShared() const;

protected:
	RCObject();
	RCObject(const RCObject& rhs);
	RCObject& operator=(const RCObject& rhs);
	virtual ~RCObject() = 0;

private:
	int refCount;
	bool shareable;
};

#endif  // RCOBJECT__H