#ifndef READER_H
#define READER_H
#include <stdio.h>
#include "types.h"



struct stream
{
    value* s;
    value* curr;
};

struct stream* read_stream(FILE *fstream, int manual);

value* read_symbol(struct stream *s);
value* read_list(struct stream *s);
value* read_expr(struct stream *s);
value* read_num(struct stream *s);

#define next(s) (s->curr = s->curr->cdr)
#define unbox(s) s->curr->car->i
#define boxes_left(s) (s->curr->cdr != NULL)
#define last_box(s) s->curr->cdr == NULL


#endif // !H_READER
