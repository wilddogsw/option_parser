//
// Created by ztarem on 11/6/23.
//

#include "option_parser.h"
#include <filesystem>
#include <spdlog/fmt/ostr.h>

namespace fs = std::filesystem;

OptionParser::OptionParser(std::string app_description) : super(std::move(app_description))
{
    this->add_flag("-v,--verbose", this->verbose, "Write debug messages to the log");
}

void OptionParser::Parse(int argc, const char *const *argv)
{
    super::name(fs::path(argv[0]).stem());
    try
    {
        super::parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        ::exit(this->exit(e));
    }
    this->PostParse_();
}

void OptionParser::Parse(std::string commandline, bool program_name_included)
{
    if (program_name_included)
    {
        size_t pos = commandline.find(' ');
        if (pos != std::string::npos)
            super::name(fs::path(commandline.substr(0, pos)).stem());
    }
    try
    {
        super::parse(std::move(commandline), program_name_included);
    }
    catch (const CLI::ParseError &e)
    {
        ::exit(this->exit(e));
    }
    this->PostParse_();
}

void OptionParser::Parse(std::vector<std::string> &args)
{
    try
    {
        super::parse(args);
    }
    catch (const CLI::ParseError &e)
    {
        ::exit(this->exit(e));
    }
    this->PostParse_();
}

void OptionParser::LogHeaders() {
    spdlog::info("{} - {}", this->get_name(), this->get_description());
    if (!headers_.empty())
    {
        size_t labelWidth = 0;
        for (auto &header : headers_)
            labelWidth = std::max(labelWidth, header.label.length());
        for (auto &header : headers_)
            spdlog::info("  {:{}} {}", header.label, labelWidth, header.value);
    }
}

void OptionParser::PostParse_()
{
    if (this->verbose)
        spdlog::set_level(spdlog::level::debug);
}
