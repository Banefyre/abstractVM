#ifndef MANAGER_HPP
# define MANAGER_HPP

#include <fstream>
#include <iostream>

class Manager {

    public:

        Manager	(std::string str);
        ~Manager (void);
        void execute (void);

    private:

        std::string				    _filename;

        void	                    _getFile(std::ifstream & file);

        Manager (Manager const & ref);
        Manager & operator= (Manager const & ref);
        Manager (void);
};

#endif