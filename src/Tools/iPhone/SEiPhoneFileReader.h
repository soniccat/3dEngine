
#ifndef SEWindowsFileReader_H
#define SEWindowsFileReader_H

#include "SEIncludeLibrary.h"
#include "SEFileReaderBase.h"

class SEWindowsFileReader: public SEFileReaderBase
{
protected:
	//HANDLE mhFile;

public:
	SEWindowsFileReader(void);
	virtual ~SEWindowsFileReader(void);

	virtual void Load(const SEPathBase* filePath);
	virtual void Close();
};

typedef SEWindowsFileReader EFileReader;

#endif SEWindowsFileReader_H