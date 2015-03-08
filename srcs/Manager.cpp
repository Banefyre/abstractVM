#include "../incs/Manager.hpp"

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