Manager::Manager (char * str): _filename(str)
{

}

void Manager::execute (void)
{
    std::ifstream	file;
    std::string		line;
    int				i = 1;
    bool			execute = true;

    this->_getFile(file);
    while (std::getline((this->_filename ? file : std::cin), line)) {
        if (line == ";;" && !this->_filename) {
            break;
        }
        if (line.size() > 0 && line.at(0) != 59) {
            try {
                this->_parseThisLine(line, i);
            } catch (SyntaxException & e) {
                execute = false;
                std::cout << e.what() << std::endl;
            }
        }
        ++i;
    }
}

void Manager::_getFile (std::ifstream & file)
{
    if (this->_filename) {
        file.open(this->_filename);
    }
}