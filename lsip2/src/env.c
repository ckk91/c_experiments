// ENV
#include <stdlib.h>
#include "env.h"
/*
alist env, behaves like a stack
(
    ((k . v)
     (k . v)
     (k . v))
    (PARENT_ENV)
)

*/
value* make_env(value* env) {
    return cons(NULL, env);
}

value* env_pop(value* env) {
     return env->cdr;  // todo free/gc
}

value* env_add(value* k, value* v, value* env) {
    env->car = cons(cons(k, v), env->car);
    return env;
}

value* find_in_env(value* sym, value* env) {
    while (env != NULL)
    {
        value* symbols = env->car;  // alist ((k.v) ((k.v) (NULL)))
        while (symbols != NULL)
        {
            value* curr = symbols->car;  // (k . v)
            if (curr->car == sym)  // k == sym
            {
                return curr->cdr;
            }
            symbols = symbols->cdr;  // ((k.v) NULL)            
        }
        env = env->cdr;  // grab parent
        // TODO explode if not found
    }
    return 0;
}