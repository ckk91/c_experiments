#ifndef TYPES_H
#define TYPES_H

typedef enum
{
    _CELL, _INT, _SYM, 
    _FUN, // builtin func
    _LAM  // user defined func
} TAG;


typedef struct value  // boxing
{
    TAG tag;
    union
    {
        // CELL
        struct {
            struct value* car;
            struct value* cdr;
        };
        // LITS        
        char* sym;
        int i;
        struct value* (*fn)(struct value*);
    };
} value;

value* make_int(int i);
value* intern(char* sym);
value* make_sym(char* sym);
value* cons(value* car, value* cdr);
value* make_lam(value *args, value *body);
value* v_alloc();

#define car(x) (x->car)
#define cdr(x) (x->cdr)
#define cddr(x) (x->cdr->cdr)
#define cadr(x) (x->cdr->car)
#define cdar(x) (x->car->cdr)

#endif // !TYPES_H
