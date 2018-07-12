/**
 * @brief 
 * 
 * @file CConsoleWriter.h
 * @author ofir iluz
 * @date 2018-07-10
 */

#ifndef CLOGGER_CWRITERS_CCONSOLEWRITER_H_
#define CLOGGER_CWRITERS_CCONSOLEWRITER_H_

#include <CLogger/CWriters/CWriter.h>
#include <iostream>

namespace CLogger
{
    class CConsoleWriter : public CWriter
    {
    private:
        bool disable_console_color_;

    private:
        /**
         * Changes the console log color for the fitting level
         * @param log_level
         */
        void configure_log_color(const CLogLevel &log_level);
        /**
         * Resets the log color
         */
        void reset_log_color();

    public:
        /**
         * Constructor
         * @param config
         */
        CConsoleWriter(const CWriterConfig &config);
        /**
         * Destructor
         */
        virtual ~CConsoleWriter();
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
