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
    T data = context.read<T>(sizeof(T)*CHAR_BIT);
    context.set((uint)data);
    context.out() << data << std::endl;
  }
};

template <>
class Integer<uint8_t> : public Node {
public:
  void convert(Context& context)
  {
    uint8_t data = context.read<uint8_t>(sizeof(uint8_t)*CHAR_BIT);
    context.set(data);
    context.out() << (uint)data << std::endl;
  }
};

template <>
class Integer<int8_t> : public Node {
public:
  void convert(Context& context)
  {
    int8_t data = context.read<int8_t>(sizeof(int8_t)*CHAR_BIT);
    context.set((uint)data);
    context.out() << (int)data << std::endl;
  }
};
  
} /* namespace ast */

#endif /* INTEGER_HPP */