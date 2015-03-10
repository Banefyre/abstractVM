#include <Instruction.hpp>

Instruction::Instruction (std::string instruction , std::string paramtype, std::string paramvalue) : _instruction(instruction), _type(paramtype), _value(paramvalue), _instrType(PARAMETERS)
{
}

Instruction::Instruction (std::string instruction) : _instruction(instruction), _instrType(SIMPLE)
{

}

e_type       Instruction::geteType(void) const {return this->_instrType;}
std::string  Instruction::getInstruction(void) const {return this->_instruction;}
std::string  Instruction::getType(void) const {return this->_type;}
std::string  Instruction::getValue(void) const {return this->_value;}