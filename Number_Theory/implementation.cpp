#include <iostream>
#include <vector>

namespace number_theory
{

    typedef long long ll;

    typedef unsigned long long u_ll;
    typedef unsigned int u_int;
    class Modulo
    {

        friend std::ostream &operator <<(std::ostream &, Modulo &);
        friend std::ostream &operator <<(std::ostream &, Modulo &&);
        friend std::istream &operator >>(std::istream &, Modulo &);
    public:

        // constructors:
        Modulo(u_ll _mod, u_ll _n) : mod_(_mod), n_(_n)
        {
            if(0 == mod_)
            {
                std::cout << "error: mod_ == 0\n";
                // throw error
            }

            n_ %= mod_;
        }
        Modulo(u_ll _mod) : Modulo(_mod, 0ULL) { }

        
        // cast operators:
        operator u_ll()
        {
            return n_;
        }
        operator u_int()
        {
            if(n_ > (u_ll)UINT_MAX)
            {
                std::cout << "n_ > " << (u_ll)UINT_MAX << "\n";
                // throw error
            }

            return (u_int)n_;
        }
        operator ll()
        {
            if(n_ > (u_ll)LONG_LONG_MAX)
            {
                std::cout << "n_ > " << (u_ll)LONG_LONG_MAX << "\n";
                // throw error
            }

            return (ll)n_; 
        }
        operator int()
        {
            if(n_ > (u_ll)INT_MAX)
            {
                std::cout << "n_ > " << (u_ll)INT_MAX << "\n";
                // throw error
            }

            return (u_int)n_;
        }
        
        
        // assignment operators:
        Modulo operator =(u_ll _x)
        {
            // *this = Modulo
            n_ = _x % mod_;
            return *this;
        }
        Modulo operator =(u_int _x)
        {
            n_ = _x % mod_;
            return *this;
        }
        Modulo operator =(int _x)
        {
            if(_x < 0)
            {
                std::cout << "error: _x < 0\n";
                // throw error
            }

            n_ = (u_int)_x % mod_;
            return *this;
        }
        Modulo operator =(ll _x)
        {
            if(_x < 0)
            {
                std::cout << "error: ll _x < 0\n";
                // throw error
            }

            n_ = (u_int)_x % mod_;
            return *this;
        }

        // arithmetic operators:
        // addition (+)
        Modulo operator +(Modulo _m2)
        {
            if(mod_ != _m2.mod_)
            {
                // throw an exception
            }
            
            return Modulo(mod_, (n_ + _m2.n_) % mod_);
        }
        Modulo operator +(u_ll _x)
        {
            return Modulo(mod_, (n_ + _x) % mod_);
        }
        Modulo operator +(u_int _x)
        {
            return Modulo(mod_, (n_ + (u_ll)_x) % mod_);
        }
        // multiplication (*)
        Modulo operator *(u_ll _x)
        {
            return Modulo(mod_, modular_multiplication_(_x, n_));
        }
        // Modulo operator
        

        /*
        Modulo &operator +=(int _x)
        {
            u_ll x;
            if(_x < 0)
            {
                // x = 
                std::cout << "error: _x < 0\n";
                // throw error
            }

            n_ += (u_ll)_x;
            n_ %= mod_;

            return *this;
        }
        Modulo &operator +=(Modulo _m2)
        {
            if(mod_ != _m2.mod_)
            {
                // throw an exception
            }

            n_ += _m2.n_;
            n_ %= mod_;

            return *this;
        }

        */
    private:
        u_ll mod_;
        u_ll n_;
        u_ll modular_multiplication_(u_ll _a, u_ll _b)
        {
            u_ll ans = 0ULL;
            while(_b != 0ULL)
            {
                if((_b & 1) != 0)
                {
                    ans += _a;

                    if(ans >= mod_)
                    {
                        ans %= mod_;
                    }
                }

                _a <<= 1;

                if(_a >= mod_)
                {
                    _a %= mod_;
                }

                _b >>= 1;
            }
            return ans;
        }
    };

    std::ostream &operator <<(std::ostream &_o, Modulo &_m)
    {
        _o << _m.n_;
        return _o;
    }
    std::ostream &operator <<(std::ostream &_o, Modulo &&_m)
    {
        _o << _m.n_;
        return _o;
    }
    std::istream &operator >>(std::istream &_i, Modulo &_m)
    {
        std::string s;
        std::cin >> s;
        
        // u_ll n = 0ULL;
        // u_int length = s.length();
        // for(u_int i = 0; i < length; i++)
        // {
            
        // }
        // auto x = _m.n_;
        // _i >> x;
        // _m = Modulo(_m.mod_, x);
        return _i;
    }
}


int main()
{
    // number_theory::Modulo m((unsigned long long)LONG_LONG_MAX);
    // std::cin >> m;
    // std::cout << m << " ";
    // std::cout << m << "\n";
    // m += -1234;
    // std::cout << m << "\n";

    unsigned long long x;
    std::cin >> x;
    std::cout << x << " ";

    x *= 10;
    std::cout << x << " ";

}