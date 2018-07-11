/**
 * @brief 
 * 
 * @file CManager.h
 * @author ofir iluz
 * @date 2018-07-10
 */

#ifndef CLOGGER_CMANAGER_H_
#define CLOGGER_CMANAGER_H_

#include <CLogger/CLog.h>
#include <CLogger/CChannel.h>
#include <CLogger/CConfig.h>
#include <CLogger/CWriters/CWriterFactory.h>

#include <mutex>

namespace CLogger
{
    class CManager
    {
    private:
        std::map<std::string, CChannelPtr> channels_;
        std::vector<CWriterPtr> writers_;
        std::mutex writers_mutex_;
        CConfigPtr config_;
        CLogLevel default_log_level_;

    private:
        /**
         * @brief
         * Deleted Copy Constructor, Singleton Manager
         * 
         * @param other
         */
        CManager(const CManager &other) = delete;
        /**
         * @brief
         * Delete Equals Operator, Singleton Manager
         * 
         * @param other
         * @return CManager
         */
        CManager &operator=(const CManager &other) = delete;
        /**
         * @brief Construct a new CManager object
         * 
         */
        CManager();

    public:
        /**
         * @brief
         * Getter for the singleton instance of the manager
         * 
         * @return CManager
         */
        static CManager &get_instance();
        /**
         * @brief Destroy the CManager object
         * 
         */
        virtual ~CManager();
        /**
         * @brief
         * Getter for a channel for a given name if exists
         * 
         * @param name
         * @return CChannelPtr
         */
        CChannelPtr get_channel(const std::string &name);
        /**
         * @brief
         * Configures the manager for the given configuration
         * 
         * @param config
         */
        void configure(const CConfigPtr &config);
        /**
         * @brief
         * Writes a given log and channel to all the writers who can accept the level
         * 
         * @param log
         * @param channel
         */
        void write(const CLog &log, const CChannelPtr &channel);
        /**
         * @brief
         * Clears all the writers
         */
        void clear_writers();
        /**
         * @brief
         * Clears all the channels
         */
        void clear_channels();
    };
}

#endif /* CLOGGER_CMANAGER_H_ */
