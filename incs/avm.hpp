#ifndef AVM
# define AVM

# define FAILEXCEPT(STR, NB)	throw FailException(STR, NB, __FILE__, __LINE__);

class BasicException: public std::exception {};

class ArgException: public BasicException {

    public:
         virtual const char * what (void) const throw ();
};

class ExitException: public BasicException {

public:
    virtual const char * what (void) const throw ();
};

class FailException: public std::exception {

    public:
        FailException (const std::string &arg, int nb, const char * file, int line);

        virtual const char * what (void) const throw ();

        FailException (FailException const & ref);
        ~FailException (void);

    private:
        std::string		_msg;

        FailException (void);
        FailException & operator= (FailException const & ref);
};

#endif