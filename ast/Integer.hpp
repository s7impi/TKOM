#ifndef INTEGER_HPP
#define INTEGER_HPP

#include "Node.hpp"
#include "Context.hpp"

namespace ast {

template <class T>
class Integer : public Node {
public:
  void convert(Context& context)
  {
    context.out() << context.read<T>(sizeof(T)*CHAR_BIT) << std::endl;
  }
};

template <>
class Integer<uint8_t> : public Node {
public:
  void convert(Context& context)
  {
    context.out() << (uint)context.read<uint8_t>(sizeof(uint8_t)*CHAR_BIT) << std::endl;
  }
};

template <>
class Integer<int8_t> : public Node {
public:
  void convert(Context& context)
  {
    context.out() << (int)context.read<int8_t>(sizeof(int8_t)*CHAR_BIT) << std::endl;
  }
};
  
} /* namespace ast */

#endif /* INTEGER_HPP */