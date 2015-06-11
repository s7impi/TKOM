#ifndef NUMBER_HPP
#define NUMBER_HPP

#include "Expression.hpp"

namespace ast {

class Number : public Expression {
  uint value;
public:
  Number(uint value);
  uint compute(Context &context);
};
  
} /* namespace ast */

#endif /* NUMBER_HPP */