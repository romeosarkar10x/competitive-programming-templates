#include <stdio.h>
int cntSetBits (int _number)
{
    int cnt = 0;
    while (_number)
    {
        cnt++;
        _number &= (_number - 1);
    }
    return cnt;
}
int leastSignificantBit (int _number)
{
    return _number ^ (_number & (_number - 1));
}
int mostSignificantBit (int _number)
{
    while (_number & (_number - 1))
    {
        _number &= (_number - 1);
    }
    return _number;
}
int main ()
{
    // printf ("%d\n", cntSetBits (235));
    printf ("%d\n", leastSignificantBit (2));
    printf ("%d\n", mostSignificantBit (126));
    return 0;
}