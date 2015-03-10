#ifndef MANAGER_HPP
# define MANAGER_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <Vm.hpp>

class Manager {

    public:

        Manager	(std::string str);
        ~Manager (void);
        void execute (void);

    private:

        std::string				                 _filename;


        void                        _parseThisLine (std::string & line, int i);

        void	                    _getFile(std::ifstream & file);

        Manager (Manager const & ref);
        Manager & operator= (Manager const & ref);
        Manager (void);
};

#endif