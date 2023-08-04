#include <iostream>
#include <vector>
#include <cmath>


namespace number_theory
{
    typedef unsigned int u_int;
    typedef unsigned long long u_ll;

    extern const u_int kMax;

    bool is_prime(u_int);

    const std::vector<u_int> &get_vec_primes();

    u_int get_next_prime(u_int);
}