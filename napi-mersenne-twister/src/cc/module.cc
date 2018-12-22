#include <napi.h>
#include "mersenne-twister-chatty-wrap.h"
#include "mersenne-twister-wrap.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  MersenneTwisterChattyWrap::Initialize(env);
  exports["MersenneTwisterChatty"] = MersenneTwisterChattyWrap::constructor.Value();

  MersenneTwisterWrap::Initialize(env);
  exports["MersenneTwister"] = MersenneTwisterWrap::constructor.Value();

  return exports;
}

NODE_API_MODULE(mersenne_twister, Init)