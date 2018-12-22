#include "mersenne-twister-wrap.h"

Napi::FunctionReference MersenneTwisterWrap::constructor;

void MersenneTwisterWrap::Initialize(Napi::Env env) {
  constructor = Napi::Persistent(
    DefineClass(env, "MersenneTwister", {
      InstanceMethod("load", &MersenneTwisterWrap::Load)
    })
  );

  constructor.SuppressDestruct();
}

MersenneTwisterWrap::MersenneTwisterWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<MersenneTwisterWrap>(info) {
  if (info.Length() == 0) {
    return;
  }

  if (!info[0].IsNumber()) {
    Napi::Error::New(info.Env(), "seed should be a number").ThrowAsJavaScriptException();
    return;
  }

  mt.SetSeed(info[0].ToNumber().Uint32Value());
}

void MersenneTwisterWrap::Load(const Napi::CallbackInfo& info) {

  if (info.Length() == 0 || !info[0].IsTypedArray()) {
    Napi::Error::New(info.Env(), "array should be typed array").ThrowAsJavaScriptException();
    return;
  }

  auto&& typed_array = info[0].As<Napi::TypedArray>();
  if (typed_array.TypedArrayType() != napi_uint32_array) {
    Napi::Error::New(info.Env(), "array should be of type uint32").ThrowAsJavaScriptException();
    return;
  }

  auto&& array = typed_array.As<Napi::Uint32Array>();
  auto&& data = array.Data();
  for (int i = 0; i < array.ElementLength(); i++) {
    data[i] = mt.Next();
  }
}