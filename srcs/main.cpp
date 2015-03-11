#include <iostream>

#include <sstream>
#include <Avm.hpp>
#include <Manager.hpp>
#include <Vm.hpp>

//****************************** Exceptions *****************************************//

const char * ArgException::what (void) const throw ()
{
    return "./abstractvm [filename]";
}

VmException::VmException (const std::string &arg, int nb, const char * file, int line)
{
    std::stringstream ss;
    ss << "\033[31m" << arg << "\033[0m\033[37m\nat \033[34mline:" << nb << "\033[0m\033[37m (throwed at \033[34mL" << line << "\033[0m\033[37m of \033[34m" << file << "\033[0m\033[37m).\033[0m";
    this->_msg = ss.str();
}

VmException::VmException (VmException const & ref)
{
    *this = ref;
}

VmException & VmException::operator= (VmException const & ref)
{
    (void)ref;
    return *this;
}

VmException::~VmException (void)
{
}

const char * VmException::what (void) const throw ()
{
    return this->_msg.c_str();
}

const char * ExitException::what (void) const throw ()
{
    return "Goodbye.";
}

ParserException::ParserException (const std::string &arg, int nb, const char * file, int line)
{
    std::stringstream ss;
    ss << "\033[31m" << arg << "\033[0m\033[37m\nat \033[34mline:" << nb << "\033[0m\033[37m (throwed at \033[34mL" << line << "\033[0m\033[37m of \033[34m" << file << "\033[0m\033[37m).\033[0m";
    this->_msg = ss.str();
}

ParserException::ParserException (ParserException const & ref)
{
    *this = ref;
}

ParserException & ParserException::operator= (ParserException const & ref)
{
    (void)ref;
    return *this;
}

ParserException::~ParserException (void)
{
}

const char * ParserException::what (void) const throw ()
{
    return this->_msg.c_str();
}

void argtest (int ac)
{
    if (ac > 2)
    {
        throw ArgException();
    }
}

//*************************************************************************************//

int main(int ac, char **av) {


    std::string filename;

    try {
        argtest(ac);
        if (ac > 1)
          filename.assign(av[1]);
        else
           filename.assign("");
        Manager     m(filename);
        m.execute();
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
