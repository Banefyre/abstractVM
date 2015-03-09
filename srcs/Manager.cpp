#include <Manager.hpp>
#include <regex>
#include <Vm.hpp>


Manager::Manager(std::string str): _filename(str)
{

    this->_firstMap["add"] = &Vm::add;
    this->_firstMap["sub"] = &Vm::sub;
    this->_firstMap["mul"] = &Vm::mul;
    this->_firstMap["div"] = &Vm::div;
    this->_firstMap["mod"] = &Vm::mod;
    this->_firstMap["print"] = &Vm::print;
    this->_firstMap["exit"] = &Vm::exit;
    this->_firstMap["dump"] = &Vm::dump;
    this->_firstMap["pop"] = &Vm::pop;

    this->_secondMap["push"] = &Vm::push;
    this->_secondMap["assert"] = &Vm::assert;

    this->_thirdMap["int8"] = INT8;
    this->_thirdMap["int16"] = INT16;
    this->_thirdMap["int32"] = INT32;
    this->_thirdMap["float"] = FLOAT;
    this->_thirdMap["double"] = DOUBLE;

}

Manager::~Manager(void)
{

}

void Manager::execute(void)
{
    std::ifstream	file;
    std::string		line;
    int				i = 1;
   // bool			execute = true;

    this->_getFile(file);
    while (std::getline((this->_filename.empty() ? std::cin : file), line)) {
        if (line == ";;" && this->_filename.empty()) {
            break;
        }
        if (line.size() > 0 && line.at(0) != 59) {
            std::cout << line << std::endl;
        }
        ++i;
    }
}

void Manager::_getFile(std::ifstream & file)
{
    if (!this->_filename.empty()) {
        file.open(this->_filename);
    }
}

void Manager::_parseThisLine (std::string & line, int i)
{
    std::regex basic("^(add|sub|mul|div|mod|print|exit|dump|pop)$");
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
        Vm::getInstance().pushInstruction(this->_secondMap[instruction], this->_thirdMap[paramType], paramValue, i);
    } else {
        std::smatch m;
        std::regex_search(line, m, basic);
        Vm::getInstance().pushInstruction(this->_firstMap[m.str(1)], i);
    }
}