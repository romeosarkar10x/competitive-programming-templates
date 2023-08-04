#include <iostream>
#include <vector>
#include <cmath>

#include "header.hpp"

namespace number_theory
{
    typedef unsigned int u_int;
    typedef unsigned long long u_ll;

    const u_int kMax = 1e7;

    namespace
    {
        u_int square_root(u_int x)
        {
            if(0U == x)
            {
                return 0U;
            }

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
    }


    bool is_prime(u_int n)
    {
        if(n > kMax)
        {
            // throw error!
            return false;
        }

        static auto arr_flag_is_prime = [] () 
        {
            u_int n = square_root(kMax);
            auto arr_flag_is_prime = new bool[kMax + 1U];
            for(u_int u = 0; u <= kMax; u++)
            {
                arr_flag_is_prime[u] = true;
            }
            
            for(u_int u = 2; u <= n; u++)
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

    const std::vector<u_int> &get_vec_primes()
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
        if(!is_prime(x))
        {
            // throw error!
        }

        static auto arr_next_prime = [] ()
        {
            auto &vec_primes = get_vec_primes();
            
            auto arr_primes = vec_primes.data();
            u_int n_primes = vec_primes.size();

            auto arr_next_prime = new u_int[kMax + 1];

            u_int index_max = n_primes - 1;
            for(u_int index = 0; index < index_max; index++)
            {
                u_int prime = arr_primes[index];
                u_int next_prime = arr_primes[index + 1];
                arr_next_prime[prime] = next_prime; 
            }
            
            return arr_next_prime;
        } ();
        
        return arr_next_prime[x];
    }
}

int main()
{
    clock_t clock_start = clock();
    number_theory::is_prime(43);
    auto & vec_primes = number_theory::get_vec_primes();


    unsigned int prime = 2;
    std::vector<unsigned int> primes(10000);
    for(unsigned int u = 0; u < 10000; u++)
    {
        // std::cout << prime << " ";
        primes.at(u) = prime;
        prime = number_theory::get_next_prime(prime);
    }
    std::cout << "total_time: " << ((double)clock() - clock_start) / CLOCKS_PER_SEC << " seconds \n";

    std::cout << vec_primes.at(0) << "\n";
    typedef unsigned int u_int;
    for(u_int u = 0; u < 1000; u++)
    {
        std::cout << primes.at(u) << " ";
    }
    std::cout << std::endl;
    std::string s;
    std::cin >> s;
    return 0;
}