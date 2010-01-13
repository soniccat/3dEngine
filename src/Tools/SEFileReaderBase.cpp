#include "SEFileReaderBase.h"
#include "SEPathBase.h"

#define SEFILEREADER_BUFFER_LENGHT 1024

SEFileReaderBase::SEFileReaderBase(void)
{
}

SEFileReaderBase::~SEFileReaderBase(void)
{
	Close();
}

void SEFileReaderBase::Load(const SEPathBase* filePath)
{
	Close();
	mCurrentFile = filePath;

	sechar buffer[SEFILEREADER_BUFFER_LENGHT];
	TRACE( filePath->cString() );
	
	FILE* file = fopen(filePath->cString(), "r");
	int feofFlag = feof(file);

	while( feofFlag == 0 )
	{
		memset(buffer,0,sizeof(buffer));
		
		//fgets( buffer, SEWindowsFileReader_BUFFER_LENGHT-1, file );
		fread(buffer, SEFILEREADER_BUFFER_LENGHT-1, 1, file);
		
		feofFlag = feof(file);
		HandleString( buffer, static_cast<bool>( feofFlag != 0 ) );
	}
	
	fclose(file);
}

void SEFileReaderBase::Close()
{
	mCurrentFile = NULL;
}

void SEFileReaderBase::HandleString(const sechar* string, bool isEndOfFile)
{
	if( mHandler )
		mHandler->HandleString(string, isEndOfFile);
}

void SEFileReaderBase::SetHandler( SEFileReaderHandlerInterface* _handler )
{
	mHandler = _handler;
}

SEFileReaderHandlerInterface* SEFileReaderBase::handler()
{
	return mHandler;
}
