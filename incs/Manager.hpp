#ifndef MANAGER_HPP
# define MANAGER_HPP

class Manager {

    public:

        Manager	(char * str);
        ~Manager (void);
        void execute (void);

    private:

        char *					    _filename;

        void	                    _getFile(std::ifstream & file);

        Manager (Manager const & ref);
        Manager & operator= (Manager const & ref);
        Manager (void);
};

#endif