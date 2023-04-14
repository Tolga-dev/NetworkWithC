#include <bits/stdc++.h>

using namespace std;

template<typename T> concept Hash = requires(T a) { { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>; };
/// is base of
template<class T, class U> concept Derived = std::is_base_of<T,U>::value;
/// is integral
template<class T> concept Integral = std::is_integral<T>::value;
template<class T> concept IsSigned = std::is_signed<T>::value;
template<class T> concept UnSigned = !std::is_signed<T>::value;
template<class T> concept SignedIntegral = Integral<T> && IsSigned<T>;
template<class T> concept UnSignedIntegral = Integral<T> && UnSigned<T>;

/// implementation
template<Hash T> auto f(T t) { return t; }
template<typename T> requires SignedIntegral<T>
auto f(T t) { return t; }

/// string c++11 14
template<typename T> std::enable_if_t<std::is_convertible_v<T,std::string>, std::string> str(T t) { return t; }
template<typename T> std::enable_if_t<!std::is_convertible_v<T,std::string>, std::string> str(T t) { return std::to_string(t); }

/// comparing numbers c++11 14
template<class T> concept is_floating_u = is_floating_point<T>::value;
template<class T> concept if_not_floating_u = !is_floating_point<T>::value;
template<class T> T abs_u(T arg) { return arg < 0 ? -arg : arg;}
template<class T> enable_if_t<is_floating_u<T>,bool> CloseNumbers(T a, T b) { return abs_u(a - b) < static_cast<T>(0.0000001); }
template<class T> enable_if_t<if_not_floating_u<T>,bool> CloseNumbers(T a, T b) { return a == b; }

/// comparing number c++ 17
template <class T> constexpr auto precision_threshold = T(0.000001);
template<class T>
constexpr bool CloseNumbers_v(T a, T b){  if constexpr(is_floating_u<T>) return abs_u(a - b) < precision_threshold<T>; else return a == b;}

/// COMPARING NUMBER C++ 20
bool CloseNumber_Uv3(std::floating_point auto a , std::floating_point auto b) { return abs_u(a - b) < precision_threshold<std::common_type_t<decltype(a), decltype(b)>>; }
bool CloseNumber_Uv3(std::integral auto a, std::integral auto b) { return a == b; }

/// COMPARING NUMBER alternative
template<std::floating_point T>
constexpr bool CLoseNumber_Uv4(T a, T b) { return abs_u(a - b) < precision_threshold<T>; }
constexpr bool CLoseNumber_Uv4(std::integral auto a, std::integral auto b) { return a == b; }

///COMPARING NUMBER alternative
template<typename T> requires std::is_floating_point_v<T>
constexpr bool Close_Number_Uv5(T a, T b) { return abs_u(a - b) < precision_threshold<T>; }
constexpr bool Close_Number_Uv5(std::integral auto a, std::integral auto b) { return a == b; }

/// computing average
template <typename T> requires std::is_integral_v<T> || std::is_floating_point_v<T>
constexpr double Average(std::vector<T> const &ints)
{
//    return std::same_as<decltype(std::accumulate(ints.begin(),ints.end(), 0.0)), double>;
    return ( std::accumulate(ints.begin(),ints.end(), 0.0) / static_cast<double>(ints.size()) ) ;
}
/// computing average concept
template <typename T> concept numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

template<typename T> requires numeric<T>
constexpr double Average1(std::vector<T> const &ints)
{
    return ( std::accumulate(ints.begin(),ints.end(), 0.0) / static_cast<double>(ints.size()) ) ;
}

/// c++ 14 computing
template<typename T>
enable_if<numeric<T>,double> Average(std::vector<T> const &ints)
{
    return ( std::accumulate(ints.begin(),ints.end(), 0.0) / static_cast<double>(ints.size()) ) ;
}

/// Concepts Provider
namespace Detail
{
    template<class T, class U> concept ct_same_provider = std::is_same_v<T,U>; // SINCE C++20
    template<typename T, typename ... U> concept ct_same_provider_alternative = (std::same_as<T,U> || ...);
    template<typename T, T v> concept ct_integral_constant_provider = std::integral_constant<T,v>::type;
    template<typename T> struct ct_is_integral_provide : std::bool_constant<requires (T t,  T* p, void(*f)(T))
    { reinterpret_cast<T>(t); f(0); p + t; }> {};


}
/// Concepts
namespace c_ud
{
    template<class T, class U> concept ct_same = Detail::ct_same_provider<T,U> && Detail::ct_same_provider<U,T>;
    template<typename T> concept ct_is_printable =  std::integral<T> || std::floating_point<T> ||
                                                    Detail::ct_same_provider_alternative<std::remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>,char,wchar_t>;
    template<typename T> concept integral = Detail::ct_is_integral_provide<T>::value;
    template<typename T> concept ct_signed_integral = integral<T> && std::is_signed_v<T>;
    template<typename T> concept ct_unsigned_integral = integral<T> && !std::is_signed_v<T>;
    template<typename T> concept ct_floating = std::is_floating_point_v<T>;

}
/// Functions
namespace f_ud
{

    template<class T, class U> auto constexpr is_same_u() { return c_ud::ct_same<T,U>; }
    template<typename T, T v> auto integral_constant() { return v; }
    void print(c_ud::ct_is_printable auto const ... args) { (std::wcout<< ... << args) << '\n'; }

template<typename T>  requires c_ud::ct_floating<T> constexpr auto f_is_float(T x)
{
    return true;
}

}

class A{};
class B : public A {};
class D : private A{};

struct Default
{
    int foo(){return 0;};

};

struct NonDefault
{
    NonDefault() = delete;
    int foo() {return 0;};
};

int main()
{

    static_assert(f_ud::f_is_float(3.1));

    static_assert(!c_ud::ct_unsigned_integral<float>);
    static_assert(c_ud::ct_unsigned_integral<bool>);
    static_assert(!c_ud::ct_unsigned_integral<int>);

    static_assert(!c_ud::ct_signed_integral<float>);
    static_assert(!c_ud::ct_signed_integral<bool>);
    static_assert(c_ud::ct_signed_integral<int>);

    static_assert(!Detail::ct_is_integral_provide<float>::value);
    static_assert(!c_ud::integral<float>);
    static_assert(Detail::ct_is_integral_provide<bool>::value);
    static_assert(c_ud::integral<bool>);
    static_assert(Detail::ct_is_integral_provide<char>::value);
    static_assert(c_ud::integral<char>);



    decltype(std::declval<NonDefault>().foo()) n1 ;
//    decltype(NonDefault().foo()) n1 ;
    decltype(Default().foo()) n2;


    std::integral_constant<int , 2> t;
    std::integral_constant<int , 2> fx;
    static_assert(t == fx);


    static_assert(f_ud::is_same_u<decltype(f_ud::integral_constant<int,0>()) , decltype(f_ud::integral_constant<int,6>())>());


    static_assert(std::derived_from<B,B>);
    static_assert(std::derived_from<B,A>);
    static_assert(!std::derived_from<D,A>);
    static_assert(std::is_base_of_v<A,D>);


    f_ud::print("Example: ", 3.14, " : ", 42, " : [", 'a', '-', "Z]");
    f_ud::is_same_u<int,int>(); // 1

    static_assert(std::is_same_v<std::remove_cvref_t<int&>, int>);
    static_assert(std::is_same_v<std::remove_pointer<int*>::type, int>);
    static_assert(std::is_same_v<int,int>);
    static_assert(std::is_same_v<int,std::remove_pointer<int*>::type>);
    static_assert(std::is_same_v<int,std::remove_pointer<int* const>::type>);
    static_assert(std::is_same_v<int,std::remove_pointer<int* volatile>::type>);


    std::vector ints { 1, 2, 3, 4, 5};
    cout << Average(ints) << endl;


    cout << Close_Number_Uv5(0.00001f,0.0001f) << endl;
    cout << Close_Number_Uv5(1,1) << endl;

    cout << CLoseNumber_Uv4(0.00001f,0.0001f) << endl;
    cout << CLoseNumber_Uv4(1,1) << endl;

    cout << CloseNumber_Uv3(0.00001f,0.0001f) << endl;
    cout << CloseNumber_Uv3(1,1) << endl;

    cout << CloseNumbers_v(0.00001f,0.0001f) << endl;
    cout << CloseNumbers_v(1,1) << endl;

    cout << CloseNumbers(0.00001f,0.0001f) << endl;

    std::cout << str("hello") << '\n';
    std::cout << str(std::string{"hi!"}) << '\n';
    std::cout << str(42) << '\n';
    std::cout << str(42.2) << '\n';
    std::cout << str(true) << '\n';

    static_assert(Derived<A,B>);
    static_assert(Derived<A,A>);
    f(12.11);

}