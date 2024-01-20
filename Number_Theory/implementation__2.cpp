#include <iostream>
#include <vector>
#include <cmath>

#include "header.hpp"

namespace number_theory
{
    typedef unsigned int u_int;
    typedef unsigned long long u_ll;

    const u_int kMax = 5e7;

    const u_ll kMax_square = (u_ll)kMax * kMax;
    const u_int Invalid = 2111444111;

    namespace 
    {
        void range_check(u_int n)
        {
            if(n > kMax)
            {
                std::string error = std::string() +
                "number_theory::range_check: n (which is " + 
                std::to_string(n) +
                ") > kMax (which is " +
                std::to_string(kMax) +
                ")";
                throw std::out_of_range(error);
            }
        }
        void range_check(u_ll n)
        {
            if(n > kMax_square)
            {
                std::string error =  std::string() + 
                "number_theory::range_check: n (which is " +
                std::to_string(n) +
                ") > kMax_square (which is " +
                std::to_string(kMax_square) +
                ")";
                throw std::out_of_range(error);
            }
        }

        u_int square_root(u_int x)
        {
            if(0U == x)
            {
                return 0U;
            }

            u_int left = 1, right = x;
            while(left < right)
            {
                u_int mid = (left + right + 1) >> 1;
                
                if((u_ll)mid * mid <= x)
                {
                    left = mid;
                    continue;
                }
                right = mid - 1;
            }

            return left;
        }
    }


    bool is_prime(u_int n)
    {
        range_check(n);
        
        static const auto arr_flag_is_prime = [] () 
        {
            u_int kMax_square_root = square_root(kMax);
            auto arr_flag_is_prime = new bool[kMax + 1U];
            for(u_int u = 0; u <= kMax; u++)
            {
                arr_flag_is_prime[u] = true;
            }
            
            for(u_int u = 2; u <= kMax_square_root; u++)
            {
                if(arr_flag_is_prime[u])
                {
                    for(u_int u2 = u * u; u2 <= kMax; u2 += u)
                    {
                        arr_flag_is_prime[u2] = false;
                    }
                }
            }

            return arr_flag_is_prime;
        } ();

        return arr_flag_is_prime[n];
    }

    const std::vector<u_int>& get_vector_primes()
    {
        static const auto vec_primes = [] ()
        {
            auto vec_primes = *new std::vector<u_int>();
            for(u_int u = 2; u <= kMax; u++)
            {
                if(is_prime(u))
                {
                    vec_primes.push_back(u);
                }
            }
            return vec_primes;
        } ();

        return vec_primes;
    }

    u_int get_next_prime(u_int x)
    {
        range_check(x);
        
        static const auto arr_next_prime = [] ()
        {
            auto &vec_primes = get_vector_primes();
            
            auto arr_primes = vec_primes.data();
            u_int n_primes = vec_primes.size();

            auto arr_next_prime = new u_int[kMax + 1];
            
            u_int prime;
            u_int index = 0U, index_prime_max = n_primes - 1;
            for(u_int index_prime = 0U; index_prime < index_prime_max; index_prime++)
            {
                prime = arr_primes[index_prime];
                while(index < prime)
                {
                    arr_next_prime[index++] = prime;
                }
                
                prime = arr_primes[index_prime + 1];
                arr_next_prime[index++] = prime;
            }

            while(index <= kMax)
            {
                arr_next_prime[index++] = Invalid;
            }
            
            return arr_next_prime;
        } ();

        return arr_next_prime[x];
    }

    std::vector<u_int> get_prime_factors(u_ll n)
    {
        if(0ULL == n || 1ULL == n)
        {
            return std::vector<u_int>();
        }

        range_check(n);
        
        u_int n_square_root = square_root(n);
        std::vector<u_int> prime_factors;
        u_int prime = 2U;
        while(n != 1ULL && prime <= n_square_root)
        {
            if(n % prime == 0ULL)
            {
                prime_factors.push_back(prime);
            }

            while(n % prime == 0ULL)
            {
                n /= prime;
            }

            prime = get_next_prime(prime);
        }
        if(n != 1ULL)
        {
            prime_factors.push_back(n);
        }

        return prime_factors;
    }
    std::vector<u_int> get_prime_factors(u_int n)
    {
        if(0U == n || 1U == n)
        {
            return std::vector<u_int>();
        }

        range_check(n);
        
        u_int n_square_root = square_root(n);
        std::vector<u_int> prime_factors;
        u_int prime = 2U;
        while(n != 1U && prime <= n_square_root)
        {
            if(n % prime == 0U)
            {
                prime_factors.push_back(prime);
            }

            while(n % prime == 0U)
            {
                n /= prime;
            }

            prime = get_next_prime(prime);
        }
        if(n != 1U)
        {
            prime_factors.push_back(n);
        }

        return prime_factors;
    }
}


template<typename T>
std::ostream& operator<<(std::ostream& o, std::vector<T> vec_t)
{
    for(auto e : vec_t)
    {
        o << e << " ";
    }

    return o;
}
typedef unsigned int u_int;
int main()
{
    clock_t clock_start = clock();
    number_theory::is_prime(43);
    auto & vec_primes = number_theory::get_vector_primes();


    unsigned int prime = 2;
    std::vector<unsigned int> primes(10000);
    for(unsigned int u = 0; u < 10000 && prime != number_theory::Invalid; u++)
    {
        // std::cout << prime << " ";
        primes.at(u) = prime;
        prime = number_theory::get_next_prime(prime);
    }
    std::cout << prime << "\n";

    std::cout << vec_primes.at(0) << "\n";
    
    // for(unsigned int i = 0; i <= 100; i++)
    // {
    //     std::cout << "(" << i << ", " << number_theory::get_next_prime(i) << ") ";
    // }
    // std::cout << "\n";

    // number_theory::range_check_2(2);
    // std::vector<int> vec(1);
    // vec.at(2);
    // std::cout << number_theory::is_prime(1e7 + 1);

    // typedef unsigned int u_int;
    // for(u_int u = 0; u < 1000; u++)
    // {
    //     std::cout << primes.at(u) << " ";
    // }
    // std::cout << std::endl;
    // std::string s;
    // std::cin >> s;
    // const auto prime_factors = number_theory::get_prime_factors(2500000000000000U);
    for(u_int i = 0; i < 100000; i++)
    {
        number_theory::get_prime_factors(i);
    }
    std::cout << "total_time: " << ((double)clock() - clock_start) / CLOCKS_PER_SEC << " seconds \n";

    // std::cout << prime_factors << "\n";
    return 0;
}