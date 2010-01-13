
#ifndef SEFileLineReader_H
#define SEFileLineReader_H

#include "SEIncludeLibrary.h"
#include "SEFileReaderBase.h"

class SEFileLineReader: public SEFileReader
{
	SEString stringBuffer;
	int lastEndOfLineIndex;

public:
	SEFileLineReader(void);
	~SEFileLineReader(void);

	virtual void HandleString(const sechar* string, bool isEndOfFile);
};

#endif SEFileLineReader_H
