#include "core.h"

#include <emscripten.h>
#include <emscripten/val.h>

class test
{
   public:
   test()
   {

   }
};

extern "C" {
int main()
{
   auto a = new test();
   return 2;
}

int init()
{
   return 1;
}
}