#include <IOperand.hpp>
#include <avm.hpp>
#include <Vm.hpp>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>

template <typename T>
class Operand: public IOperand {

    public :

        Operand (eOperandType type, std::string val): _type(type), _str(val)
        {
            double              value;
            std::stringstream   ss(val);

            //val -> double
            ss >> value;

            //double ---> numeric limit<T> :: max and ::lowest ----> throw error overflow or underflow
            if (value < std::numeric_limits<T>::lowest() || (type == INT8 && value < -128)) {
                FAILEXCEPT("Error : underflow", Vm::getInstance().getLine());
            }
            else if (value > std::numeric_limits<T>::max() || (type == INT8 && value > 127)) {
                FAILEXCEPT("Error : overflow", Vm::getInstance().getLine());
            }
            // not working with int8_t -> 127 / -128
            else if (ss.fail()) {
                FAILEXCEPT("Not a valid numeric representation", Vm::getInstance().getLine());
            }
        }

        virtual ~Operand (void) {}


        virtual IOperand const * operator+( IOperand const & rhs ) const
        {
            double              st;
            double              nd;
            eOperandType        type;
            std::stringstream   res;

            this->_getParams(st, nd, type, rhs);
            res << (st + nd);

            return Vm::getInstance().createOperand(type, res.str());
        }
        virtual IOperand const * operator-( IOperand const & rhs ) const
        {
            double              st;
            double              nd;
            eOperandType        type;
            std::stringstream   res;

            this->_getParams(st, nd, type, rhs);
            res << (st - nd);

            return Vm::getInstance().createOperand(type, res.str());
        }
        virtual IOperand const * operator*( IOperand const & rhs ) const
        {
            double              st;
            double              nd;
            eOperandType        type;
            std::stringstream   res;

            this->_getParams(st, nd, type, rhs);
            if (type <= INT32)
                res << (int) (st * nd);
            else
                res << (st * nd);

            return Vm::getInstance().createOperand(type, res.str());
        }
        virtual IOperand const * operator/( IOperand const & rhs ) const
        {
            double              st;
            double              nd;
            eOperandType        type;
            std::stringstream   res;

            this->_getParams(st, nd, type, rhs);
            if (nd == 0)
                FAILEXCEPT("Error : division by 0", Vm::getInstance().getLine())
            if (type <= INT32)
                res << (int) (st / nd);
            else
                res << (st / nd);

            return Vm::getInstance().createOperand(type, res.str());
        }
        virtual IOperand const * operator%( IOperand const & rhs ) const
        {
            double              st;
            double              nd;
            eOperandType        type;
            std::stringstream   res;

            this->_getParams(st, nd, type, rhs);
            if (nd == 0)
                FAILEXCEPT("Error : modulus by 0", Vm::getInstance().getLine())
            if (type <= INT32)
                res << (int)(fmod(st,nd));
            else
                res << (fmod(st,nd));

            return Vm::getInstance().createOperand(type, res.str());
        }


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

        void				_getParams (double & st, double & nd, eOperandType & type, IOperand const & rhs) const
        {
            std::stringstream	ss(this->_str);
            std::stringstream	ss2(rhs.toString());

            ss >> st;
            ss2 >> nd;

            type = (this->_type > rhs.getType() ? this->_type : rhs.getType());
        }

        Operand (void);
        Operand (Operand const & ref);
        Operand & operator= (Operand const & ref);

};