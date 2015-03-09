#ifndef INSTRUCTION_CLASS
# define INSTRUCTION_CLASS

# include "abstract.hpp"

class Instruction {

public:

    Instruction (VmBasics fn, VmParams extra, eOperandType type, std::string value, int line);
    ~Instruction (void);

    VmBasics			basic;
    VmParams			extra;

    eOperandType		type;
    std::string			value;

    int					line;

private:

    Instruction (Instruction const & ref);
    Instruction & operator= (Instruction const & ref);

};

#endif