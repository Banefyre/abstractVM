#ifndef VM_HPP
# define VM_HPP

#include <string>
#include <map>
#include <iostream>
#include <list>
#include <avm.hpp>
#include <IOperand.hpp>
#include <Instruction.hpp>

class Vm
{

    public:

        static Vm& getInstance(void);

        Vm	(void);
        ~Vm	(void);

        IOperand const * createOperand(eOperandType type, std::string const & value ) const;

        void push(std::string type, std::string value);
        void pop (void);
        void dump (void);
        void add(void);
        void sub(void);
        void mul(void);
        void div(void);
        void mod(void);
        void print(void);
        void exit(void);
        void assert(std::string type, std::string value);
        int  getLine			(void) const;
        std::map<std::string, eOperandType > eType;

        void    addInstruction(Instruction * instr);

        void    run(void);

    private:


        typedef void(Vm::*basics)(void);
        typedef void(Vm::*params)(std::string, std::string);


        std::map<std::string, basics>		    _basicsMap;
        std::map<std::string, params>		    _paramsMap;
        std::map<std::string, eOperandType>	    _typeMap;

        std::list<Instruction *> _instructions;


        typedef IOperand const * (Vm::*makeOperand)( std::string const & value) const;

        std::list<IOperand const *>		_stack;
        int								_line;
        Vm	(Vm const & ref);
        Vm & operator=(Vm const& ref);

        IOperand const * createInt8( std::string const & value ) const;
        IOperand const * createInt16( std::string const & value ) const;
        IOperand const * createInt32( std::string const & value ) const;
        IOperand const * createFloat( std::string const & value ) const;
        IOperand const * createDouble( std::string const & value ) const;
};

#endif