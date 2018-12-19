#include <napi.h>

Napi::Value Square(const Napi::CallbackInfo& info) {
  double value = info[0].ToNumber().DoubleValue();
  return Napi::Number::New(info.Env(), value * value);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports["square"] = Napi::Function::New(env, Square);
  return exports;
}

NODE_API_MODULE(square, Init)