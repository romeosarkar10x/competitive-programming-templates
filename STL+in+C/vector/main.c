#include "sources/vector.c"
#include <stdio.h>

VECTOR(int);

void display (struct vector *v)
{
    printf ("[");
    for (int i=0; i<v->_size; i++)
    {
        printf ("%d", at(v, i));
        if (i<v->_size-1)
        {
            printf (",");
        }
    }
    printf ("]\n");
}
void pop (struct vector *v)
{
    printf ("[");
    for (; v->_size; )
    {
        printf ("%d", pop_back (v));
        if (v->_size)
        {
            printf (",");
        }
    }
    printf ("]\n");
}

void swap (int *a, int *b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
    return;
}
int main ()
{
    struct vector v={0, 0, NULL};
    printf ("%zd %zd\n", size (&v), capacity (&v));
    push_back (&v, 0);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    push_back (&v, 2);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    push_back (&v, 4);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    push_back (&v, 9);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    push_back (&v, 6);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    push_back (&v, 8);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    push_back (&v, 5);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    push_back (&v, 3);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    push_back (&v, 8);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    display (&v);
    pop_back (&v);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    pop_back (&v);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    pop_back (&v);
    pop_back (&v);
    pop_back (&v);
    printf ("%zd %zd\n", size (&v), capacity (&v));
    display (&v);
    // swap (&at (&v, 0), &at (&v, 9));
    pop (&v);
    display (&v);
    clear (&v);
    int *p = malloc (100);
    p[0] = 134;
    printf ("hello world\n");
    return 0;
}