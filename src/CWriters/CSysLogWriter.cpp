/**
 * @brief 
 * 
 * @file CSysLogWriter.cpp
 * @author ofir iluz
 * @date 2018-07-10
 */

#include <CLogger/CWriters/CSysLogWriter.h>

namespace CLogger
{
  CSysLogWriter::CSysLogWriter(const CWriterConfig & config)
      :CWriter(config)
  {
      syslog_name_ = config.get_option_default(CWriterOption::WO_CONSOLE_DISABLE_COLOR, "CLogger");
  }

  CSysLogWriter::~CSysLogWriter()
  {

  }

  void CSysLogWriter::write(const CLog & log, const CChannelPtr & channel)
  {
      // Check if the stream is not null
      if(log.get_stream())
      {
          // Create a temp buffer for date time formatting
          char dtf[1024];
          
          // Format the log time
          std::time_t time = std::chrono::system_clock::to_time_t(log.get_time_created());
          std::strftime(dtf, sizeof(dtf), "[%d/%m/%Y %H:%M:%S]",std::localtime(&time));;

          std::stringstream ss;
          ss << dtf << "[" << channel->get_channel_name() << "][" << CLog::level_to_string(log.get_log_level()) 
                    << "]: "
                    << log.get_stream()->str();

          // Write to syslog
          openlog(syslog_name_.c_str(), LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
          syslog(LOG_INFO, ss.str().c_str(), NULL);
          closelog();
      }
  }
}


