#ifndef FIELD_HPP
#define FIELD_HPP

#include <string>
#include <memory>

#include "Node.hpp"

namespace ast {
  
class Field : public Node {
  std::string name;
  std::shared_ptr<Node> type;

public:
  Field(std::string name, std::shared_ptr<Node>&& type);
  
  void convert(Context &context);
};
  
} /* namespace ast */

#endif /* FIELD_HPP */