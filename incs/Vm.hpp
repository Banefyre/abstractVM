#ifndef VM_HPP
# define VM_HPP

#include <string>
#include <map>
#include <list>
#include <avm.hpp>
#include <IOperand.hpp>

class Vm
{

    public:

        static Vm& getInstance(void);

        Vm	(void);
        ~Vm	(void);

        IOperand const * createOperand(eOperandType type, std::string const & value ) const;

        void push(std::string type, std::string value);

    private:

        typedef IOperand const * (Vm::*makeOperand)( std::string const & value) const;

        std::list<IOperand const *>		_stack;

        Vm	(Vm const & ref);
        Vm & operator=(Vm const& ref);

        IOperand const * createInt8( std::string const & value ) const;
        IOperand const * createInt16( std::string const & value ) const;
        IOperand const * createInt32( std::string const & value ) const;
        IOperand const * createFloat( std::string const & value ) const;
        IOperand const * createDouble( std::string const & value ) const;
};

#endif