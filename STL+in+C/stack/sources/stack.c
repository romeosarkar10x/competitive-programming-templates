#ifndef STACK_H
#define STACK_H


#include <stdio.h>
#include <stdlib.h>

#define STACK(type) \
struct stack\
{\
    size_t _size, _capacity;\
    type *p;\
};\
type null_return;\
void push (struct stack *_stack, type _element)\
{\
    if(_stack->_capacity==_stack->_size)\
    {\
        if (_stack->_capacity==0) \
        {\
            _stack->_capacity++;\
        }\
        else\
        {\
            _stack->_capacity<<=1;\
        }\
        _stack->p=realloc(_stack->p, _stack->_capacity*sizeof(type));\
    }\
    _stack->p[_stack->_size++]=_element;\
    return;\
}\
type pop (struct stack *_stack)\
{\
    if(_stack->_size==0)\
    {\
        return null_return;\
    }\
    type ret=_stack->p[--_stack->_size];\
    if(_stack->_size==(_stack->_capacity>>1))\
    {\
        _stack->_capacity>>=1;\
        _stack->p=realloc(_stack->p, _stack->_capacity*sizeof(type));\
    }\
    return ret;\
}\
type top (struct stack *_stack)\
{\
    return _stack->p[_stack->_size-1];\
}\
int empty (struct stack *_stack)\
{\
    if(0==_stack->_size)\
    {\
        return 1;\
    }\
    return 0;\
}

#endif