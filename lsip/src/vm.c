#include <stdlib.h>
#include <stdio.h>

#include "vm.h"
#include "types.h"
/*
control layout:
:HEADER
->META
->PROGRAM
->DATA
:PROGRAM
000 LOADC ...
NNN ...
END STOP*10
:DATA // interned strings n shit
*/

Frame* make_frame() {
    Frame* frame = malloc(sizeof *frame);
    if (!frame)
    {
        return frame;
    }
    
    frame->s = make_list(_VAL);
    frame->e = make_list(_VAL);
    frame->c = make_list(_OP);
    frame->d = make_list(_FRAME);
    frame->pc = 0;

    return frame;
}

void vm_new_frame(VM* vm) {
    Frame* frame = make_frame();
    list_push(frame->d, vm->frame);
    vm->frame = frame;
}

void vm_return_frame(VM* vm) {
    vm->frame = list_pop(vm->frame->d);
}

VM* vm_init() {
    value* NIL_CELL=v_alloc();
    VM* vm = malloc(sizeof *vm);
    vm->frame = make_frame();
    vm->error = 0;
    vm->running = 0;
    vm->NIL_CELL = NIL_CELL;
    return vm;
}

ListField* vm_pop(List* list){
    return list_pop(list);
}

void vm_push(List* list, void* val) {
    list_push(list, make_list_field_val(list, val));  // todo dispatch
}

ListField* vm_peek(List* list, size_t pos) {
    return list_peek(list, pos);
}

void run_vm(VM* vm){
    vm->running = 1;
    OP curr;

    while (vm->running)
    {
        // fetch        
        curr = vm_peek(vm->frame->c, vm->frame->pc++)->o;
        // decode
        switch (curr)
        {
        case NIL:
            vm_push(vm->frame->s, vm->NIL_CELL);
            break;
        
        case LOADC:  // todo evtl dispatch by data type?
            vm_push(
                vm->frame->s,
                make_int(vm_peek(vm->frame->c, vm->frame->pc++)->o)
            );
            break;

        case CONS:
            {
            ListField* a = vm_pop(vm->frame->s);
            ListField* b = vm_pop(vm->frame->s);
            vm_push(vm->frame->s, cons(a->v, b->v));
            }
            break;

        case LAM:
            // s->(c, e)
            // ListField* c = {c, vm->frame->e}
            vm_push(vm->frame->s, )
            break;

        case STOP:
            vm->running = 0;
            break;

        default:
            printf("Unknown OPCODE: %i. stopping.\n", curr);
            vm->running = 0;
            vm->error = 1;
            break;
        }
        // execute
    }
    
}