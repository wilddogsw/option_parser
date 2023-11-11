//
// Created by ztarem on 11/10/23.
//

#include <gtest/gtest.h>
#include "option_parser.h"

class Parser : public OptionParser
{
    using super = OptionParser;

  public:
    int first{1};
    std::string second{};

    Parser() : super("Testing OptionParser") {
        this->add_option("-f,--first", this->first, "First argument")->capture_default_str();
        this->add_option("-s,--second", this->second, "Second argument");
    }
    ~Parser() override = default;

  protected:
    void PostParse_() override {
        super::PostParse_();
        this->AddHeader("First", this->first);
        this->AddHeader("Second", this->second);
    }
};

//TEST(option_parser_tests, cmdline_help)
//{
//    Parser parser;
//    parser.Parse("-h");
//}

TEST(option_parser_tests, cmdline)
{
    Parser parser;
    parser.Parse("-f 42 --second Hello");
    parser.LogHeaders();


}
