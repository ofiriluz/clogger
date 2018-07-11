/**
 * @brief 
 * 
 * @file CWriter.h
 * @author ofir iluz
 * @date 2018-07-10
 */

#ifndef CLOGGER_CWRITERS_CWRITER_H_
#define CLOGGER_CWRITERS_CWRITER_H_

#include <CLogger/CChannel.h>
#include <CLogger/CConfig.h>

namespace CLogger
{
    class CWriter
    {
    private:
        const CWriterConfig config_;

    protected:
        /**
         * @brief 
         * Protected Getter for the writer config
         * Only inherited writers may see the config and use it
         * 
         * @return const CWriterConfig& 
         */
        const CWriterConfig &get_config() const;

    public:
        /**
         * @brief Construct a new CWriter object
         * 
         * @param config 
         */
        CWriter(const CWriterConfig &config);
        /**
         * @brief Destroy the CWriter object
         * 
         */
        virtual ~CWriter();
        /**
         * @brief 
         * Writes the contents of a given log and its channel to this writer
         * @param log 
         * @param channel 
         */
        virtual void write(const CLog &log, const CChannelPtr &channel) = 0;
    };
    typedef std::shared_ptr<PSWriter> PSWriterPtr;
}

#endif /* CLOGGER_CWRITERS_CWRITER_H_ */
