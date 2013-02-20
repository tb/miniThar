#include "LogManager.h"
#include "BaseException.h"

// Required for va_start, va_end and sprintf
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#ifdef WIN32
	#define vsnprintf _vsnprintf
#endif

namespace utility {
    //-----------------------------------------------------------------------
    LogManager::LogManager()
    {
        mDefaultLog = NULL;
    }
    //-----------------------------------------------------------------------
    LogManager::~LogManager()
    {
        // Destroy all logs
        LogList::iterator i;
        for (i = mLogs.begin(); i != mLogs.end(); ++i)
        {
            delete i->second;
        }
    }
    //-----------------------------------------------------------------------
	Log* LogManager::createLog( const std::string& name, bool defaultLog )
    {
        Log* newLog = new Log(name);

        if( !mDefaultLog || defaultLog )
        {
            mDefaultLog = newLog;
        }

        mLogs.insert( LogList::value_type( name, newLog ) );

        return newLog;
    }
    //-----------------------------------------------------------------------
    Log* LogManager::getDefaultLog()
    {
        if (!mDefaultLog)
			throw LogException( ERROR_MSG("No logs created yet.") );

        return mDefaultLog;
    }
    //-----------------------------------------------------------------------
    Log* LogManager::setDefaultLog(Log* newLog)
    {
        Log* oldLog = mDefaultLog;
        mDefaultLog = newLog;
        return oldLog;
    }
    //-----------------------------------------------------------------------
    Log* LogManager::getLog( const std::string& name)
    {
        LogList::iterator i = mLogs.find(name);
        if (i != mLogs.end())
            return i->second;
        else
			throw LogException( ERROR_MSG("Log not found.") );

    }
    //-----------------------------------------------------------------------
    void LogManager::logMessage( const std::string& message, LogMessageLevel lml )
    {
        getDefaultLog()->logMessage(message, lml );
    }
    //-----------------------------------------------------------------------
    void LogManager::logMessage( LogMessageLevel lml, const char* szMessage, ... )
    {
        static char szBuffer[4097];
        va_list list;
        va_start( list, szMessage );

        ::vsnprintf( szBuffer, 4096, szMessage, list );
        getDefaultLog()->logMessage( szBuffer, lml );

        va_end( list );
    }
    //-----------------------------------------------------------------------
    void LogManager::setLogDetail(LoggingLevel ll)
    {
        getDefaultLog()->setLogDetail(ll);
    }
}
