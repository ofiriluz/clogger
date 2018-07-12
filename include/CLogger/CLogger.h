/**
 * @brief 
 * 
 * @file CLogger.h
 * @author ofir iluz
 * @date 2018-07-10
 */

#ifndef CLOGGER_CLOGGER_H_
#define CLOGGER_CLOGGER_H_

#include <CLogger/CChannel.h>
#include <mutex>
#include <stdexcept>

namespace CLogger
{
    class CLogger
    {
    private:
        CChannelPtr logger_channel_;

    private:
        /**
         * @brief
         * Writes the log to the needed channel through the logger manager
         * 
         * @param log
         */
        void write_log(const CLog &log) const;

    public:
        /**
         * @brief Construct a new CLogger object
         * 
         * @param channel 
         */
        CLogger(const std::string &channel);
        /**
         * @brief Destroy the CLogger object
         * 
         */
        virtual ~CLogger();
        /**
         * @brief 
         * Getter for this loggers channel
         * 
         * @return const PSChannelPtr& 
         */
        const CChannelPtr &get_logger_channel() const;
        /**
         * @brief
         * Getter for the debug logger
         * Will write the contents of this log when it dies
         * 
         * @return CLog
         */
        CLog debug();
        /**
         * @brief
         * Getter for the info logger
         * Will write the contents of this log when it dies
         * 
         * @return CLog
         */
        CLog info();
        /**
         * @brief
         * Getter for the notice logger
         * Will write the contents of this log when it dies
         * 
         * @return CLog
         */
        CLog notice();
        /**
         * @brief
         * Getter for the warning logger
         * Will write the contents of this log when it dies
         * 
         * @return CLog
         */
        CLog warning();
        /**
         * @brief
         * Getter for the error logger
         * Will write the contents of this log when it dies
         * 
         * @return CLog
         */
        CLog error();

        friend class CLog;
    };
}

#endif /* CLOGGER_CLOGGER_H_ */
