/**
 * @brief 
 * 
 * @file CManager.cpp
 * @author ofir iluz
 * @date 2018-07-11
 */

#include <CLogger/CManager.h>

namespace CLogger
{
    CManager::CManager()
        : config_(new CConfig()), default_log_level_(CLogLevel::LL_DEBUG)
    {
    }

    CManager &CManager::get_instance()
    {
        static CManager manager;
        return manager;
    }

    CManager::~CManager()
    {
        clear_writers();
        clear_channels();
    }

    CChannelPtr CManager::get_channel(const std::string &name)
    {
        if (channels_.find(name) == channels_.end())
        {
            channels_[name] = CChannelPtr(new CChannel(name, default_log_level_));
        }
        return channels_[name];
    }

    void CManager::configure(const CConfigPtr &config)
    {
        clear_writers();
        config_ = config;

        // Change the default level if requested by config
        if (config_->has_option(CLoggerOption::LG_DEFAULT_CHANNEL_LEVEL))
        {
            int default_level;
            if (config_->get_option(CLoggerOption::LG_DEFAULT_CHANNEL_LEVEL, default_level))
            {
                default_log_level_ = static_cast<CLogLevel>(default_level);
            }
        }

        // Create all the writers
        for (auto &&writer_config : config_->get_writers())
        {
            CWriterPtr writer = CWriterFactory::get_instance().create_writer(writer_config);
            if (writer)
            {
                writers_.push_back(writer);
            }
        }
    }

    void CManager::write(const CLog &log, const CChannelPtr &channel)
    {
        std::lock_guard<std::mutex> lock(writers_mutex_);
        for (auto &&writer : writers_)
        {
            writer->write(log, channel);
        }
    }

    void CManager::clear_writers()
    {
        writers_.clear();
    }

    void CManager::clear_channels()
    {
        channels_.clear();
    }
}
