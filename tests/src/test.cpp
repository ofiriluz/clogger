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
   fileWriterConfig.set_option(CLogger::CWriterOption::WO_FILE_LOG_FILES_PATH, "/tmp/test");
   config->add_writer(file_writer_config);
   config->add_writer(console_writer_config);
   CLogger::CManager::get_singleton().configure(config);

   logger.debug() << "HI";
   logger.info() << "HI2";
   logger.notice() << "HI3";
   logger.warning() << "HI4";
   logger.error() << "HI5";

   // Stream Test
   for(size_t i=0;i<1000000000000;i++)
   {
      logger.debug() << "X";
   }
}


