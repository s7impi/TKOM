#include "Reference.hpp"

#include "Context.hpp"

namespace ast {
  
Reference::Reference(std::string id) :
  id(id)
{}

void Reference::convert(Context& context)
{
  context.definition(id)->convert(context);
}

uint Reference::compute(Context& context)
{
  return context.get(id);
}

} /* namespace ast */