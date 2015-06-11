#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <memory>

#include "Node.hpp"
#include "Expression.hpp"

namespace ast {
  
class Array : public Node {
private:
  std::shared_ptr<Expression> exp;
  std::shared_ptr<Node> type;
public:
  Array(std::shared_ptr<Expression>&& exp, std::shared_ptr<Node>&& type);
  void convert(Context &context);
};
  
  
} /* namespace ast */

#endif /* ARRAY_HPP */