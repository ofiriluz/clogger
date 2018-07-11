/**
 * @brief 
 * 
 * @file CLog.h
 * @author ofir iluz
 * @date 2018-07-10
 */

#ifndef CLOGGER_CLOG_H_
#define CLOGGER_CLOG_H_

#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

namespace CLogger
{
    class CLogger;
    enum class CLogLevel : uint8_t
    {
        LL_DEBUG,
        LL_INFO,
        LL_NOTICE,
        LL_WARNING,
        LL_ERROR
    };
    class CLog
    {
    private:
        std::ostringstream *stream_;
        CLogLevel log_level_;
        const CLogger &logger_;
        std::chrono::time_point<std::chrono::system_clock> time_created_;

    private:
        /**
         * @brief 
         * Private Constructor, Only the logger can create Logs
         * 
         * @param log_level 
         * @param logger 
         */
        CLog(const CLogLevel &log_level, const CLogger &logger);

    public:
        /**
         * @brief Destroy the PSLog object
         * 
         */
        virtual ~CLog();
        /**
         * @brief 
         * Converts a given log level to string representation
         * 
         * @param level 
         * @return std::string 
         */
        static std::string level_to_string(const CLogLevel &level);
        /**
         * @brief
         * Converts a given log level string to its enum
         * 
         * @param level_str
         * @return CLogLevel
         */
        static CLogLevel string_to_level(const std::string &level_str);
        /**
         * @brief
         * Getter for this log's creation time
         * 
         * @return const std::chrono::time_point<std::chrono::system_clock>& 
         */
        const std::chrono::time_point<std::chrono::system_clock> &get_time_created() const;
        /**
         * @brief 
         * Getter for this log's stream
         * 
         * @return const std::ostringstream* 
         */
        const std::ostringstream *get_stream() const;
        /**
         * @brief
         * Getter for this log's level
         * 
         * @return CLogLevel
         */
        const CLogLevel &get_log_level() const;
        /**
         * @brief
         * Writer stream operator
         * 
         * @tparam T
         * @param value
         * @return CLog
         */
        template <class T>
        CLog &operator<<(const T &value)
        {
            if (stream_)
            {
                *stream_ << value;
            }
            return *this;
        }

        friend class CLogger;
    };
}

#endif /* CLOGGER_CLOG_H_ */
