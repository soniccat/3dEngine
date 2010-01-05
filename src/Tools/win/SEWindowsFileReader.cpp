
#include "SEWindowsFileReader.h"
#include "SEPathBase.h"

#define SEWindowsFileReader_BUFFER_LENGHT 1024

SEWindowsFileReader::SEWindowsFileReader(void)
{
	mhFile = INVALID_HANDLE_VALUE;
}

SEWindowsFileReader::~SEWindowsFileReader(void)
{
}

