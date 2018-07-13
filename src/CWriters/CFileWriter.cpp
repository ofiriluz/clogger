/**
 * @brief 
 * 
 * @file CFileWriter.cpp
 * @author ofir iluz
 * @date 2018-07-11
 */

#include <CLogger/CWriters/CFileWriter.h>

namespace CLogger
{
    CFileWriter::CFile::CFile() : index(0)
    {
    }

    CFileWriter::CFile::~CFile()
    {
    }

    void CFileWriter::create_log_path()
    {
        // Create a formatted date time for the log path
        char dtf[1024];
        std::chrono::time_point<std::chrono::system_clock> dt = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(dt);
        std::strftime(dtf, sizeof(dtf), "%d-%m-%Y", std::localtime(&time));

        // Handle last backslash (need to normalize better the path)
        if (log_path_.data()[log_path_.size() - 1] != '/')
        {
            log_path_ += '/';
        }

        // Add the prefix if given
        log_path_ += folder_name_prefix_;
        if (folder_name_prefix_ != "")
        {
            log_path_ += "_";
        }

        log_path_ += std::string(dtf);
    }

    int CFileWriter::recursive_folder_creation(const char *dir, mode_t mode)
    {
        struct stat sb;

        if (!dir)
        {
            errno = EINVAL;
            return 1;
        }

        if (!stat(dir, &sb))
        {
            return 0;
        }

        recursive_folder_creation(dirname(strdupa(dir)), mode);

        int rc = mkdir(dir, mode);

        free((char*)dir);

        return rc;
    }

    void CFileWriter::switch_stream(const std::string &channel)
    {
        char dtf[1024];
        std::shared_ptr<CFile> file;

        // If Channel file exists, close it and move to the index for this channel
        if (current_files_.find(channel) != current_files_.end())
        {
            file = current_files_[channel];
            if (file->stream.is_open())
            {
                file->stream.close();
            }
            file->index++;
        }

        // Create new file for the channel
        else
        {
            current_files_[channel] = std::shared_ptr<CFile>(new CFile());
            file = current_files_[channel];
        }

        // Create formatted date time
        std::chrono::time_point<std::chrono::system_clock> dt = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(dt);
        std::strftime(dtf, sizeof(dtf), "%d-%m-%Y_%H-%M-%S", std::localtime(&time));

        std::stringstream ss;
        ss << log_path_ << "/";
        if (seperate_channel_to_files_)
        {
            ss << channel << "_";
        }
        else
        {
            ss << "Channels"
            << "_";
        }

        ss << "#" << file->index << "_" << dtf << ".log";
        file->stream.open(ss.str().data(), std::ofstream::out);
    }

    CFileWriter::CFileWriter(const CWriterConfig &config) : CWriter(config)
    {
        folder_name_prefix_ = config.get_option_default(CWriterOption::WO_FILE_LOG_FOLDER_PREFIX, "");
        log_path_ = config.get_option_default(CWriterOption::WO_FILE_LOG_FILES_PATH, "./");
        size_per_file_ = config.get_option_default(CWriterOption::WO_FILE_SIZE_PER_LOG_FILE, 1024 * 1024);
        max_files_ = static_cast<uint32_t>(config.get_option_default(CWriterOption::WO_FILE_MAX_LOG_FILES, 100));
        seperate_channel_to_files_ = static_cast<bool>(config.get_option_default(CWriterOption::WO_FILE_SEPERATE_CHANNEL_FILES, 0));

        create_log_path();
        recursive_folder_creation(log_path_.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

        if (!seperate_channel_to_files_)
        {
            switch_stream("DefaultChannel");
        }
    }

    CFileWriter::~CFileWriter()
    {
        for (auto &&file : current_files_)
        {
            file.second->stream.close();
        }
    }

    void CFileWriter::write(const CLog &log, const CChannelPtr &channel)
    {
        char dtf[1024];
        std::shared_ptr<CFile> file;
        std::string channelName;

        if (!seperate_channel_to_files_)
        {
            channelName = "DefaultChannel";
        }
        else
        {
            channelName = channel->get_channel_name();
            if (current_files_.find(channelName) == current_files_.end())
            {
                current_files_[channelName] = std::shared_ptr<CFile>(new CFile);
                switch_stream(channelName);
            }
        }

        file = current_files_[channelName];
        if (file->index > max_files_)
        {
            return;
        }

        if (file->stream.tellp() > size_per_file_)
        {
            switch_stream(channelName);
        }

        if (!log.get_stream())
        {
            return;
        }

        std::time_t time = std::chrono::system_clock::to_time_t(log.get_time_created());
        std::strftime(dtf, sizeof(dtf), "[%d/%m/%Y %H:%M:%S]", std::localtime(&time));
        ;
        file->stream << dtf << "[" << channel->get_channel_name() << "]["
                    << CLog::level_to_string(log.get_log_level()) << "]: " << log.get_stream()->str() << std::endl;
        file->stream.flush();
    }
}
