#include "Array.hpp"

#include "Context.hpp"

namespace ast {
  
typedef unsigned int uint;

Array::Array(std::shared_ptr<Expression>&& exp, std::shared_ptr<Node>&& type) : 
  exp(std::move(exp)),
  type(std::move(type))
{}

void Array::convert(Context &context)
{
  uint size = exp->compute(context);
  context.startLevel();
  context.out() << std::endl;
  for(uint i = 0; i < size; ++i)
  {
    context.out() << '[' << i << "]";
    type->convert(context);
  }
  context.endLevel();
}

} /* namespace ast */