#ifndef H_ENV
#define H_ENV
#include "types.h"

value* make_env(value* env);
value* env_pop(value* env);
value* env_add(value* k, value* v, value* env);
value* find_in_env(value* sym, value* env);
#endif