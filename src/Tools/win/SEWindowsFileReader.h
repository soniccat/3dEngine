#pragma once

#include <windows.h>
#include "SEIncludeLibrary.h"
#include "SEFileReaderBase.h"

class SEWindowsFileReader: public SEFileReaderBase
{
protected:
	HANDLE mhFile;

public:
	SEWindowsFileReader(void);
	virtual ~SEWindowsFileReader(void);
};

typedef SEWindowsFileReader EFileReader;