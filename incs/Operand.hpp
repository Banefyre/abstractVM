#include <IOperand.hpp>
#include <avm.hpp>
#include <Vm.hpp>
#include <string>

template <typename T>
class Operand: public IOperand {

    public :

        Operand (eOperandType type, std::string val): _type(type), _str(val)
        {
        //construct stuff
        }

        virtual ~Operand (void) {}


        virtual IOperand const * operator+( IOperand const & rhs ) const
        {

            //getType >= rhs.getTYpe -> determiner le type de la nouvelle operand
            //toString - > double   (a laide de string stream)
            //x2
            //d1 + d2
            //value >> ss


            return Vm::getInstance().createOperand(newType, ss.str());
        }
        virtual IOperand const * operator-( IOperand const & rhs ) const {return this;}
        virtual IOperand const * operator*( IOperand const & rhs ) const {return this;}
        virtual IOperand const * operator/( IOperand const & rhs ) const {return this;}
        virtual IOperand const * operator%( IOperand const & rhs ) const {return this;}


        int				    getPrecision (void) const
        {
            return this->_type;
        }


        eOperandType	    getType (void) const
        {
            return this->_type;
        }

        std::string const &	toString (void) const
        {
            return this->_str;
        }

    private :

        eOperandType		_type;
        std::string			_str;

        Operand (void);
        Operand (Operand const & ref);
        Operand & operator= (Operand const & ref);

};