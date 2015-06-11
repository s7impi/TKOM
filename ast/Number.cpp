#include "Number.hpp"

namespace ast {  
  
Number::Number(uint value) : value(value) {}
  
uint Number::compute(Context &context)
{
  return value;
}

  
} /* namespace ast */