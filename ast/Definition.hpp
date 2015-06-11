#ifndef DEFINITION_HPP
#define DEFINITION_HPP

#include <vector>
#include <memory>
#include <string>

#include "Node.hpp"

namespace ast {
  
class Definition : public Node {
  std::string name;
  std::vector<std::shared_ptr<Node>> fields;
  
public:
  Definition(std::string name, std::vector<std::shared_ptr<Node>>);
  
  const std::string& id() const;
  
  void convert(Context& c);
};
  
} /* namespace ast */

#endif /* DEFINITION_HPP */