#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

class Context;

namespace ast {
  
typedef unsigned int uint;
  
class Expression {
public:
  virtual uint compute(Context &context) = 0;
};
  
} /* namespace ast */

#endif /* EXPRESSION_HPP */