#include <Vm.hpp>
#include <Operand.hpp>

Vm::Vm (void)
{
}

Vm::~Vm (void)
{
    std::list<IOperand const*> ::iterator it;

    for (it = this->_stack.begin(); it != this->_stack.end(); it++) {
        delete *it;
    }
}

static Vm& getInstance()
{
    // Guaranteed to be destroyed.
    static Vm    instance;
    // Instantiated on first use.
    return instance;
}


void    Vm::add(void)
{
    //check si >= 2 dans la stack sinon throw error

    //pop top -> keep pointer
    //pop top-> keep pointer

    this->_stack.push_font(ptr1 + ptr2);
}

IOperand const *	Vm::createOperand (eOperandType type, std::string const & value) const
{
    static std::map<eOperandType, makeOperand> map = {
            { INT8, &Vm::createInt8 },
            { INT16, &Vm::createInt16 },
            { INT32, &Vm::createInt32 },
            { DOUBLE, &Vm::createDouble },
            { FLOAT, &Vm::createFloat }
    };

    return (this->*(map[type]))(value);
}

IOperand const * Vm::createInt8 (std::string const & value) const
{
    return new Operand<int8_t>(INT8, value);
}

IOperand const * Vm::createInt16 (std::string const & value) const
{
    return new Operand<int16_t>(INT16, value);
}

IOperand const * Vm::createInt32 (std::string const & value) const
{
    return new Operand<int32_t>(INT32, value);
}

IOperand const * Vm::createFloat (std::string const & value) const
{
    return new Operand<float>(FLOAT, value);
}

IOperand const * Vm::createDouble (std::string const & value) const
{
    return new Operand<double>(DOUBLE, value);
}
