#include <iostream>
typedef unsigned int u_int;

const u_int Mod = 10;
u_int binary_multiplication(u_int _a, u_int _b)
{
    u_int ans = 0;
    while(_b != 0)
    {
        if((_b & 1) != 0)
        {
            ans += _a;
            ans %= 10;
        }
        
        _a <<= 1;
        _a %= 10;
        
        _b >>= 1;
    }
    
    return ans;
}

int main()
{
    std::cout << binary_multiplication(4, 6) << "\n";
    return 0;
}