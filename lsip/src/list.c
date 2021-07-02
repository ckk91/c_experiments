
List* make_list(ListTag tag){
    List* list = malloc(sizeof *list);
    if (!list)
    {
        return list;
    }
    list->tag = tag;
    list->head = -1;  // todo uninit -1
    list->length = 255;
    
    return list;
}

ListField* make_list_field_val(List* list, value* val) {
    ListField* lf = malloc(sizeof *lf);
    lf->tag = list->tag;
    lf->v = val;
    return lf;
}
ListField* make_list_field_op(List* list, OP val) {
    ListField* lf = malloc(sizeof *lf);
    lf->tag = list->tag;
    lf->o = val;
    return lf;
}
ListField* make_list_field_frame(List* list, Frame* val) {
    ListField* lf = malloc(sizeof *lf);
    lf->tag = list->tag;
    lf->f = val;
    return lf;
}

ListField* list_pop(List* list) {
    return list->arr[list->head--];  // todo check underrun
}

void list_push(List* list, ListField* val) {
    list->head += 1;

    if (list->head >= list->length)
    {
       list_resize(list);  // todo return handling
    }
    list->arr[list->head] = val;
}

ListField* list_peek(List* list, size_t pos) {
    return list->arr[pos];
}

List* list_resize(List* list) {
    int new_size = list->length*2;
    *list->arr = realloc(list->arr, sizeof(list->arr)*new_size);
    list->length = new_size;
    return list;
}
