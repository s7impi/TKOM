#ifndef BINARY_EXPRESSION_HPP
#define BINARY_EXPRESSION_HPP

#include <memory>

#include "Expression.hpp"

namespace ast {
  
class BinaryExpression : public Expression {
public:
  enum class Operator {
    ADD,
    SUB,
    MUL
  };
private:
  std::shared_ptr<Expression> left;
  Operator op;
  std::shared_ptr<Expression> right;
public:
  BinaryExpression(std::shared_ptr<Expression>&& left, Operator op, std::shared_ptr<Expression>&& right);
  uint compute(Context &context);
};
  
} /* namespace ast */

#endif /* BINARY_EXPRESSION_HPP */