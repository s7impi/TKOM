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
  std::string id;
  std::size_t bit;
  std::istream& is;
  std::ostream& os;
  std::unordered_map<std::string, std::shared_ptr<ast::Definition>> definitions;
  std::vector<std::unordered_map<std::string, uint>> scopes;
  
  void read();
  uchar read(std::size_t bits);
  void read(std::size_t bits, uchar* data);
  
public:
  Context(std::istream& is, std::ostream& os);
  void set(uint val);
  uint get(std::string id) const;
  
  template <typename T>
  T read(std::size_t bits)
  {
    T data;
    read(bits, reinterpret_cast<uchar*>(&data));
    return data;
  }
  
  std::ostream& out();
  
  void openScope(std::string id);
  void closeScope();
  
  void startLevel();
  void endLevel();
  
  void definition(std::string id, std::shared_ptr<ast::Definition> definition);
  std::shared_ptr<ast::Definition> definition(std::string id);
};

#endif /* CONTEXT_HPP */