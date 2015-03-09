#ifndef AVM
# define AVM

# define VMEXCEPT(STR, NB)	throw VmException(STR, NB, __FILE__, __LINE__);
# define PARSEEXCEPT(STR, NB)	throw ParserException(STR, NB, __FILE__, __LINE__);

class BasicException: public std::exception {};

class ArgException: public BasicException {

    public:
         virtual const char * what (void) const throw ();
};

class ExitException: public BasicException {

public:
    virtual const char * what (void) const throw ();
};

class VmException: public std::exception {

    public:
        VmException (const std::string &arg, int nb, const char * file, int line);

        virtual const char * what (void) const throw ();

        VmException (VmException const & ref);
        ~VmException (void);

    private:
        std::string		_msg;

        VmException (void);
        VmException & operator= (VmException const & ref);
};

class ParserException: public std::exception {
public:
    ParserException (const std::string &arg, int nb, const char * file, int line);

    virtual const char * what (void) const throw ();

    ParserException (ParserException const & ref);
    ~ParserException (void);

private:
    std::string		_msg;

    ParserException & operator= (ParserException const & ref);
    ParserException (void);
};

#endif