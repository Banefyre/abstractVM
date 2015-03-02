#ifndef ABSTRACTVM
# define ABSTRACTVM

class BasicException: public std::exception {};

class ArgException: public BasicException {

    public:
         virtual const char * what (void) const throw ();
};

#endif