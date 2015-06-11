#include "Field.hpp"

#include "Context.hpp"

namespace ast {
  
Field::Field(std::string name, std::shared_ptr<Node>&& type) : 
  name(name), 
  type(std::move(type))
{}

void Field::convert(Context &context)
{
  context.out() << name << ":";
  context.openScope(name);
  type->convert(context);
  context.closeScope();
}

} /* namespace ast */