//
// Created by ztarem on 11/6/23.
//

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

int main(int argc, char *argv[]) {
   Parser parser;
   parser.Parse(argc, argv);
   parser.LogHeaders();

   spdlog::debug("This is a debug message");
}
