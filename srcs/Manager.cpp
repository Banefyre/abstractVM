#include <Manager.hpp>
#include <regex>
#include "Instruction.hpp"


Manager::Manager(std::string str): _filename(str)
{


}

Manager::~Manager(void)
{

}

void Manager::execute(void)
{
    std::ifstream	file;
    std::string		line;
    int				i = 1;
    bool			execute = true;

    this->_getFile(file);
    while (std::getline((this->_filename.empty() ? std::cin : file), line)) {
        if (line == ";;" && this->_filename.empty()) {
            break;
        }
        if (line.size() > 0 && line.at(0) != 59) {
            try {
                this->_parseThisLine(line, i);
            } catch (ParserException & e) {
                execute = false;
                std::cout << e.what() << std::endl;
            }
        }
        ++i;
    }

    if(!this->_filename.empty())
    {
        file.close();
    }

    if (execute)
        Vm::getInstance().run();
}

void Manager::_getFile(std::ifstream & file)
{
    if (!this->_filename.empty()) {
        file.open(this->_filename);
    }
}

void Manager::_parseThisLine (std::string & line, int i)
{
    std::regex basic("^(add|sub|mul|div|mod|print|exit|dump|pop)?([ ];.*)?$");
    std::regex high("^(push|assert)[ ]+(.*)$");

    if (!std::regex_match(line, basic) && !std::regex_match(line, high)) {
        PARSEEXCEPT("Unknown instruction", i);
    }

    if (std::regex_match(line, high)) {

        std::regex N("[-]?[0-9]+");
        std::regex Z("[-]?[0-9]+[.]{1}[0-9]+");

        std::smatch m;
        std::regex_search(line, m, high);
        std::regex type("(int8|int16|int32|float|double)\\((.*)\\)");
        std::string instruction = m.str(1);

        if (!std::regex_match(m.str(2), type)) {
            PARSEEXCEPT("Invalid parameter", i);
        }

        std::regex_search(m.str(2), m, type);

        std::string paramType = m.str(1);
        std::string paramValue = m.str(2);
        if (!std::regex_match(paramValue, (paramType == "float" || paramType == "double" ? Z : N))) {
            PARSEEXCEPT("The specified parameter does not match a valid type", i);
        }
            Vm::getInstance().addInstruction(new Instruction(instruction, paramType, paramValue));
        }
        else {
        std::smatch m;
        std::regex_search(line, m, basic);
        Vm::getInstance().addInstruction(new Instruction(m.str(1)));
    }
}