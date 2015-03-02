#include <iostream>
#include "../incs/avm.hpp"
using namespace std;

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

    (void)av;
    try {
        argtest(ac);
        cout << "Hello, World!" << endl;
    }
    catch (ArgException & e) {
        std::cout << "Usage: " << e.what() << std::endl;
    }
    return 0;
}
