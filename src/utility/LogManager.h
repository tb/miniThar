#ifndef __UTILITY_LOGMANAGER_H__
#define __UTILITY_LOGMANAGER_H__


#include "Singleton.h"
#include "Log.h"

#include <string>
#include <map>

namespace utility {

    /** The log manager handles the creation and retrieval of logs for the
        application.
        @remarks
            This class will create new log files and will retrieve instances
            of existing ones. Other classes wishing to log output can either
            create a fresh log or retrieve an existing one to output to.
            One log is the default log, and is the one written to when the
            logging methods of this class are called.
    */
    class LogManager : public Singleton<LogManager>
    {
    protected:
        typedef std::map<std::string, Log*, std::less<std::string> > LogList;

        /// A list of all the logs the manager can access
        LogList mLogs;

        /// The default log to which output is done
        Log* mDefaultLog;

    public:
        LogManager();
        ~LogManager();

        /** Creates a new log with the given name.
            @param
                name The name to give the log e.g. 'Ogre.log'
            @param
                defaultLog If true, this is the default log output will be
                sent to if the generic logging methods on this class are
                used. The first log created is always the default log unless
                this parameter is set.
            @param
                debuggerOutput If true, output to this log will also be
                routed to the debugger's output window.
        */
        Log* createLog( const std::string& name, bool defaultLog = false );

        /** Retrieves a log managed by this class.
        */
        Log* getLog( const std::string& name);

        /** Returns a pointer to the default log.
        */
        Log* getDefaultLog();

        /** Sets the passed in log as the default log.
        @returns The previous default log.
        */
        Log* setDefaultLog(Log* newLog);

        /** Log a message to the default log.
        */
        void logMessage( const std::string& message, LogMessageLevel lml = LML_NORMAL );

        /** Log a message, smarter form - allows a variable number of
            arguments.
            @note
                <br>The longest string that this function can output is 4096
                characters long.
        */
        void logMessage( LogMessageLevel lml, const char* szMessage, ... );

        /** Sets the level of detail of the default log.
        */
        void setLogDetail(LoggingLevel ll);
    };
}

#define LOG(msg) { std::stringstream s; s << msg; utility::LogManager::getSingletonPtr()->logMessage( s.str() ); } 

#endif
