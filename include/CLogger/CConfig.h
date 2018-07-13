/**
 * @brief 
 * 
 * @file CConfig.h
 * @author ofir iluz
 * @date 2018-07-10
 */

#ifndef CLOGGER_CCONFIG_H_
#define CLOGGER_CCONFIG_H_

#include <string>
#include <vector>
#include <map>
#include <thread>
#include <sstream>

namespace CLogger
{
    /**
     * @brief 
     * Defines the Options available to configure the Logger
     */
    enum class CLoggerOption : uint8_t
    {
        LG_DEFAULT_CHANNEL_LEVEL
    };

    /**
     * @brief
     * Defines the options for specific writers
     */
    enum class CWriterOption : uint8_t
    {
        WO_CONSOLE_DISABLE_COLOR,

        WO_FILE_LOG_FILES_PATH,
        WO_FILE_SIZE_PER_LOG_FILE,
        WO_FILE_MAX_LOG_FILES,
        WO_FILE_LOG_FOLDER_PREFIX,
        WO_FILE_SEPERATE_CHANNEL_FILES,

        WO_SYSLOG_NAME
    };

    /**
     * @brief
     * Defines the available writes for the logger
     */
    enum class CWriterType : uint8_t
    {
        LW_FILE_WRITER,
        LW_CONSOLE_WRITER,
        LW_SYSLOG_WRITER
    };

    class CWriterConfig
    {
    private:
        std::map<CWriterOption, std::string> options_;
        CWriterType writer_type_;
        std::string writer_name_;

    public:
        /**
         * @brief Construct a new CWriterConfig object
         * 
         * @param writer_name 
         * @param writer_type 
         */
        CWriterConfig(const std::string &writer_name, const CWriterType &writer_type);
        /**
         * @brief Destroy the CWriterConfig object
         * 
         */
        virtual ~CWriterConfig();
        /**
         * @brief 
         * Setter for an option with a given value, will override old option
         * 
         * @param option 
         * @param value 
         */
        void set_option(const CWriterOption &option, const std::string &value);
        /**
         * @brief
         * Setter for an option with a given value, if this option is applicable for int
         * Will override old option
         * 
         * @param option 
         * @param value 
         */
        void set_option(const CWriterOption &option, int value);
        /**
         * @brief 
         * Setter for an option with a given value, if this option is applicable for double
         * Will override old option
         * 
         * @param option 
         * @param value 
         */
        void set_option(const CWriterOption &option, double value);
        /**
         * @brief
         * Removes an option if exists
         * 
         * @param option
         */
        bool remove_option(const CWriterOption &option);
        /**
         * @brief
         * Checks if an option exists
         * 
         * @param option
         * @return
         */
        bool has_option(const CWriterOption &option) const;
        /**
         * @brief 
         * Getter for an option, puts it in the value and returns true if exists
         * 
         * @param option 
         * @param value 
         * @return true 
         * @return false 
         */
        bool get_option(const CWriterOption &option, std::string &value) const;
        /**
         * @brief Get the Option object
         * Getter for an option, puts it in the value and returns true if exists
         * 
         * @param option 
         * @param value 
         * @return true 
         * @return false 
         */
        bool get_option(const CWriterOption &option, int &value) const;
        /**
         * Getter for an option, puts it in the value and returns true if exists
         * 
         * @param option
         * @param value
         * @return
         */
        bool get_option(const CWriterOption &option, double &value) const;
        /**
         * @brief 
         * Getter for an option with default value
         * 
         * @param option 
         * @param default_value 
         * @return std::string 
         */
        std::string get_option_default(const CWriterOption &option, const std::string &default_value) const;
        /**
         * @brief 
         * Getter for an option with default value
         * 
         * @param option 
         * @param default_value 
         * @return int 
         */
        int get_option_default(const CWriterOption &option, int default_value) const;
        /**
         * @brief 
         * Getter for an option with default value
         * 
         * @param option 
         * @param default_value 
         * @return double
         */
        double get_option_default(const CWriterOption &option, double default_value) const;
        /**
         * @brief 
         * Getter for the writer name
         * 
         * @return std::string 
         */
        std::string get_writer_name() const;
        /**
         * @brief 
         * Getter for the writer type
         * 
         * @return PSWriterType 
         */
        CWriterType get_writer_type() const;
    };
    class CConfig
    {
    private:
        std::vector<CWriterConfig> writer_configs_;
        std::map<CLoggerOption, std::string> logger_options_;

    private:
        /**
         * @brief
         * Converts a given input to template T
         * 
         * @tparam T
         * @param input
         * @return
         */
        template <class T>
        static T convert_to(const std::string &input)
        {
            std::stringstream convertor;
            convertor << input;
            T out;
            convertor >> out;
            return out;
        }
        /**
         * @brief
         * Converts a given T to string
         * T must implement << operator
         * 
         * @tparam T
         * @param input
         * @return
         */
        template <class T>
        static std::string convert_from(const T &input)
        {
            std::stringstream convertor;
            convertor << input;
            return convertor.str();
        }

    public:
        /**
         * @brief Construct a new CConfig object
         * 
         */
        CConfig();
        /**
         * @brief Destroy the CConfig object
         * 
         */
        virtual ~CConfig();
        /**
         * @brief
         * Setter for a given logger option
         * 
         * @param option
         * @param value
         */
        void set_option(const CLoggerOption &option, const std::string &value);
        /**
         * @brief
         * Setter for a given logger option for int (only some options will be permitted)
         * 
         * @param option
         * @param value
         */
        void set_option(const CLoggerOption &option, int value);
        /**
         * @brief
         * Setter for a given logger option for double (only some options will be permitted)
         * 
         * @param option
         * @param value
         */
        void set_option(const CLoggerOption &option, double value);
        /**
         * @brief
         * Checks if a given writer exists
         * 
         * @param writer_name
         * @return true
         * @return false
         */
        bool has_writer(const std::string &writer_name) const;
        /**
         * @brief
         * Getter for the list of writers
         * 
         * @return const std::vector<CWriterConfig>& 
         */
        const std::vector<CWriterConfig> &get_writers() const;
        /**
         * @brief
         * Adds a writer to the writer list
         * 
         * @param config
         */
        void add_writer(const CWriterConfig &config);
        /**
         * @brief
         * Removes a writer by name
         * 
         * @param writer_name
         */
        void remove_writer(const std::string &writer_name);
        /**
         * @brief
         * Removes an option from the config if exists
         * 
         * @param option
         * @return true
         * @return false
         */
        bool remove_option(const CLoggerOption &option);
        /**
         * @brief
         * Checks if an option exists
         * 
         * @param option
         * @return true
         * @return false
         */
        bool has_option(const CLoggerOption &option) const;
        /**
         * @brief
         * Getter for an option's value for a given option
         * 
         * @param option
         * @param value
         * @return true
         * @return false
         */
        bool get_option(const CLoggerOption &option, std::string &value) const;
        /**
         * @brief
         * Getter for an option's value for a given option
         * @param option
         * @param value
         * @return true
         * @return false
         */
        bool get_option(const CLoggerOption &option, int &value) const;
        /**
         * @brief
         * Getter for an option's value for a given option
         * 
         * @param option
         * @param value
         * @return true
         * @return false
         */
        bool get_option(const CLoggerOption &option, double &value) const;

        friend class CWriterConfig;
    };
    typedef std::shared_ptr<CConfig> CConfigPtr;
}

#endif /* CLOGGER_CCONFIG_H_ */
