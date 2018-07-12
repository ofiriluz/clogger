/**
 * @brief 
 * 
 * @file CChannel.cpp
 * @author ofir iluz
 * @date 2018-07-11
 */

#include <CLogger/CChannel.h>

namespace CLogger
{
    CChannel::CChannel(const std::string &channel_name, const CLogLevel &channel_level)
        : channel_name_(channel_name), channel_level_(channel_level)
    {
    }

    CChannel::~CChannel()
    {
    }

    CLogLevel CChannel::get_log_level() const
    {
        return channel_level_;
    }

    void CChannel::set_log_level(const CLogLevel &channel_level)
    {
        channel_level_ = channel_level;
    }

    std::string CChannel::get_channel_name() const
    {
        return channel_name_;
    }
}
