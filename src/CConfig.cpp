/**
 * @brief 
 * 
 * @file CConfig.cpp
 * @author ofir iluz
 * @date 2018-07-11
 */

#include <CLogger/CConfig.h>

namespace CLogger
{
    CWriterConfig::CWriterConfig(const std::string &writer_name, const CWriterType &writer_type)
        : writer_name_(writer_name), writer_type_(writer_type)
    {
    }

    CWriterConfig::~CWriterConfig()
    {
    }

    void CWriterConfig::set_option(const CWriterOption &option, const std::string &value)
    {
        options_[option] = value;
    }

    void CWriterConfig::set_option(const CWriterOption &option, int value)
    {
        set_option(option, CConfig::convert_from<int>(value));
    }

    void CWriterConfig::set_option(const CWriterOption &option, double value)
    {
        set_option(option, CConfig::convert_from<double>(value));
    }

    bool CWriterConfig::remove_option(const CWriterOption &option)
    {
        if (has_option(option))
        {
            options_.erase(option);
            return true;
        }
        return false;
    }

    bool CWriterConfig::has_option(const CWriterOption &option) const
    {
        return options_.find(option) != options_.end();
    }

    bool CWriterConfig::get_option(const CWriterOption &option, std::string &value) const
    {
        if (has_option(option))
        {
            value = options_.at(option);
            return true;
        }
        return false;
    }

    bool CWriterConfig::get_option(const CWriterOption &option, int &value) const
    {
        std::string s;
        if (get_option(option, s))
        {
            try
            {
                value = CConfig::convert_to<int>(s);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }
        return false;
    }

    bool CWriterConfig::get_option(const CWriterOption &option, double &value) const
    {
        std::string s;
        if (get_option(option, s))
        {
            try
            {
                value = CConfig::convert_to<double>(s);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }
        return false;
    }

    std::string CWriterConfig::get_option_default(const CWriterOption &option, const std::string &default_value) const
    {
        if (has_option(option))
        {
            return options_.at(option);
        }
        return default_value;
    }

    int CWriterConfig::get_option_default(const CWriterOption &option, int default_value) const
    {
        std::string s = get_option_default(option, CConfig::convert_from<int>(default_value));
        try
        {
            int i = CConfig::convert_to<int>(s);
            return i;
        }
        catch (...)
        {
            return default_value;
        }
    }

    double CWriterConfig::get_option_default(const CWriterOption &option, double default_value) const
    {
        std::string s = get_option_default(option, CConfig::convert_from<double>(default_value));
        try
        {
            double i = CConfig::convert_to<double>(s);
            return i;
        }
        catch (...)
        {
            return default_value;
        }
    }

    std::string CWriterConfig::get_writer_name() const
    {
        return writer_name_;
    }

    CWriterType CWriterConfig::get_writer_type() const
    {
        return writer_type_;
    }

    CConfig::CConfig()
    {
    }

    CConfig::~CConfig()
    {
    }

    void CConfig::set_option(const CLoggerOption &option, const std::string &value)
    {
        logger_options_[option] = value;
    }

    void CConfig::set_option(const CLoggerOption &option, int value)
    {
        set_option(option, convert_from<int>(value));
    }

    void CConfig::set_option(const CLoggerOption &option, double value)
    {
        set_option(option, convert_from<double>(value));
    }

    bool CConfig::has_writer(const std::string &writer_name) const
    {
        for (auto &&w : writer_configs_)
        {
            if (w.get_writer_name() == writer_name)
            {
                return true;
            }
        }
        return false;
    }

    const std::vector<CWriterConfig> &CConfig::get_writers() const
    {
        return writer_configs_;
    }

    void CConfig::add_writer(const CWriterConfig &writer)
    {
        writer_configs_.push_back(writer);
    }

    bool CConfig::remove_option(const CLoggerOption &option)
    {
        if (!has_option(option))
        {
            return false;
        }
        logger_options_.erase(option);
        return true;
    }

    bool CConfig::has_option(const CLoggerOption &option) const
    {
        return logger_options_.find(option) != logger_options_.end();
    }

    bool CConfig::get_option(const CLoggerOption &option, std::string &value) const
    {
        if (has_option(option))
        {
            value = logger_options_.at(option);
            return true;
        }
        return false;
    }

    bool CConfig::get_option(const CLoggerOption &option, int &value) const
    {
        std::string s;
        if (get_option(option, s))
        {
            value = convert_to<int>(s);
            return true;
        }
        return false;
    }

    bool CConfig::get_option(const CLoggerOption &option, double &value) const
    {
        std::string s;
        if (get_option(option, s))
        {
            value = convert_to<double>(s);
            return true;
        }
        return false;
    }

    void CConfig::remove_writer(const std::string &writer_name)
    {
        for (size_t i = 0; i < writer_configs_.size(); i++)
        {
            if (writer_configs_[i].get_writer_name() == writer_name)
            {
                writer_configs_.erase(writer_configs_.begin() + i);
                return;
            }
        }
    }
}
