#include <node_api.h>

napi_value square(napi_env env, napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  double value;
  napi_get_value_double(env, argv[0], &value);

  napi_value result;
  napi_create_double(env, value * value, &result);

  return result;
}

napi_value init(napi_env env, napi_value exports) {
  napi_value square_fn;
  napi_create_function(env, NULL, 0, square, NULL, &square_fn);
  napi_set_named_property(env, exports, "square", square_fn);

  return exports;
}

NAPI_MODULE(square, init)