#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <memory>
#include <limits.h>

#include "Definition.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

class Context {
  uint level;
  uchar cur;
  std::size_t bit;
  std::istream& is;
  std::ostream& os;
  std::unordered_map<std::string, std::shared_ptr<ast::Definition>> definitions;
  std::vector<std::unordered_map<std::string, uint>> scopes;
  void read()
  {
    cur = is.get();
    bit = 0;
  }
  void read(std::size_t bits, uchar* data)
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
  
public:
  Context(std::istream& is, std::ostream& os) :
    level(0),
    cur(0),
    bit(CHAR_BIT),
    is(is),
    os(os)
  {}
  void set(std::string id, uint val)
  {
    scopes.back().insert(std::make_pair(id, val));
  }
  uint get(std::string id) const
  {
    for (auto it = scopes.rbegin(), end = scopes.rend(); it != end; ++it)
    {
      auto el = it->find(id);
      if (el != it->end())
	return el->second;
    }
    throw std::runtime_error("");
  }
  template <typename T>
  T read(std::size_t bits)
  {
    T data;
    read(bits, reinterpret_cast<uchar*>(&data));
    return data;
  }
  std::ostream& out()
  {
    for (uint i = 0; i < level; ++i)
      os << "  ";
    return os;
  }
  void openScope(std::string /*id*/)
  {
    scopes.emplace_back(std::unordered_map<std::string, uint>());
  }
  void closeScope()
  {
    scopes.pop_back();
  }
  void startLevel()
  {
    ++level;
  }
  void endLevel()
  {
    --level;
  }
  void definition(std::string id, std::shared_ptr<ast::Definition> definition)
  {
    definitions.insert(std::make_pair(id, definition));
  }
  std::shared_ptr<ast::Definition> definition(std::string id)
  {
    return definitions[id];
  }
};

#endif /* CONTEXT_HPP */