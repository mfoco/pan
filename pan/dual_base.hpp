
#ifndef _DUAL_BASE_
#define _DUAL_BASE_

#include <cmath>
#include <ostream>

namespace pan
{
    template <typename T> class dual_base
    {
        T _a, _b;
    public:
        constexpr dual_base() = default;
        constexpr dual_base(const dual_base<T> &) = default;
        constexpr dual_base(dual_base<T> &&) = default;
        //constexpr dual_base<T> & operator = (const dual_base<T> &) = default;
        //constexpr dual_base<T> & operator = (dual_base<T> &&) = default;

        constexpr dual_base(T a, T b) noexcept : _a(a), _b(b) {}

        constexpr T real() const noexcept { return _a; }
        constexpr T dual() const noexcept { return _b; }

        constexpr auto operator + () const noexcept
        {
            return *this;
        }

        constexpr dual_base<T> operator - () const noexcept(noexcept(-_a) && noexcept(-_b))
        {
            return{ -_a , -_b };
        }

        /*constexpr*/ dual_base<T> &operator += (T other) noexcept(noexcept(_a += other)) 
        {
            _a += other;
            return *this;
        }

        /*constexpr*/ dual_base<T> &operator += (const dual_base<T> &other) noexcept(noexcept(_a += other._a))
        {
            _a += other._a;
            _b += other._b;
            return *this;
        }

        /*constexpr*/ dual_base<T> &operator -= (T other) noexcept(noexcept(_a -= other))
        {
            _a -= other;
            return *this;
        }

        /*constexpr*/ dual_base<T> &operator -= (const dual_base<T> &other) noexcept(noexcept(_a -= other._a))
        {
            _a -= other._a;
            _b -= other._b;
            return *this;
        }

        /*constexpr*/ dual_base<T> &operator *= (T other) noexcept(noexcept(_a *= other))
        {
            _a *= other;
            _b *= other;
            return *this;
        }

        /*constexpr*/ dual_base<T> &operator *= (const dual_base<T> &other) noexcept(noexcept(_a *= other._a) && noexcept(_b += _a*other._b))
        {
            auto tmp = _a*other._b;
            _a *= other._a;
            _b *= other._a;
            _b += tmp;
            return *this;
        }

        /*constexpr*/ dual_base<T> &operator /= (T other) noexcept(noexcept(_a /= other))
        {
            _a /= other;
            _b /= other;
            return *this;
        }

        /*constexpr*/ template<typename U> dual_base<T> &operator /= (const dual_base<U> &other) noexcept(noexcept(*this *= conj(other)) && noexcept(*this /= norm(other)))
        {
            *this *= conj(other);
            return *this /= norm(other);
        }
    };

    template <typename T> constexpr dual_base<T> operator + (const dual_base<T> &a, T b) noexcept(noexcept(a.real() + b))
    {
        return{ a.real() + b, a.dual() };
    }

    template <typename T> constexpr dual_base<T> operator + (T a, const dual_base<T> &b) noexcept(noexcept(a.real() + b))
    {
        return{ a + b.real(), b.dual() };
    }

    template <typename T> constexpr dual_base<T> operator + (const dual_base<T> &a, const dual_base<T> &b) noexcept(noexcept(a.real() + b.real()) && noexcept(a.dual() + b.dual()))
    {
        return{ a.real() + b.real(), a.dual() + b.dual() };
    }

    template <typename T> constexpr dual_base<T> operator - (const dual_base<T> &a, T b) noexcept(noexcept(a.real() - b))
    {
        return{ a.real() - b, a.dual() };
    }

    template <typename T> constexpr dual_base<T> operator - (T a, const dual_base<T> &b) noexcept(noexcept(a - b.real()) && noexcept(- b.dual()))
    {
        return{ a - b.real(), - b.dual() };
    }

    template <typename T> constexpr dual_base<T> operator - (const dual_base<T> &a, const dual_base<T> &b) noexcept(noexcept(a.real() - b.real()) && noexcept(a.dual() - b.dual()))
    {
        return{ a.real() - b.real(), a.dual() - b.dual() };
    }

    template <typename T> constexpr dual_base<T> operator * (const dual_base<T> &a, T b) noexcept(noexcept(a.real() * b) && noexcept(a.dual() * b))
    {
        return{ a.real() * b, a.dual() * b };
    }

