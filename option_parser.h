//
// Created by ztarem on 11/6/23.
//

#pragma once

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

class OptionParser : public CLI::App
{
    using super = CLI::App;

  public:
    bool verbose{false};

    explicit OptionParser(std::string app_description = "");
    ~OptionParser() override = default;

    void Parse(int argc, const char *const *argv);
    void Parse(std::string commandline, bool program_name_included = false);
    void Parse(std::vector<std::string> &args);

    template <typename T>
    void AddHeader(const std::string &label, const T &value)
    {
        headers_.emplace_back(OptionHeader{label + ":", fmt::format("{}", value)});
    }

    void LogHeaders();

  protected:
    struct OptionHeader
    {
        std::string label;
        std::string value;
    };

    std::vector<OptionHeader> headers_{};

    virtual void PostParse_();
};
