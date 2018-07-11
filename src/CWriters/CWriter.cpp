/**
 * @brief 
 * 
 * @file CWriter.cpp
 * @author ofir iluz
 * @date 2018-07-11
 */

#include <CLogger/CWriters/CWriter.h>

namespace CLogger
{
    const CWriterConfig &CWriter::get_config() const
    {
        return config_;
    }

    CWriter::CWriter(const CWriterConfig &config)
        : config_(config)
    {
    }

    CWriter::~CWriter()
    {
    }
}
