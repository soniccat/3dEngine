#pragma once

#include "SEPathBase.h"

class SEWindowsPath: public SEPathBase
{
	bool mIsFolder;
public:

	virtual void Init( const sechar* _cString);
	virtual void ChildArray(SEPathArray* pathArray) const;
	virtual bool IsFolder() const;
};

typedef SEWindowsPath EPath;