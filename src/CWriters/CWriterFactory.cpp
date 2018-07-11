/**
 * @brief 
 * 
 * @file CWriterFactory.cpp
 * @author ofir iluz
 * @date 2018-07-11
 */

#include <CLogger/CWriters/CWriterFactory.h>

namespace CLogger
{
    CWriterFactory::CWriterFactory()
    {
    }

    CWriterFactory &CWriterFactory::get_instance()
    {
        static CWriterFactory factory;
        return factory;
    }

    CWriterFactory::~CWriterFactory()
    {
    }

    CWriterPtr CWriterFactory::create_writer(const CWriterConfig &writer_comfig)
    {
        if (writer_comfig.get_writer_type() == CWriterType::LW_CONSOLE_WRITER)
        {
            return CWriterPtr(new CConsoleWriter(writer_config));
        }
        else if (writer_comfig.get_writer_type() == CWriterType::LW_FILE_WRITER)
        {
            return CWriterPtr(new CFileWriter(writer_config));
        }
        return CWriterPtr();
    }
}
