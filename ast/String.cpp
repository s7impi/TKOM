#include "String.hpp"

#include "Context.hpp"

namespace ast {

void String::convert(Context& context)
{
  char c = context.read<char>(CHAR_BIT);
  while (c)
  {
    context.out() << c;
    c = context.read<char>(CHAR_BIT);
    context.out() << "\b\b";
  }
  context.out() << std::endl;
}

} /* namespace ast */