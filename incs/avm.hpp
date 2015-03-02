#ifndef AVM
# define AVM

class BasicException: public std::exception {};

class ArgException: public BasicException {

    public:
         virtual const char * what (void) const throw ();
};

#endif