    template <typename T> constexpr dual_base<T> operator * (T a, const dual_base<T> &b) noexcept(noexcept(a * b.real()) && noexcept(a * b.dual()))
    {
        return{ a * b.real(), a * b.dual() };
    }

    template <typename T> dual_base<T> operator * (const dual_base<T> &a, const dual_base<T> &b)  noexcept(noexcept(a.real() * b.real()) && noexcept(a.real()*b.dual() + a.dual()*b.real()))
    {
        return{ a.real()*b.real(), a.real()*b.dual() + a.dual()*b.real() };
    }

    template <typename T> dual_base<T> operator / (const dual_base<T> &a, T b) noexcept(noexcept(a.real() / b) && noexcept(a.dual() / b))
    {
        return{ a.real() / b, a.dual() / b };
    }

    template <typename T> dual_base<T> operator / (T a, const dual_base<T> &b) noexcept(noexcept(b.real() / a) && noexcept(a.dual() / b))
    {
        auto r = real(b);
        return (a * conj(b)) / (r*r);
    }

    template <typename T> auto operator / (const dual_base<T> &a, const dual_base<T> &b) noexcept(noexcept(a.real() / b.real()))
    {
        auto r = real(b);
        return (a * conj(b)) / (r*r);
    }

    template <typename T> decltype(auto) real(const dual_base<T> &other) noexcept
    {
        return other.real();
    }

    template <typename T> decltype(auto) dual(const dual_base<T> &other) noexcept
    {
        return other.dual();
    }

    template <typename T> auto abs(const dual_base<T> &other)
    {
        using namespace std;
        return ::abs(other.real());
    }

    constexpr auto conj(double x) noexcept { return x; }
    constexpr auto conj(float x) noexcept { return x; }

    template <typename T> dual_base<T> conj(const dual_base<T> &other)
    {
        return{ other.real(), -other.dual() };
    }

    template <typename T> auto norm(const dual_base<T> &other)
    {
        decltype(auto) r = other.real();
        return r*r;
    }

    template <typename T> dual_base<T> exp(const dual_base<T> &other)
    {
        using std::exp;
        auto e = exp(other.real());
        return{ e, e*other.dual() };
    }

    template <typename T> dual_base<T> log(const dual_base<T> &other)
    {
        using std::log;
        decltype(auto) r = other.real();
        return{ log(r), other.dual() / r };
    }

    template <typename T> dual_base<T> pow(const dual_base<T> &left, const dual_base<T> &right)
    {
        return exp(right*log(left));
        //using std::log;
        //decltype(auto) lr = left.real();
        //auto loglr = log(lr);
        //using std::exp;
        //auto e = exp(loglr*right.real());
        //return{ e, e*(right.real()*left.dual() / lr + right.dual()*loglr) };
    }

   template <typename T, typename T2> dual_base<T> pow(const dual_base<T> &left, const T2 &right)
    {
        return exp(right*log(left));
        //using std::pow;
        //decltype(auto) lr = left.real();
        //auto e = pow(lr, right);
        //return{ e, e*(right*left.dual() / lr) };
   }

    template <typename T, typename T2> dual_base<T> pow(const T2 &left, const dual_base<T> &right)
    {
        using std::log;
        return exp(right*log(left));
        //using std::log;
        //auto logl = log(left);
        //using std::exp;
        //auto e = exp(logl*right.real());
        //return{ e, e*(right.dual()*logl) };
    }

    template <typename T> dual_base<T> sin(const dual_base<T> &other)
    {
        using namespace std;
        return{ ::sin(other.real()), ::cos(other.real())*other.dual() };
    }

    template <typename T> dual_base<T> cos(const dual_base<T> &other)
    {
        using namespace std;
        return{ ::cos(other.real()), -::sin(other.real())*other.dual() };
    }

    template<typename _Ty, typename _Elem, typename _Tr> inline std::basic_ostream<_Elem, _Tr>& operator<<(std::basic_ostream<_Elem, _Tr>& ostr, const dual_base<_Ty>& right) {
        const auto& facet = std::use_facet<std::ctype<_Elem>>(ostr.getloc());
        return ostr << facet.widen('(') << real(right)
            << facet.widen(',') << dual(right)
            << facet.widen(')');
    }
}

#endif
