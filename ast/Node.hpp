#ifndef NODE_HPP
#define NODE_HPP

class Context;

namespace ast {
  
class Node {
public:
  virtual ~Node() {};
  
  virtual void convert(Context &context) = 0;
};
  
} /* namespace ast */

#endif /* NODE_HPP */