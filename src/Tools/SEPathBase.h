
#ifndef SEPathBase_H
#define SEPathBase_H


#include "SEIncludeLibrary.h"
#include "SEDefinition.h"


class SEPathBase;

typedef shared_ptr<SEPathBase> SEPathPtr;
typedef vector< SEPathPtr, SEAllocator<SEPathPtr> > SEPathArray;

class SEPathBase
{
protected:
	path mPath;

public:

	static void CurrentDirectory(SEPathBase* outPath);

	SEPathBase(const sechar* _cString);
	SEPathBase(const SEPathBase* pathBase);
	SEPathBase(void);
	virtual ~SEPathBase(void);

	virtual void Init( const sechar* _cString);
	const sechar* cString() const;
	const sechar* name() const;
	const SEString Extension() const;
	void AppendName( const char* name );

	SEPathBase ParentPath() const;

	virtual void ChildArray(SEPathArray* pathArray) const;
	virtual bool IsFolder() const;
};

typedef SEPathBase SEPath;


#endif SEPathBase_H

