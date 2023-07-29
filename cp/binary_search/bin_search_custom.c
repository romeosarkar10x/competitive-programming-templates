#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
struct S
{
    int i;
    char c;
};
int cmp (const void *_a, const void *_b)
{
    const struct S a = *((const struct S *) (_a));
    const struct S b = *((const struct S *) (_b));
    return a.i - b.i;
}
long long binary_search (void *_arr, size_t _len, size_t _elemSiz, void *_elem, int (*_cmp) (const void *_a, const void *_b))
{
    long long l = 0, h = _len - 1;
    while (l <= h)
    {
        // printf ("\e[31m(%llu;%llu)\e[m", l, h);
        long long mid = (l + h) / 2;
        void *p = _arr + _elemSiz * mid;
        int flag = cmp (_elem, p);
        if (flag > 0)
        {
            l = mid + 1;
        }
        else if (flag == 0)
        {
            return mid;
        }
        else
        {
            h = mid - 1;
        }
    }
    return -1;
}
struct S *create (size_t _len, ...)
{
    va_list list;
    va_start (list, _len);
    struct S *p = malloc (sizeof (struct S) * _len);
    for (size_t i = 0; i < _len; i++)
    {
        int arg = va_arg (list, int);
        p[i].i = arg;
        p[i].c = (rand () % (127 - 32)) + 32;
    }
    return p;
}
int main ()
{
    size_t len = 6;
    struct S *arr = create (6, 1, 3, 5, 7, 9, 11);
    for (int i = 0; i < len; i++)
    {
        printf ("%d,%c ", arr[i].i, arr[i].c);
    }
    printf ("\n");
    for (int i = 0; i < len; i++)
    {
        int idx = binary_search (arr, len, sizeof (struct S), &arr[i], cmp);
        printf ("(%d,\'%c\') ", arr[idx].i, arr[idx].c);
    }
    printf ("\n");

    return 0;
}