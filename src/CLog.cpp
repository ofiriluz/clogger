/**
 * @brief 
 * 
 * @file CLog.cpp
 * @author ofir iluz
 * @date 2018-07-11
 */

#include <CLogger/CLog.h>
#include <CLogger/CLogger.h>

namespace CLogger
{
    CLog::CLog(const CLogLevel &log_level, const CLogger &logger)
        : stream_(nullptr), log_level_(log_level), logger_(logger)
    {
        if (log_level_ >= logger.get_logger_channel()->get_log_level())
        {
            stream_ = new std::ostringstream();
        }
    }

    CLog::~CLog()
    {
        if (stream_)
        {
            time_created_ = std::chrono::system_clock::now();
            logger_.write_log(*this);
            delete stream_;
        }
    }

    std::string CLog::level_to_string(const CLogLevel &level)
    {
        switch (level)
        {
        case CLogLevel::LL_DEBUG:
            return "Debug";
        case CLogLevel::LL_INFO:
            return "Info";
        case CLogLevel::LL_NOTICE:
            return "Notice";
        case CLogLevel::LL_WARNING:
            return "Warning";
        case CLogLevel::LL_ERROR:
            return "Error";
        }
    }

    CLogLevel CLog::string_to_level(const std::string &level_str)
    {
        if (level_str == "Info")
        {
            return CLogLevel::LL_INFO;
        }
        if (level_str == "Debug")
        {
            return CLogLevel::LL_DEBUG;
        }
        if (level_str == "Notice")
        {
            return CLogLevel::LL_NOTICE;
        }
        if (level_str == "Warning")
        {
            return CLogLevel::LL_WARNING;
        }
        else if (level_str == "Error")
        {
            return CLogLevel::LL_ERROR;
        }
        throw std::runtime_error("Invalid Log Level String");
    }

    const std::chrono::time_point<std::chrono::system_clock> &CLog::get_time_created() const
    {
        return time_created_;
    }

    const std::ostringstream *CLog::get_stream() const
    {
        return stream_;
    }

    const CLogLevel &CLog::get_log_level() const
    {
        return log_level_;
    }
}
