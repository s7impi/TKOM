#ifndef REFERENCE_HPP
#define REFERENCE_HPP
  
#include <string>

#include "Node.hpp"
#include "Expression.hpp"

namespace ast {
  
class Reference : public Node, public Expression {
  std::string id;
public:
  Reference(std::string id);
  void convert(Context &context);
  uint compute(Context &context);
};
  
} /* namespace ast */

#endif /* REFERENCE_HPP */