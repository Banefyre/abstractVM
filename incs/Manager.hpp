#ifndef MANAGER_HPP
# define MANAGER_HPP

#include <fstream>
#include <iostream>
#include <map>

class Manager {

    public:

        Manager	(std::string str);
        ~Manager (void);
        void execute (void);

    private:


        typedef void(Vm::*basics)(void);
        typedef void(Vm::*params)(std::string, std::string);

        std::string				                 _filename;

        std::map<std::string, basics>		    _basicsMap;
        std::map<std::string, params>		    _paramsMap;
        std::map<std::string, eOperandType>	    _typeMap;

        void                        _parseThisLine (std::string & line, int i);

        void	                    _getFile(std::ifstream & file);

        Manager (Manager const & ref);
        Manager & operator= (Manager const & ref);
        Manager (void);
};

#endif