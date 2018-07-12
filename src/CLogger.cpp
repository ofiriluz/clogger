/**
 * @brief 
 * 
 * @file CLogger.cpp
 * @author your name
 * @date 2018-07-11
 */

#include <CLogger/CLogger.h>
#include <CLogger/CManager.h>

namespace CLogger
{
    void CLogger::write_log(const CLog &log) const
    {
        CManager::get_instance().write(log, logger_channel_);
    }

    CLogger::CLogger(const std::string &channel)
    {
        logger_channel_ = CManager::get_instance().get_channel(channel);
    }

    CLogger::~CLogger()
    {
    }

    const CChannelPtr &CLogger::get_logger_channel() const
    {
        return logger_channel_;
    }

    CLog CLogger::debug()
    {
        return CLog(CLogLevel::LL_DEBUG, *this);
    }

    CLog CLogger::info()
    {
        return CLog(CLogLevel::LL_INFO, *this);
    }

    CLog CLogger::notice()
    {
        return CLog(CLogLevel::LL_NOTICE, *this);
    }

    CLog CLogger::warning()
    {
        return CLog(CLogLevel::LL_WARNING, *this);
    }

    CLog CLogger::error()
    {
        return CLog(CLogLevel::LL_ERROR, *this);
    }
}