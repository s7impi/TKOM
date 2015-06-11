#include "Choice.hpp"

#include "Context.hpp"

namespace ast {

typedef unsigned int uint;

Choice::Choice(std::string selector, std::map<uint, std::shared_ptr<Node>>&& mappedFields) : 
  selector(selector),
  mappedFields(std::move(mappedFields))
{}

void Choice::convert(Context &context)
{
  uint id = context.get(selector);
  mappedFields[id]->convert(context);
}

} /* namespace ast */
  