#include "SEFileLineReader.h"

SEFileLineReader::SEFileLineReader(void)
{
	lastEndOfLineIndex		= 0;
}

SEFileLineReader::~SEFileLineReader(void)
{
}

void SEFileLineReader::HandleString(const sechar* string, bool isEndOfFile)
{
	//split string
	stringBuffer.append( string );

	int currentEndOfLineIndex  = lastEndOfLineIndex;
	SEString substring;

	while( true )
	{
		currentEndOfLineIndex = stringBuffer.find( "\n", currentEndOfLineIndex+1 );
		if( currentEndOfLineIndex == string::npos && !isEndOfFile )
		{
			//substring = stringBuffer.substr( lastEndOfLineIndex, stringBuffer.length() - 1 - lastEndOfLineIndex );
			//mHandler->HandleString( substring.c_str(), isEndOfFile );
			break;

		}else if( currentEndOfLineIndex != string::npos )
		{
			substring = stringBuffer.substr( lastEndOfLineIndex, currentEndOfLineIndex-lastEndOfLineIndex );

			lastEndOfLineIndex = currentEndOfLineIndex;
			mHandler->HandleString( substring.c_str(), isEndOfFile );

		}else
			break;
	}
}