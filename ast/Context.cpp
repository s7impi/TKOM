#include "Context.hpp"
  
void Context::read()
{
  cur = is.get();
  bit = 0;
}

uchar Context::read(std::size_t bits)
{
  // need more data
  if (bit == CHAR_BIT)
    read();
  
  std::size_t first = CHAR_BIT-bit;
  uchar r = cur<<(CHAR_BIT-first);
  if (bits > first)
  {
    read();
    r |= cur>>first;
    bit = bits-first;
  }
  else
    bit += bits;
  return r >> (CHAR_BIT-bits);
}
  
void Context::read(std::size_t bits, uchar* data)
{
  // no more bits to read
  if (bits == 0)
    return;
    
  std::size_t rest = bits%CHAR_BIT;
  if (rest != 0)
    *data++ = read(rest);
    
  for (; bits >= CHAR_BIT; bits -= CHAR_BIT)
    *data++ = read(CHAR_BIT);
}
  
Context::Context(std::istream& is, std::ostream& os) : 
  level(0),
  cur(0),
  bit(CHAR_BIT),
  is(is),
  os(os)
{}

void Context::set(uint val)
{
  scopes[scopes.size()-2].insert(std::make_pair(id, val));
}

uint Context::get(std::string id) const
{
  for (auto it = scopes.rbegin(), end = scopes.rend(); it != end; ++it)
  {
    auto el = it->find(id);
    if (el != it->end())
      return el->second;
  }
  throw std::runtime_error("");
}

std::ostream& Context::out()
{
  for (uint i = 0; i < level; ++i)
    os << "  ";
  return os;
}

void Context::openScope(std::string id)
{
  this->id = id;
  scopes.emplace_back(std::unordered_map<std::string, uint>());
}
  
void Context::closeScope()
{
  scopes.pop_back();
}

void Context::startLevel()
{
  ++level;
}
  
void Context::endLevel()
{
    --level;
}
  
void Context::definition(std::string id, std::shared_ptr<ast::Definition> definition)
{
  definitions.insert(std::make_pair(id, definition));
}
  
std::shared_ptr<ast::Definition> Context::definition(std::string id)
{
  auto it = definitions.find(id);
  if (it == definitions.end())
    throw std::runtime_error("No such definition");
  return it->second;
}
