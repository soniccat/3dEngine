
#include "SEIncludeLibrary.h"
#include "SEDefinition.h"

bool streq(const sechar *s1, const sechar *s2)
{
	for (;;) 
	{
		if( *(s1++)!=*(s2++) )
			return 0;
		
		if( *s1 == 0 && *s2 == 0 )
			return 1;
		
		if( *s1 == 0 || *s2 == 0 )
			return 0;
	}
}