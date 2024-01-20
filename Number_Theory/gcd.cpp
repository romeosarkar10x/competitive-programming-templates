#include <iostream>

int gcd(int a, int b)
{
    if(a < b)
    {
        int tmp = b;
        b = a;
        a = tmp;
    }
    while(b != 0)
    {
        // auto [q, r] = std::div(a, b);
        // int q = a / b;
        // int r = a % b;

    }
    return 0;
}

int main()
{
    typedef unsigned int u_int;
    while(true)
    {
        u_int a, b;
        std::cin >> a >> b;

        u_int quotient = a / b;
        u_int remainder = a % b;


        std::cout << quotient << " " << remainder << std::endl;
    }
    // int a, b;
    // auto [q, r] = std::div(a, b);
    // std::cout << q << " " << r << std::endl;
    // std::cout << gcd(8, 12) << "\n";
    return 0;
}