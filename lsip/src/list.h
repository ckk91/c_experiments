
typedef enum {
    _OP, _VAL, _FRAME
} ListTag;

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