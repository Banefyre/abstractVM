#include <iostream>

#include <Avm.hpp>
#include <Manager.hpp>
#include <Vm.hpp>

//****************************** Exceptions *****************************************//

const char * ArgException::what (void) const throw ()
{
    return "./abstractvm [filename]";
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


    Vm::getInstance().push("int8", "2");

    std::string filename;

    try {
        argtest(ac);
        if (ac > 2)
          filename.assign(av[1]);
        else
           filename.assign("");
        Manager     m(filename);
        m.execute();
    }
    catch (ArgException & e) {
        std::cout << "Usage: " << e.what() << std::endl;
    }
    return 0;
}
