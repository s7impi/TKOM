#ifndef STRING_HPP
#define STRING_HPP

#include "Node.hpp"

namespace ast {
  
class String : public Node {
public:
  void convert(Context &context);
};
  
} /* namespace ast */

#endif /* STRING_HPP */