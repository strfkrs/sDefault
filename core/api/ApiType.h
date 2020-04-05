#pragma once
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

namespace core::api
{
   typedef std::vector<emscripten::val> valVector_t;
   typedef std::map<std::string,emscripten::val> valMap_t;
   typedef emscripten::val val_t;
}