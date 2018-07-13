/**
 * @brief 
 * 
 * @file CSysLogWriter.h
 * @author ofir iluz
 * @date 2018-07-10
 */

#ifndef CLOGGER_CWRITERS_CSYSLOGWRITER_H_
#define CLOGGER_CWRITERS_CSYSLOGWRITER_H_

#include <CLogger/CWriters/CWriter.h>
#include <iostream>
#include <syslog.h>

namespace CLogger
{
    class CSysLogWriter : public CWriter
    {
    private:
        std::string syslog_name_;

    public:
        /**
         * Constructor
         * @param config
         */
        CSysLogWriter(const CWriterConfig &config);
        /**
         * Destructor
         */
        virtual ~CSysLogWriter();
        /**
         * Writes the contents of the log to the console
         * @see CWriter::write
         * @param log
         * @param channel
         */
        virtual void write(const CLog &log, const CChannelPtr &channel);
    };
}

#endif /* CLOGGER_CWRITERS_CCONSOLEWRITER_H_ */
