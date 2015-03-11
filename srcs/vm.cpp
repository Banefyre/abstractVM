#include <Vm.hpp>
#include <Operand.hpp>
#include <Manager.hpp>
#include "Instruction.hpp"

Vm::Vm (void)
{
    this->eType["int8"] = INT8;
    this->eType["int16"] = INT16;
    this->eType["int32"] = INT32;
    this->eType["float"] = FLOAT;
    this->eType["double"] = DOUBLE;


    this->_basicsMap["add"] = &Vm::add;
    this->_basicsMap["sub"] = &Vm::sub;
    this->_basicsMap["mul"] = &Vm::mul;
    this->_basicsMap["div"] = &Vm::div;
    this->_basicsMap["mod"] = &Vm::mod;
    this->_basicsMap["print"] = &Vm::print;
    this->_basicsMap["exit"] = &Vm::exit;
    this->_basicsMap["dump"] = &Vm::dump;
    this->_basicsMap["pop"] = &Vm::pop;

    this->_paramsMap["push"] = &Vm::push;
    this->_paramsMap["assert"] = &Vm::assert;

    this->_typeMap["int8"] = INT8;
    this->_typeMap["int16"] = INT16;
    this->_typeMap["int32"] = INT32;
    this->_typeMap["float"] = FLOAT;
    this->_typeMap["double"] = DOUBLE;
}

Vm::~Vm (void)
{

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

void Vm::addInstruction(Instruction *instr) {
    this->_instructions.push_back(instr);
}

void Vm::run (void) {

    bool exit = false;

    //loop _instruction -> getType -> SIMPLE ->
    std::list<Instruction *>::const_iterator it = this->_instructions.begin();
    while (it != this->_instructions.end())
    {

        if ((*it)->getInstruction() == "exit")
            exit = true;

        if ((*it)->geteType() == e_type::SIMPLE) {
            (this->*(this->_basicsMap[(*it)->getInstruction()]))();
        }
        else {
            (this->*(this->_paramsMap[(*it)->getInstruction()]))((*it)->getType(), (*it)->getValue());
        }
        ++it;
    }

    if (!exit)
        VMEXCEPT("Error : Left without using exit", this->_line);;
}

void Vm::pop (void)
{
    if (this->_stack.size() < 1)
        VMEXCEPT("Error : The stack is empty", this->_line);

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
        VMEXCEPT("Top value doesn't match", this->_line);
    delete top;

}

void    Vm::add(void)
{
    if (this->_stack.size() < 2)
        VMEXCEPT("Error : Not enough operands on the stack", this->_line);

    const IOperand *op1 = this->_stack.front();
    this->_stack.pop_front();

    const IOperand *op2 = this->_stack.front();
    this->_stack.pop_front();

    this->_stack.push_front(*op2 + *op1);
}

void    Vm::push(std::string type, std::string value)
{
    if (!this->eType[type])
        VMEXCEPT("Error : unknown type", Vm::getInstance().getLine());

    this->_stack.push_front(this->createOperand(eType[type], value));
}

void    Vm::sub(void)
{
    if (this->_stack.size() < 2)
        VMEXCEPT("Error : Not enough operands on the stack", this->_line);

    IOperand const *op1 = this->_stack.front();
    this->_stack.pop_front();

    IOperand const *op2 = this->_stack.front();
    this->_stack.pop_front();

    this->_stack.push_front(*op2 - *op1);
}

void Vm::mul (void)
{
    if (this->_stack.size() < 2)
        VMEXCEPT("Error : Not enough operands on the stack", this->_line);

    IOperand const *op1 = this->_stack.front();
    this->_stack.pop_front();

    IOperand const *op2 = this->_stack.front();
    this->_stack.pop_front();

    this->_stack.push_front(*op2 * *op1);
}

void Vm::div (void)
{
    if (this->_stack.size() < 2)
        VMEXCEPT("Error : Not enough operands on the stack", this->_line);

    IOperand const *op1 = this->_stack.front();
    this->_stack.pop_front();

    IOperand const *op2 = this->_stack.front();
    this->_stack.pop_front();

    this->_stack.push_front(*op2 / *op1);
}

void Vm::mod (void)
{
    if (this->_stack.size() < 2)
        VMEXCEPT("Error : Not enough operands on the stack", this->_line);

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
    std::cout << "Goodbye." << std::endl;
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
