#ifndef __MERSENNE_TWISTER_WRAP_H__
#define __MERSENNE_TWISTER_WRAP_H__
#include <napi.h>
#include "mersenne-twister.h"

class MersenneTwisterWrap : public Napi::ObjectWrap<MersenneTwisterWrap> {
public:
  static Napi::FunctionReference constructor;
  static void Initialize(Napi::Env env);
public:
  MersenneTwisterWrap(const Napi::CallbackInfo& info);

  void Load(const Napi::CallbackInfo& info);

private:
  MersenneTwister<uint32_t> mt;
};

#endif