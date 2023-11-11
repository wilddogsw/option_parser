//
// Created by ztarem on 11/6/23.
//

#include "option_parser.h"
#include <filesystem>
#include <boost/dll/runtime_symbol_info.hpp>

namespace fs = std::filesystem;

OptionParser::OptionParser(std::string app_description) : CLI::App(std::move(app_description))
{
    this->add_flag("-v,--verbose", this->verbose, "Write debug messages to the log");
    this->add_flag("-q,--quiet", this->quiet, "Write only warnings or worse to the log");
}

void OptionParser::Parse(int argc, const char *const *argv)
{
    if (this->get_name().empty())
        this->name(boost::dll::program_location().stem().string());
    try
    {
        this->parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        ::exit(this->exit(e));
    }
    this->PostParse_();
}

void OptionParser::Parse(std::string commandline, bool program_name_included)
{
    if (this->get_name().empty() && !program_name_included)
        this->name(boost::dll::program_location().stem().string());
    try
    {
        this->parse(std::move(commandline), program_name_included);
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
    else if (this->quiet)
        spdlog::set_level(spdlog::level::warn);
}
