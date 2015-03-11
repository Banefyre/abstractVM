#ifndef INSTRUCTION_HPP
# define  INSTRUCTION_HPP

#include <string>

enum e_type
{
    SIMPLE = 1,
    PARAMETERS
};

class Instruction{

    public:

        Instruction(std::string instruction, std::string type, std::string value);
        Instruction(std::string instruction);
        ~Instruction();

        e_type       geteType(void) const;
        std::string  getInstruction(void) const;
        std::string  getType(void) const;
        std::string  getValue(void) const;

    private:

        Instruction(void);

        std::string _instruction;
        std::string _type;
        std::string _value;
        e_type      _instrType;
};

#endif