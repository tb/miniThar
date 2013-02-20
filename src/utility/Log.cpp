#include "Log.h"
//#include "OgreString.h"

namespace utility {

    //-----------------------------------------------------------------------
    Log::Log( const std::string& name )
    {
		mfpLog.open( name.c_str() );
        mLogLevel = LL_NORMAL;
    }
    //-----------------------------------------------------------------------
    Log::~Log()
    {
        mfpLog.close();
    }
    //-----------------------------------------------------------------------
    void Log::logMessage( const std::string& message, LogMessageLevel lml )
    {
        if ((mLogLevel + lml) >= LOG_THRESHOLD)
        {
            // Write time into log
            struct tm *pTime;
            time_t ctTime; time(&ctTime);
            pTime = localtime( &ctTime );
            mfpLog << std::setw(2) << std::setfill('0') << pTime->tm_hour
                << ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
                << ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec << ": " << message << std::endl;

            // Flush stcmdream to ensure it is written (incase of a crash, we need log to be up to date)
            mfpLog.flush();
        }
    }
    //-----------------------------------------------------------------------
    void Log::setLogDetail(LoggingLevel ll)
    {
        mLogLevel = ll;
    }
}
