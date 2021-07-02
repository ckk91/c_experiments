#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "reader.h"
#include "types.h"


struct stream* read_stream(FILE *fstream, int manual) {
    struct stream* s = (struct stream *)malloc(sizeof(struct stream));
    s->s = s->curr = cons(NULL, NULL);
    // s->s == head
    int ch = EOF;
   
    while (ch)
    {
        ch = getc(fstream);
        if (ch == EOF || (manual == 1 && ch == '\n'))
        {
            break;
        }
        s->curr->car = make_int(ch);
        s->curr->cdr = cons(NULL, NULL);
        s->curr = cdr(s->curr);
    }

    s->curr = s->s;
    
    return s;
}

value* read_symbol(struct stream *s) {
    char ch;
    int pos = 0;
    char sym[255] = "";  // fun fact, this won't get a new address, needs init
    
    while (boxes_left(s))
    {
        ch = unbox(s);
        if (ch == ' ' || ch == '\n' || ch == ')')
        {
            break;
        }
        sym[pos] = ch;
        pos++;
        if (last_box(s))
        {
            break;
        }
        
        next(s);

    }
    
    value* v = make_sym(sym);
    return v;
}

value* read_list(struct stream *s) {
    // ( has been eaten
    char ch;
    while (boxes_left(s))
    {
        ch = unbox(s);
        if (ch == ' ' || ch == '\n')  // skip whitespace after (
        {
            next(s);
            continue;
            
        }
        if (ch == ')')
        {
            next(s);
            return NULL;
        }
        if (ch== '.')
        {
            next(s);  // Fugly but works
            return read_expr(s);
        }
        
        value *v = read_expr(s);  // n nelements
        return cons(v, read_list(s));  // TODO test for n elements
    }
}

value* read_num(struct stream *s){  // only int for now
    char ch;
    int pos = 0;
    char num[255] = "";  // fun fact, this won't get a new address, needs init
    while (boxes_left(s))
    {
        ch = unbox(s);
        if (ch == ' ' || ch == '\n' || ch == ')')
        {
            break;
        }
        num[pos] = ch;
        pos++;
        if (last_box(s))
        {
            break;
        }
        
        next(s);

    }
    
    return make_int(atoi(num));    
}


value* read_expr(struct stream *s) {  // dispatch
    /*
    expr = list || INT || SYMBOL
    list = (expr [.] [expr ...])
    SYMBOL = ALNUM, no () or spc
    */
    char ch;
    while (boxes_left(s))
    {
        ch = unbox(s);      
        if (ch == ' ' || ch == '\n') {
            next(s);
            continue;
        }
        if (ch == EOF || ch == NULL) {
            break;
        }
        if (ch == '(') {
            next(s);
            return read_list(s);
        }
        if (isalpha(ch) || ispunct(ch)) {
            return read_symbol(s);
        }
        if (isdigit(ch))
        {
            return read_num(s);
        }

        printf("UNKNOWN CHAR: %c %i", ch, (int)ch);
        getchar();
        break;
    }
    return NULL;
}
