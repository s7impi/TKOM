#include "Definition.hpp"

#include "Context.hpp"

namespace ast {
  
Definition::Definition(std::string name, std::vector<std::shared_ptr<Node>> fields) : 
  name(name),
  fields(std::move(fields))
{}

const std::string& Definition::id() const
{
  return name;
}

void Definition::convert(Context &context)
{
  context.out() << name << ":" << std::endl;
  context.startLevel();
  for (auto it = fields.begin(), end = fields.end(); it != end; ++it)
    (*it)->convert(context);
  context.endLevel();
}

}