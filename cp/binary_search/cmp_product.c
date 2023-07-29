#include <stdio.h>
#include <math.h>

// int cmp_product_gt(int a, int b, int x)
// { // compares if a * b > x
//     int 
// }


int cmp_product_le(int a, int b, int x)
{ // compares if a * b <= x
    int ab = 0;
    while(b)
    {

        if(a > x)
        {
            return 0;
        }

        if(b & 1)
        {
            ab += a;
        }

        if(ab > x)
        {
            return 0;
        }

        a <<= 1;
        b >>= 1;
    }

    if(ab > x)
    {
        return 0;
    }
    return 1;
}

int main()
{
    
    return 0;
}