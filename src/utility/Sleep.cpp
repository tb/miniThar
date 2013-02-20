#include "Sleep.h"

namespace utility
{

#ifdef WIN32

#include <windows.h>
void sleep( unsigned long msec)
{
	Sleep (msec);
}

#else

#include <unistd.h>
void sleep( unsigned long msec )
{
	usleep(msec*1000);
}

#endif

}