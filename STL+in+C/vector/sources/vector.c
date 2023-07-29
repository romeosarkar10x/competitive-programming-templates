#ifndef VECTOR_H
#define VECTOR_H


#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZ
char _charBuf[128];
int _idx;
#define VECTOR(type) \
struct vector\
{\
    size_t _size, _capacity;\
    type *p;\
};\
void push_back (struct vector *_vector, type _element)\
{\
    if(_vector->_capacity==_vector->_size)\
    {\
        if (_vector->_capacity==0) \
        {\
            _vector->_capacity++;\
        }\
        else \
        {\
            _vector->_capacity<<=1;\
        }\
        _vector->p=realloc(_vector->p, _vector->_capacity*sizeof(type));\
    }\
    _vector->p[_vector->_size++]=_element;\
    return;\
}\
type pop_back (struct vector *_vector)\
{\
    if(_vector->_size==(_vector->_capacity>>1+1))\
    {\
        _vector->_capacity>>=1;\
        _vector->p=realloc(_vector->p, _vector->_capacity*sizeof(type));\
    }\
    return _vector->p[--(_vector->_size)];\
}\
void clear (struct vector *_vector)\
{\
    _vector->_size=_vector->_capacity=0;\
    free (_vector->p);\
    _vector->p=NULL;\
    return;\
}\
type *_at (struct vector *_vector, size_t i)\
{\
    if(i<_vector->_size)\
    {\
        return _vector->p+i;\
    }\
    else\
    {\
        printf ("error: index out of bound\n");\
        exit (-1);\
    }\
}
#define size(_vector) ((_vector)->_size)
#define capacity(_vector) ((_vector)->_capacity)
#define at(_vector, _i) *(_at (_vector, _i))
#endif