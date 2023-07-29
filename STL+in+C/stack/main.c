#include <stdio.h>

struct pair
{
    int val, n;
};

#include "sources/stack.c"

STACK(struct pair);
struct pair makePair (int val, int n)
{
    struct pair p={val, n};
    return p;
}
void display (struct stack *s)
{
    printf ("\e[1;32m[\e[m");
    while (!empty (s))
    {
        struct pair p=top (s);
        printf ("%d,%d", p.val, p.n);
        pop (s);
        if (!empty(s))
        {
            printf ("\e[1;31m(\e[m");
        }
    }
    printf ("\e[1;32m]\e[m\n");
}

int main ()
{
    struct stack s={0,0,NULL};
    push (&s, makePair (23, 4));
    push (&s, makePair (543, 7));
    push (&s, makePair (15, 8));
    push (&s, makePair (243, 9));
    push (&s, makePair (7, 6));
    // push (&s, 12);
    // push (&s, 6);
    // push (&s, 78);
    // push (&s, 23);
    // push (&s, 9);
    // push (&s, 10);
    display (&s);
    int *p = malloc (100);
    p[0] = 134;
    printf ("hello world\n");
    return 0;
}