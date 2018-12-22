#include "mersenne-twister-chatty-wrap.h"

Napi::FunctionReference MersenneTwisterChattyWrap::constructor;

void MersenneTwisterChattyWrap::Initialize(Napi::Env env) {
  constructor = Napi::Persistent(
    DefineClass(env, "MersenneTwisterChatty", {
      InstanceMethod("next", &MersenneTwisterChattyWrap::Next)
    })
  );

  constructor.SuppressDestruct();
}

MersenneTwisterChattyWrap::MersenneTwisterChattyWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<MersenneTwisterChattyWrap>(info) {
  if (info.Length() == 0) {
    return;
  }

  if (!info[0].IsNumber()) {
    Napi::Error::New(info.Env(), "seed should be a number").ThrowAsJavaScriptException();
    return;
  }

  mt.SetSeed(info[0].ToNumber().Uint32Value());
}

Napi::Value MersenneTwisterChattyWrap::Next(const Napi::CallbackInfo& info) {
  const uint32_t value = mt.Next();
  return Napi::Number::New(info.Env(), value);
}