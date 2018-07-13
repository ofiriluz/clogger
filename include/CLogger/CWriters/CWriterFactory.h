/*
* PSWriterFactory.h
*
*  Created on: Mar 14, 2018
*      Author: root
*/

#include <string>
#include <thread>

#include <CLogger/CWriters/CFileWriter.h>
#include <CLogger/CWriters/CConsoleWriter.h>
#include <CLogger/CWriters/CSysLogWriter.h>

namespace CLogger
{
    class CWriterFactory
    {
    private:
        /**
         * @brief
         * Singleton factory, Copy constructor deleted
         * @param other 
         */
        CWriterFactory(const CWriterFactory &other) = delete;
        /**
         * @brief
         * Singleton Factory, Deleted copy operator
         * 
         * @param other
         * @return CWriterFactory
         */
        CWriterFactory operator=(const CWriterFactory &other) = delete;
        /**
         * @brief
         * Private Constructor, Singleton Factory
         */
        CWriterFactory();

    public:
        /**
         * @brief
         * Singleton Getter
         * 
         * @return CWriterFactory
         */
        static CWriterFactory &get_instance();
        /**
         * @brief Destroy the CWriterFactory object
         * 
         */
        virtual ~CWriterFactory();
        /**
         * @brief
         * Creates a writer for a given config
         * 
         * @param writer_config
         * @return CWriterPtr
         */
        CWriterPtr create_writer(const CWriterConfig &writer_config);
    };
}
