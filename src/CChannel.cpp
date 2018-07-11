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
        : channel_level_(channel_level), channel_name_(channel_name)
    {
    }

    CChannel::~CChannel()
    {
    }

    PSLogLevel CChannel::GetLogLevel() const
    {
        return channel_level_;
    }

    void CChannel::SetLogLevel(const PSLogLevel &channel_level)
    {
        channel_level_ = channel_level;
    }

    std::string CChannel::GetChannelName() const
    {
        return channel_name_;
    }
}
