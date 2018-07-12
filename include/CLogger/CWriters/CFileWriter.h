/**
 * @brief 
 * 
 * @file CFileWriter.h
 * @author ofir iluz
 * @date 2018-07-10
 */

#ifndef CLOGGER_CWRITERS_CFILEWRITER_H_
#define CLOGGER_CWRITERS_CFILEWRITER_H_

#include <CLogger/CWriters/CWriter.h>
#include <iomanip>
#include <ctime>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include <fstream>

namespace CLogger
{
    class CFileWriter : public CWriter
    {
    private:
        class CFile
        {
        public:
            std::ofstream stream;
            uint32_t index;

            CFile();
            virtual ~CFile();
        };

    private:
        std::string folder_name_prefix_;
        std::string log_path_;
        long size_per_file_;
        uint32_t max_files_;
        std::map<std::string, std::shared_ptr<CFile>> current_files_;
        bool seperate_channel_to_files_;

    private:
        /**
         * @brief 
         * 
         * @param dir 
         * @param mode 
         * @return int 
         */
        int recursive_folder_creation(const char *dir, mode_t mode);
        /**
         * @brief 
         * Creates the log path which files will be written to, saves it to mLogPath
         * Appends the current time to the name aswell
         */
        void create_log_path();
        /**
         * @brief 
         * Creates the log directory if does not exist
         */
        void create_log_directory();
        /**
         * @brief
         * Switches to a new stream when the file size has reached the max
         * The old stream will saved and closed and a new stream will be opened for a new file
         * 
         * @param channel
         */
        void switch_stream(const std::string &channel);

    public:
        /**
         * @brief Construct a new CFileWriter object
         * 
         * @param config 
         */
        CFileWriter(const CWriterConfig &config);
        /**
         * @brief Destroy the CFileWriter object
         * 
         */
        virtual ~CFileWriter();
        /**
         * @brief
         * Writes the contents of the log to file / files
         * @see CWriter::write
         * 
         * @param log
         * @param channel
         */
        virtual void write(const CLog & log, const CChannelPtr & channel);
    };
}

#endif /* CLOGGER_CWRITERS_CFILEWRITER_H_ */
