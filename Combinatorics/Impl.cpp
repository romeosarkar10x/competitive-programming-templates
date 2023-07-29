#include <iostream>
#include <vector>


/**
 * #include <vector>
*/
namespace combinatorics
{
    namespace
    {
        static const int Max = 2000;
        static const long long Mod = (long long)1e18L + 9;

        static std::vector<std::vector<long long>> &nCr_precompute()
        {
            auto &nCr = *new std::vector<std::vector<long long>>(Max + 1, std::vector<long long>(Max + 1, 0)); 
            nCr.at(0).at(0) = 1;
            
            for(int n = 0; n <= Max; n++)
            {
                nCr.at(n).at(0) = 1;
                for(int r = 1; r < n; r++)
                {
                    nCr.at(n).at(r) = (nCr.at(n - 1).at(r) + nCr.at(n - 1).at(r - 1)) % Mod;
                }
                nCr.at(n).at(n) = 1;
            }
            return nCr;
        }
    }
    long long nCr(int n, int r) // n => [0, Max] && r => [0, n]
    {
        if((n < 0 || n > Max) || (r < 0 || n < r))
        {
            return -1LL;
        }

        static auto &nCr = nCr_precompute();
        return nCr.at(n).at(r);
    }
}


int main()
{
    clock_t clock_start = clock();
    for(int i = 0; i < 10000; i++)
    {
        for(int j = 0; j < 10000; j++)
        {
            combinatorics::nCr(i, j);
        }
    }

    std::cout << "total_time: " << ((double)(clock() - clock_start)) / (double)CLOCKS_PER_SEC << " seconds\n";
    // std::cout << combinatorics::nCr(5, 3) << "\n";
    return 0;
}