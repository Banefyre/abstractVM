#include <Vm.hpp>
#include <Operand.hpp>

Vm::Vm (void)
{
    this->eType["int8"] = INT8;
    this->eType["int16"] = INT16;
    this->eType["int32"] = INT32;
    this->eType["float"] = FLOAT;
    this->eType["double"] = DOUBLE;
}

Vm::~Vm (void)
{
    std::list<IOperand const*>::iterator it;

    for (it = this->_stack.begin(); it != this->_stack.end(); it++) {
        delete *it;
    }
}

Vm& Vm::getInstance(void)
{
    // Guaranteed to be destroyed.
    static Vm    instance;
    // Instantiated on first use.
    return instance;
}

int Vm::getLine (void) const
{
    return this->_line;
}

void Vm::pop (void)
{
    if (this->_stack.size() < 1)
        FAILEXCEPT("Error : The stack is empty", this->_line);

    delete *(this->_stack.begin());
    this->_stack.pop_front();
}

void Vm::dump(void)
{
    std::list<IOperand const *>::const_iterator it = this->_stack.begin();
    while (it != this->_stack.end()) {
        std::cout << (*it)->toString() << std::endl;
        ++it;
    }
}

void Vm::assert(std::string type, std::string value)
{
    IOperand const * top = *(this->_stack.begin());

    IOperand const *check = Vm::getInstance().createOperand(this->eType[type], value);

    if (top->getType() != check->getType() || top->toString() != check->toString())
        FAILEXCEPT("Top value doesn't match", this->_line);
    delete top;

}

void    Vm::add(void)
{
    if (this->_stack.size() < 2)
        FAILEXCEPT("Error : Not enough operands on the stack", this->_line);

    const IOperand *op1 = this->_stack.front();
    this->_stack.pop_front();

    const IOperand *op2 = this->_stack.front();
    this->_stack.pop_front();

    this->_stack.push_front(*op2 + *op1);
}

void    Vm::push(std::string type, std::string value)
{
    if (!this->eType[type])
        FAILEXCEPT("Error : unknown type", Vm::getInstance().getLine());

    this->_stack.push_front(this->createOperand(eType[type], value));
}

void    Vm::sub(void)
{
    if (this->_stack.size() < 2)
        FAILEXCEPT("Error : Not enough operands on the stack", this->_line);

    IOperand const *op1 = this->_stack.front();
    this->_stack.pop_front();

    IOperand const *op2 = this->_stack.front();
    this->_stack.pop_front();

    this->_stack.push_front(*op2 - *op1);
}

void Vm::mul (void)
{
    if (this->_stack.size() < 2)
        FAILEXCEPT("Error : Not enough operands on the stack", this->_line);

    IOperand const *op1 = this->_stack.front();
    this->_stack.pop_front();

    IOperand const *op2 = this->_stack.front();
    this->_stack.pop_front();

    this->_stack.push_front(*op2 * *op1);
}

void Vm::div (void)
{
    if (this->_stack.size() < 2)
        FAILEXCEPT("Error : Not enough operands on the stack", this->_line);

    IOperand const *op1 = this->_stack.front();
    this->_stack.pop_front();

    IOperand const *op2 = this->_stack.front();
    this->_stack.pop_front();

    this->_stack.push_front(*op2 / *op1);
}

void Vm::mod (void)
{
    if (this->_stack.size() < 2)
        FAILEXCEPT("Error : Not enough operands on the stack", this->_line);

    IOperand const *op1 = this->_stack.front();
    this->_stack.pop_front();

    IOperand const *op2 = this->_stack.front();
    this->_stack.pop_front();

    this->_stack.push_front(*op2 % *op1);
}

void Vm::print (void)
{
    IOperand const * top = *(this->_stack.begin());
    this->assert("int8", top->toString());
    std::stringstream ss;
    int res;
    ss << top->toString();
    ss >> res;
    std::cout << static_cast<char>(res) << std::endl;
}

void Vm::exit (void)
{
    throw ExitException();
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
