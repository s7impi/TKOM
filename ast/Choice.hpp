#ifndef CHOICE_HPP
#define CHOICE_HPP

#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <map>

#include "Node.hpp"

typedef unsigned int uint;

namespace ast {
  
class Choice : public Node {
private:
  std::string selector;
  std::map<uint, std::shared_ptr<Node>> mappedFields;
  
public:
  Choice(std::string selector, std::map<uint, std::shared_ptr<Node>>&& mappedFields);
  
  void convert(Context &context);
}; 
  
} /* namespace ast */

#endif /* CHOICE_HPP */
