#if !defined(VM_H)
#define VM_H
#include "types.h"
#include <stddef.h>

typedef enum {
    NIL,
    LOADC,
    LOAD,  // var
    LAM,
    CONS,
    STOP,
} OP;

typedef enum {
    _OP, _VAL, _FRAME
} ListTag;

typedef struct frame Frame;

typedef struct listfield {
    ListTag tag;
    union
    {
        OP o;  // TODO fix if only bytes
        Frame* f;
        value* v;
    };
    

} ListField;

typedef struct list {
    // where we're going we don't need free, bay-bee
    ListTag tag;
    ListField* arr[255];
    size_t length; //255
    size_t head; //left to right increment
} List;

typedef struct frame {
    // old list, new frame is new list
    List *s;  // [value*, ...]List of values
    List *e;  // [parent_env, env, ...] env=value*
    List *c;  // [OP,OP,OP, ...]
    List *d; // [(s*, e*, c*, d*), ...] stackframe
    size_t pc;  // next c
} Frame;

typedef struct vm
{
    Frame *frame;
    int running;  // bool
    int error;  // bool
    value* NIL_CELL;
} VM;

ListField* make_list_field_val(List* list, value* val); 
ListField* make_list_field_op(List* list, OP val); 
ListField* make_list_field_frame(List* list, Frame* val); 

List* make_list(ListTag tag);

ListField* list_pop(List* list);
void list_push(List* list, ListField* val);
ListField* list_peek(List* list, size_t pos);
List* list_resize(List* list);


Frame* make_frame();



void vm_new_frame(VM* vm);
void vm_return_frame(VM* vm);

VM* vm_init();

ListField* vm_pop(List* list);
void vm_push(List* list, void* val);
ListField* vm_peek(List* list, size_t pos);

void run_vm(VM* vm);

#endif // VM_H
