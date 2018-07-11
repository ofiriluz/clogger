/**
 * @brief 
 * 
 * @file CChannel.h
 * @author ofir iluz
 * @date 2018-07-10
 */

#ifndef CLOGGER_CCHANNEL_H_
#define CLOGGER_CCHANNEL_H_

#include <CLogger/CLog.h>
#include <thread>

namespace CLogger
{
    class CChannel
    {
    private:
        std::string channel_name_;
        CLogLevel channel_level_;

    public:
        /**
         * @brief Construct a new CChannel object
         * 
         * @param channel_name 
         * @param channel_level 
         */
        CChannel(const std::string &channel_name, const CLogLevel &channel_level);
        /**
         * @brief Destroy the CChannel object
         * 
         */
        virtual ~CChannel();
        /**
         * @brief 
         * Getter For this channel log level
         * Depending on the Logger log level this channel will be outputted or not
         * 
         * @return CLogLevel 
         */
        CLogLevel get_log_level() const;
        /**
         * @brief 
         * Setter For this channel log level
         * Depending on the Logger log level this channel will be outputted or not
         * 
         * @param channel_level 
         */
        void set_log_level(const CLogLevel &channel_level);
        /**
         * @brief
         * Getter for the channel name
         * Will be represented on the log
         * 
         * @return std::string 
         */
        std::string get_channel_name() const;

        friend class CManager;
    };
    typedef std::shared_ptr<CChannel> CChannelPtr;
}

#endif /* CLOGGER_CCHANNEL_H_ */
