#ifndef __MERSENNE_TWISTER_CHATTY_WRAP_H__
#define __MERSENNE_TWISTER_CHATTY_WRAP_H__
#include <napi.h>
#include "mersenne-twister.h"

class MersenneTwisterChattyWrap : public Napi::ObjectWrap<MersenneTwisterChattyWrap> {
public:
  static Napi::FunctionReference constructor;
  static void Initialize(Napi::Env env);
public:
  MersenneTwisterChattyWrap(const Napi::CallbackInfo& info);

  Napi::Value Next(const Napi::CallbackInfo& info);

private:
  MersenneTwister<uint32_t> mt;
};

#endif