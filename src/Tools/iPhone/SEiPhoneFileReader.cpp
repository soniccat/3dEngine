
#include "SEiPhoneFileReader.h"
#include "SEPathBase.h"

#define SEWindowsFileReader_BUFFER_LENGHT 1024

SEWindowsFileReader::SEWindowsFileReader(void)
{
	//mhFile = INVALID_HANDLE_VALUE;
}

SEWindowsFileReader::~SEWindowsFileReader(void)
{
}

void SEWindowsFileReader::Load(const SEPathBase* filePath)
{
	TRACE( filePath->cString() );
	SEFileReaderBase::Load(filePath);

	sechar buffer[SEWindowsFileReader_BUFFER_LENGHT];
	//size_t readed = 1;
	
	FILE* file = fopen(filePath->cString(), "r");
	
	while( feof(file) == 0 )
	{
		memset(buffer,0,sizeof(buffer));
		
		//fgets( buffer, SEWindowsFileReader_BUFFER_LENGHT-1, file );
		fread(buffer, SEWindowsFileReader_BUFFER_LENGHT-1, 1, file);
		
		HandleString( buffer, feof(file) );
	}
	
	fclose(file);
	
	/*
	mhFile = CreateFile( filePath->cString(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	//SEAssert( mhFile != INVALID_HANDLE_VALUE, filePath->cString() );
	if( mhFile == INVALID_HANDLE_VALUE )
	{
		INIT_ERROR( "File not open" );
		return;
	}

	//read file
	sechar buffer[SEWindowsFileReader_BUFFER_LENGHT];
	DWORD readed = 1;

	while(true)
	{
		memset(buffer,0,sizeof(buffer));

		if( !ReadFile( mhFile, buffer, SEWindowsFileReader_BUFFER_LENGHT-1, &readed , NULL) )
		{
			SEAssert(false, "error when file read");
			break;
		}

		buffer[readed]='\0';
		HandleString( buffer, readed == 0 );

		if(!readed)
			break;
	}

	Close();
	*/
}

void SEWindowsFileReader::Close()
{
	SEFileReaderBase::Close();

	/*
	if( mhFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle(mhFile);
		mhFile = INVALID_HANDLE_VALUE;
	}
	*/
}