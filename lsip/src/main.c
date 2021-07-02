#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "reader.h"
#include "printer.h"
#include "env.h"
#include "globals.h"
#include <string.h>

value* fn_add(value* cell) {
    int sum = 0;
    
    value* curr = cell;
    for (; curr->cdr != NULL ; curr = curr->cdr)
    {
        sum += car(curr)->i;
    }
    sum += car(curr)->i;  // TODO fix off by one
    
    return make_int(sum);
}

value* fn_prn(value* cell) {
    print(cell);
    return &NIL;
}

value* fn_eq(value* cell) {
    if (car(cell) == cadr(cell)){
        return &T;
    }  // poniter comparison
    return &NIL;
}


value* map(value* list, value* cb){
    value* new = &NIL;
    for (value* curr = list->car; curr->cdr != NULL ; curr = curr->cdr)
    {
        new = cons(cb->fn(curr), new);
    }
    return new;
}

// todo map, reduce, filter

value* apply(value* fn, value* args, value* env) {
    // env = make_env(env);
   
}

/*
FROM https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-26.htmlhttps://web.archive.org/web/20160531205537/https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-26.html

(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((lambda? exp)
         (make-procedure (lambda-parameters exp)
                         (lambda-body exp)
                         env))
        ((begin? exp) 
         (eval-sequence (begin-actions exp) env))
        ((cond? exp) (eval (cond->if exp) env))
        ((application? exp)
         (apply (eval (operator exp) env)
                (list-of-values (operands exp) env)))
        (else
         (error "Unknown expression type -- EVAL" exp))))

For clarity, eval has been implemented as a case analysis using con

*/

value* eval(value* val, value* env) {
    if (val == 0)
    {
        return 0;
    }
    
    else if (val->tag == _INT)
    {
        return val;
        
    } else if (val->tag == _SYM)  // variable
    {
        value* tmp = find_in_env(val, env);
        if (tmp == 0)
        {
            printf("UNKOWN SYMBOL: %s\n", val->sym);
            return 0;
        }
        return tmp;
    } else if (val->tag == _CELL)  // is pair
    {
        // val->car->tag == _FUN  --> apply
        if (val->car == intern("QUOTE"))  // quote  TODO syml global
        {
            return val->cdr->car; 
        } else if (val->car == intern("def")) // assign
        {
            /* (DEF NAME EVAL(VALUE)) => NAME, bind to env */
            env_add(cadr(val), eval(val->cdr->cdr->car, env), &ENV);
            return cadr(val);
        } else if (val->car == intern("lambda"))
        {
            /* make proc, capture env */
            /* (lambda (x y z) BODY) */
            return make_lam(cadr(val), cddr(val));  // TODO handle env
        } else {
            // probably a func, apply
            print(val);  // trace
            printf("\n");
            if (val->cdr == NULL)  // signifies end of list, single value left
            {
                return cons(eval(val->car, env),NULL);
            }
            
            value* evaled = eval(val->cdr, env);
            
            value* fn = eval(val->car, env);
            print(fn);  // trace
            print(evaled);  // trace
            printf("\n");
            if (fn->tag == _FUN)
            {
                return (fn->fn)(evaled);
            }
            if (fn->tag == _LAM){  // ( (_(x) (+ 1 x)) 1)
                env = make_env(env);
                // capture free vars /evaled, positional
                env_add(fn->car->car, evaled->car, env);  // test drive one param
                return eval(fn->cdr, env);
                // todo remove env?
            }
            return cons(fn, evaled);
            // TODO user defined
            
        }
        
        
        
    }
    
    
    
}



value* fn_eval(value* val) { return eval(val, &ENV); }

void make_builtin(char* name, value* (*fn)(value*)) {  // todo move to types
    value* fn_ = v_alloc();  // todo cons!
    fn_->tag = _FUN;
    fn_->fn = fn;
    env_add(make_sym(name), fn_, &ENV);
}


int main(int argc, char const* argv[])
{
    printf("Starting up and testing...\n");

    char BOOT[] = "(FOO . 1)";

    FILE *fstream = fmemopen(BOOT, strlen(BOOT), "r");
	struct stream* s = read_stream(fstream, 0);
	fclose(fstream);

    value * boot_cons = read_expr(s);

    print(boot_cons);

    env_add(boot_cons->car, boot_cons->cdr, &ENV);

    make_builtin("+", fn_add);
    make_builtin("eq", fn_eq);
    make_builtin("PRN", fn_prn);
    make_builtin("eval", fn_eval);


    print(&SYML);
    printf("\nREADY.\n");
    value * e = NULL;
 
    // === REPL ===
    while (1)
    {
    printf("> ");
    struct stream *instream = read_stream(stdin, 1);
    value *result = read_expr(instream);
    e = eval(result, &ENV);
    if (e == NULL)  // TODO error handling
    {
        continue;
    }
    
    print(e);
    clearerr(stdin);
    }
    
    
    return 0;
}