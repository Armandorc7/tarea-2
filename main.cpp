#include <iostream>
#include <vector>
#include <list>
#include <concepts>
#include <iterator>
#include <cmath>
#include <type_traits>
#include <string>
#include <stdexcept>

using namespace std;

namespace core_numeric {

// ===== CONCEPTS =====

template<typename C>
concept Iterable = requires(C c) {
    begin(c);
    end(c);
};

template<typename C>
concept Sized = Iterable<C> && requires(C c) {
    c.size();
};

template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> same_as<T>;
};

template<typename T>
concept Divisible = requires(T a, size_t n) {
    a / n;
};

template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> convertible_to<bool>;
    { a > b } -> convertible_to<bool>;
};

template<typename T>
concept Numeric = Addable<T> && Comparable<T> && requires(T a, T b) {
    { a - b } -> same_as<T>;
    { a * b } -> same_as<T>;
};

template<typename T>
using MeanT = conditional_t<is_integral_v<T>, double, T>;

// ===== ALGORITMOS =====

template<Sized C>
requires Addable<typename C::value_type>
auto sum(const C& c) {
    using T = typename C::value_type;
    T r{};
    for (auto& x : c) r = r + x;
    return r;
}

template<Sized C>
requires Addable<typename C::value_type> && Divisible<typename C::value_type>
auto mean(const C& c) {
    using T = typename C::value_type;
    using R = MeanT<T>;
    if (c.size() == 0) return R{};
    R s{};
    for (auto& x : c) s += static_cast<R>(x);
    return s / c.size();
}

template<Sized C>
requires Numeric<typename C::value_type> && Divisible<typename C::value_type>
auto variance(const C& c) {
    using T = typename C::value_type;
    using R = MeanT<T>;
    if (c.size() == 0) return R{};
    R m = mean(c);
    R s{};
    for (auto& x : c) {
        R d = static_cast<R>(x) - m;
        s += d * d;
    }
    return s / c.size();
}

template<Sized C>
requires Comparable<typename C::value_type>
auto max_element(const C& c) {
    if (c.size() == 0) throw invalid_argument("vacio");
    auto it = begin(c);
    auto m = *it++;
    for (; it != end(c); ++it)
        if (*it > m) m = *it;
    return m;
}

template<Sized C, typename F>
requires Addable<decltype(declval<F>()(declval<typename C::value_type>()))>
auto transform_reduce(const C& c, F f) {
    using R = decltype(f(*begin(c)));
    R r{};
    for (auto& x : c) r = r + f(x);
    return r;
}

// ===== VARIADIC =====

template<Addable... Ts>
auto sum_variadic(Ts... x) {
    return (x + ...);
}

template<typename... Ts>
requires (Addable<Ts> && ...)
auto mean_variadic(Ts... x) {
    using T = common_type_t<Ts...>;
    using R = MeanT<T>;
    return (static_cast<R>(x) + ...) / sizeof...(x);
}

template<typename... Ts>
requires (Numeric<Ts> && ...)
auto variance_variadic(Ts... x) {
    using T = common_type_t<Ts...>;
    if constexpr (is_integral_v<T>) {
        double m = mean_variadic(x...);
        double s = (((x - m) * (x - m)) + ...);
        return s / sizeof...(x);
    } else {
        T m = mean_variadic(x...);
        T s = (((x - m) * (x - m)) + ...);
        return s / sizeof...(x);
    }
}

template<typename... Ts>
requires Comparable<common_type_t<Ts...>>
auto max_variadic(Ts... x) {
    using T = common_type_t<Ts...>;
    T m{};
    bool first = true;
    auto f = [&](auto v) {
        T t = static_cast<T>(v);
        if (first) { m = t; first = false; }
        else if (t > m) m = t;
    };
    (f(x), ...);
    return m;
}

} // namespace core_numeric

// ===== CLASE Vector3D =====

class Vector3D {
    double x, y, z;
public:
    Vector3D(double x=0,double y=0,double z=0):x(x),y(y),z(z){}

    Vector3D operator+(const Vector3D& o) const {
        return {x+o.x, y+o.y, z+o.z};
    }

    Vector3D& operator+=(const Vector3D& o){
        x += o.x;
        y += o.y;
        z += o.z;
        return *this;
    }

    Vector3D operator-(const Vector3D& o) const {
        return {x-o.x, y-o.y, z-o.z};
    }

    Vector3D operator*(const Vector3D& o) const {
        return {x*o.x, y*o.y, z*o.z};
    }

    Vector3D operator/(size_t n) const {
        return {x/n, y/n, z/n};
    }

    bool operator>(const Vector3D& o) const { return mag() > o.mag(); }
    bool operator<(const Vector3D& o) const { return mag() < o.mag(); }

    double mag() const { return sqrt(x*x + y*y + z*z); }

    friend ostream& operator<<(ostream& os,const Vector3D& v){
        return os<<"("<<v.x<<","<<v.y<<","<<v.z<<")";
    }
};

// ===== MAIN =====

int main() {
    using namespace core_numeric;

    cout << "TEST QUE COMPILAN\n\n";

    cout << "Test 1\n";
    vector<int> a{1,2,3,4};
    cout << sum(a) << endl << endl;

    cout << "Test 2\n";
    cout << mean(a) << endl << endl;

    cout << "Test 3\n";
    cout << variance(a) << endl << endl;

    cout << "Test 4\n";
    cout << max_element(a) << endl << endl;

    cout << "Test 5\n";
    cout << transform_reduce(a, [](int x){ return x*2; }) << endl << endl;

    cout << "Test 6\n";
    cout << sum_variadic(1,2,3) << endl;
    cout << mean_variadic(1,2,3) << endl;
    cout << variance_variadic(1,2,3) << endl;
    cout << max_variadic(1,2.5,3) << endl << endl;

    cout << "Test 7\n";
    vector<Vector3D> v{{1,0,0},{0,1,0},{0,0,1}};
    cout << sum(v) << endl;
    cout << mean(v) << endl;
    cout << max_element(v) << endl << endl;

    cout << "TEST QUE NO COMPILAN (comentados)\n";

    // vector<const char*> p{"hola","mundo"};
    // sum(p); // Addable falla

    // vector<char> c{'a','b'};
    // mean(c); // char + char -> int

    // vector<string> s{"a","b"};
    // variance(s); // Numeric falla

    // struct X{int a;};
    // vector<X> vx{{1}};
    // max_element(vx); // Comparable falla

    return 0;
}