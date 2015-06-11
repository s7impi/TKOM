#include "BinaryExpression.hpp"

#include <stdexcept>

namespace ast {

typedef unsigned int uint;
  
BinaryExpression::BinaryExpression(std::shared_ptr<Expression>&& left, Operator op, std::shared_ptr<Expression>&& right) :
  left(std::move(left)),
  op(op),
  right(std::move(right))
{}
  
uint BinaryExpression::compute(Context &context)
{
  switch (op) 
  {
    case Operator::ADD:
      return left->compute(context)+right->compute(context);
    case Operator::SUB:
      return left->compute(context)-right->compute(context);
    case Operator::MUL:
      return left->compute(context)*right->compute(context);
    default:
      throw std::runtime_error("Unrecognized expression.");
  }
}

} /* namespace ast */