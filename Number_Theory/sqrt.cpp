#include <iostream>

typedef unsigned int u_int;
typedef unsigned long long u_ll;
u_int square_root(u_int x)
{
    u_int left = 1, right = x;
    while(left < right)
    {
        u_int mid = (left + right + 1) / 2U;
        
        if((u_ll)mid * mid <= x)
        {
            left = mid;
            continue;
        }
        right = mid - 1;
    }

    return left;
}
int main()
{
    std::cout << square_root(312432543U) << "\n";
    return 0;
}