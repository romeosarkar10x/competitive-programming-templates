#include <iostream>

typedef unsigned long long u_ll;

u_ll find_power(u_ll base, u_ll exponent)
{
    u_ll ans = 1;
    while(exponent != 0ULL)
    {
        if((exponent & 1ULL) != 0ULL)
        {
            ans *= base;
        }

        exponent >>= 1;
        base *= base;
    }

    return ans;
}

int main()
{
    std::cout << find_power(7ULL, 345345633ULL) << "\n";
}