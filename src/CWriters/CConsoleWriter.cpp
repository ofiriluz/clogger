/**
 * @brief 
 * 
 * @file CConsoleWriter.cpp
 * @author ofir iluz
 * @date 2018-07-10
 */

#include <CLogger/CWriters/CConsoleWriter.h>

namespace CLogger
{
  void CConsoleWriter::configure_log_color(const CLogLevel & log_level)
  {
      switch (log_level)
      {
          case CLogLevel::LL_DEBUG:
              std::cout << "\e[32m";
              break;
          case CLogLevel::LL_INFO:
              std::cout << "\e[36m";
              break;
          case CLogLevel::LL_NOTICE:
              std::cout << "\e[34m";
              break;
          case CLogLevel::LL_WARNING:
              std::cout << "\e[33m";
              break;
          case CLogLevel::LL_ERROR:
              std::cout << "\e[31m";
              break;
      }
  }

  void CConsoleWriter::reset_log_color()
  {
      std::cout << "\e[39m";
  }

  CConsoleWriter::CConsoleWriter(const CWriterConfig & config)
      :CWriter(config)
  {
      disable_console_color_ = static_cast<bool>(config.get_option_default(CWriterOption::WO_CONSOLE_DISABLE_COLOR,0));
  }

  CConsoleWriter::~CConsoleWriter()
  {

  }

  void CConsoleWriter::write(const CLog & log, const CChannelPtr & channel)
  {
      // Check if the stream is not null
      if(log.get_stream())
      {
          // Create a temp buffer for date time formatting
          char dtf[1024];

          // Set output buffer
          if(!disable_console_color_)
          {
              configure_log_color(log.get_log_level());
          }
          
          // Format the log time
          std::time_t time = std::chrono::system_clock::to_time_t(log.get_time_created());
          std::strftime(dtf, sizeof(dtf), "[%d/%m/%Y %H:%M:%S]",std::localtime(&time));;

          // Output to console
          std::cout << dtf << "[" << channel->GetChannelName() << "][" << PSLog::LevelToString(log.GetLogLevel()) 
                    << "]: "
                    << log.GetStream()->str();

          // Reset output color
          if(!disable_console_color_)
          {
              reset_log_color();
          }

          std::cout << std::endl;
      }
  }
}


