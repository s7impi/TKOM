#include "Context.hpp"
  
void Context::read()
{
  cur = is.get();
  bit = 0;
}
  
void Context::read(std::size_t bits, uchar* data)
{
  // no more bits to read
  if (bits == 0)
    return;
    
  // current buffer read - read more data
  if (bit == CHAR_BIT)
    read();
    
  std::size_t rest = bits%CHAR_BIT;
  if (rest != 0)
  {
    if (CHAR_BIT-bit >= rest)
    {
      *data = cur>>(CHAR_BIT-rest-bit)&((1<<rest)-1);
      bit += rest;
    }
    else
    {
      std::size_t first = CHAR_BIT-bit;
      *data = cur<<(rest-first)&((1<<rest)-1);
      read();
      *data |= cur>>(CHAR_BIT-(first-rest))&((1<<rest)-1);
      bit = rest-first;    
    }
  }
    
  while (bits)
  {
    // current buffer read - read more data
    if (bit == CHAR_BIT)
      read();
      
    std::size_t first = bit;
    *data = cur<<first;
      
    if (first != 0)
    {
      read();
      *data |= cur>>(CHAR_BIT-first);
    }
      
    bit = CHAR_BIT-first;
    ++data;
    bits -= CHAR_BIT;
  }
}
  
Context::Context(std::istream& is, std::ostream& os) : 
  level(0),
  cur(0),
  bit(CHAR_BIT),
  is(is),
  os(os)
{}

void Context::set(std::string id, uint val)
{
  scopes.back().insert(std::make_pair(id, val));
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

void Context::openScope(std::string /*id*/)
{
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
  return definitions[id];
}
