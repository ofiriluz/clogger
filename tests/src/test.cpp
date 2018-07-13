/**
 * @brief 
 * 
 * @file test.cpp
 * @author ofir iluz
 * @date 2018-07-11
 */

#include <CLogger/CManager.h>
#include <CLogger/CLogger.h>
#include <CLogger/CConfig.h>
#include <unistd.h>

int main(int argc, char **argv)
{
   CLogger::CLogger logger("Test");
   std::shared_ptr<CLogger::CConfig> config(new CLogger::CConfig());
   CLogger::CWriterConfig file_writer_config("File", CLogger::CWriterType::LW_FILE_WRITER);
   CLogger::CWriterConfig console_writer_config("Console", CLogger::CWriterType::LW_CONSOLE_WRITER);
   CLogger::CWriterConfig syslog_writer_config("Syslog", CLogger::CWriterType::LW_SYSLOG_WRITER);
   file_writer_config.set_option(CLogger::CWriterOption::WO_FILE_LOG_FILES_PATH, "/tmp/test");
   config->add_writer(file_writer_config);
   config->add_writer(console_writer_config);
   config->add_writer(syslog_writer_config);
   CLogger::CManager::get_instance().configure(config);

   logger.debug() << "Debug";
   logger.info() << "Info";
   logger.notice() << "Notice";
   logger.warning() << "Warning";
   logger.error() << "Error";

   // Stream Test
   for(size_t i=0;i<100000;i++)
   {
      logger.debug() << "Message = " << i;
   }
}


