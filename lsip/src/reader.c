#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "reader.h"
#include "types.h"


char* read_string_from_input(FILE *fp) {
    //struct stream* s = malloc(sizeof *s);
    
    int pos = 0;
    int ch = EOF;
    size_t len = 0;
    const int START_LENGTH = 16;
    size_t size = START_LENGTH;
    char *str = malloc(sizeof(char)*START_LENGTH);
    if (!str)
    {
        return str;  // 0
    }
    
    while (ch)
    {
        ch = getc(fp);
        if (ch == EOF ||  ch == '\n')
        {
            break;
        }
        str[len]=ch;
        len++;
        if (len == size)
        {
            size += START_LENGTH;
            str = realloc(str, sizeof(char)*size);
            if (!str)
            {
                return str;  // 0
            }
        }    
        
    }
    str[len]='\0';  // null termination
    len++;
    str = realloc(str, sizeof(char)*len);
    return str;  // todo free
}

char*
tokenize(char* str, size_t* pos, char breaks[], int breaks_len) {
    printf("TOKENIZE %zu\n", *pos);

    size_t START = 16;
    size_t size = START;
    size_t len = 0;

    char *token = malloc(sizeof(char)*START);
    int broken = 0;
    char ch = EOF;    
    while (ch)
    {
        ch = str[*pos];
        printf("TOKENIZE POS %zu\n", *pos);

        for (size_t i = 0; i < breaks_len; i++)
        {
            if (ch == breaks[i])  // ch == ' ' || ch == '\n' || ch=='\0'
            {   
                broken = 1;
                break;
            }
            
        }
        if (broken)
        {
            broken = 0;
            break;
        }
        
        
        token[len] = ch;
        len += 1;
        *pos += 1;
        if (len == size)
        {
            size += START;
            token = realloc(token, sizeof(char)*size);
            if (!token)
            {
                return token;
            }
            
        }

    }
    token[len] = '\0';
    len += 1;
    token = realloc(token, sizeof(char)*len);
    return token;
}

value*
read_symbol(char* str, size_t* pos) {
    printf("READ SYM %zu\n", *pos);

    char breaks[] = {' ', '\n', ')', '\0'};
    char* token = tokenize(str, pos, breaks, sizeof(breaks));
    value* v = make_sym(token);
    free(token);
    return v;
}

value*
read_num(char* str, size_t* pos){  // only int for now
    printf("READ NUM %zu\n", *pos);

    char breaks[] = {' ', '\n', ')'};
    char* token = tokenize(str, pos, breaks, sizeof(breaks));
    value* num = make_int(atoi(token)); 
    free(token);
    return num;    
}

value*
read_list(char* str, size_t* pos) {
    printf("READ LIST %zu\n", *pos);
    value *v;
    char ch = EOF;
    while (ch)
    {
        ch = str[*pos];
        *pos += 1;

        if (ch == ' ' || ch == '\n')  // skip whitespace after (
        {
            continue;            
        }
        if (ch == ')')
        {
            return NULL;
        }
        if (ch== '.')
        {
            return read_expr(str, pos);
        }
        
        *pos -= 1;

        v = read_expr(str, pos);  // n nelements        

        return cons(v, read_list(str, pos));  // TODO test for n elements
    }
}




value* read_expr(char* str, size_t* pos) {  // dispatch
    /*
    expr = list || INT || SYMBOL
    list = (expr [.] [expr ...])
    SYMBOL = ALNUM, no () or spc
    */
    // struct stream* s = malloc(sizeof *s);
    char ch = EOF;
    printf("READ EXPR %zu\n", *pos);
    while (ch)
    {
        ch = str[*pos];
        *pos += 1;
        
        if (ch == EOF || ch == NULL) {
            break;
        }

        if (ch == ' ' || ch == '\n') {
            continue;
        }
        if (ch == '(') {
            return read_list(str, pos);
        }
        if (isalpha(ch) || ispunct(ch)) {
            *pos -= 1;

            return read_symbol(str, pos);
        }
        if (isdigit(ch))
        {
            return read_num(str, pos);
        }

        printf("UNKNOWN CHAR: %c %i", ch, (int)ch);
        getchar();
        break;
    }
    return NULL;
}
