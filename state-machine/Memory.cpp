#include "Memory.hpp"

namespace Memory
{
  void end(void* p)
  {
    asm volatile("" : : "g"(p) : "memory");
  }

  void read()
  {
    asm volatile("" : : : "memory");
  }
}
