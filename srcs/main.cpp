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

FailException::FailException (const std::string &arg, int nb, const char * file, int line)
{
    std::stringstream ss;
    ss << "\033[31m" << arg << "\033[0m\033[37m\nat \033[34mline:" << nb << "\033[0m\033[37m (throwed at \033[34mL" << line << "\033[0m\033[37m of \033[34m" << file << "\033[0m\033[37m).\033[0m";
    this->_msg = ss.str();
}

FailException::FailException (FailException const & ref)
{
    *this = ref;
}

FailException & FailException::operator= (FailException const & ref)
{
    (void)ref;
    return *this;
}

FailException::~FailException (void)
{
}

const char * FailException::what (void) const throw ()
{
    return this->_msg.c_str();
}

const char * ExitException::what (void) const throw ()
{
    return "Goodbye.";
}

void argtest (int ac)
{
    if (ac > 2)
    {
        throw ArgException();
    }
}

//*************************************************************************************//

int main() {


    Vm::getInstance().push("int8", "2");
    Vm::getInstance().push("int8", "5");
    Vm::getInstance().dump();
    Vm::getInstance().add();
    Vm::getInstance().dump();

//    std::string filename;
//
//    try {
//        argtest(ac);
//        if (ac > 2)
//          filename.assign(av[1]);
//        else
//           filename.assign("");
//        Manager     m(filename);
//        m.execute();
//    }
//    catch (ArgException & e) {
//        std::cout << "Usage: " << e.what() << std::endl;
//    }
    return 0;
}
