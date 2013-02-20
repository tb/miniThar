#ifndef __UTILITY_LOG_H__
#define __UTILITY_LOG_H__

#include "BaseException.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

namespace utility {

    // LogMessageLevel + LoggingLevel > LOG_THRESHOLD = message logged
    #define LOG_THRESHOLD 4

    /** The level of detail to which the log will go into.
    */
    enum LoggingLevel
    {
        LL_LOW = 1,
        LL_NORMAL = 2,
        LL_BOREME = 3
    };

    /** The importance of a logged message.
    */
    enum LogMessageLevel
    {
        LML_TRIVIAL = 1,
        LML_NORMAL = 2,
        LML_CRITICAL = 3
    };

	class LogException : public utility::BaseException
	{
	public:
		LogException::LogException(const utility::BaseException& rhs) :
		  utility::BaseException(rhs)
		  {
		  }
	};

    /** Log class for writing debug/log data to files.
        @note
            <br>Should not be used directly, but trough the LogManager class.
    */
    class Log
    {
    protected:
		std::ofstream mfpLog;
        LoggingLevel mLogLevel;
        bool mDebugOut;

    public:
        /** Usual constructor - called by LogManager.
        */
		Log( const std::string& name );

        /** Default destructor.
        */
        ~Log();

        /** Log a message to the debugger and to log file (the default is
            "<code>OGRE.log</code>"),
        */
        void logMessage(
            const std::string& message,
            LogMessageLevel lml = LML_NORMAL );

        /** Sets the level of the log detail.
        */
        void setLogDetail(LoggingLevel ll);
    };

}

#endif
