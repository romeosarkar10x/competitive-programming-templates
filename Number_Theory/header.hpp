#include <iostream>
#include <vector>
#include <cmath>


namespace number_theory
{
    typedef unsigned int u_int;
    typedef unsigned long long u_ll;

    extern const u_int kMax;
    extern const u_ll kMax_square;
    extern const u_int Invalid;

    bool is_prime(u_int);
    u_int get_next_prime(u_int);

    const std::vector<u_int> &get_vector_primes();
    std::vector<u_int> get_prime_factors(u_ll);
}