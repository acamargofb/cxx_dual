
//  (C) Copyright Edward Diener 2016
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <string>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <boost/static_assert.hpp>

#define CXXD_TEST_NOT(expr) BOOST_TEST(!(expr))

#include <boost/cxx_dual/type_traits.hpp>

class A {};

struct B {
    int m;
};
 
struct C {
    virtual ~C();
};

class X {};
class Y : public X {};
class Z {};

enum E {};
 
template <class T>
T f(T i)
{
    BOOST_STATIC_ASSERT_MSG(cxxd_type_traits_ns::is_integral<T>::value, "Integer required.");
    return i;
}

struct foo
{
    int m() { return 1; }
    int m() const { return 0; }
};
 
template <class T>
int call_m()
{
    return (T().m());
}

template <typename T, typename U>
struct decay_equiv : 
    cxxd_type_traits_ns::is_same<typename cxxd_type_traits_ns::decay<T>::type, U>::type 
{};

int main()
    {
  
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_void<void>));
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_void<int>));
    
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_integral<A>));
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_integral<float>));
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_integral<int>));
    f(123);
    
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_floating_point<A>));
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_floating_point<float>));
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_floating_point<int>));
    
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_array<A>));
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_array<A[]>));
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_array<A[3]>));
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_array<float>));
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_array<int>));
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_array<int[]>));
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_array<int[3]>));
    
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_enum<A>));
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_enum<E>));
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_enum<int>));
    
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_compound<A>));
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_compound<int>));
                     
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::is_empty<A>));
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_empty<B>));
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::is_empty<C>));
    
    BOOST_TEST_TRAIT_FALSE((cxxd_type_traits_ns::has_virtual_destructor<std::string>));
    BOOST_TEST_TRAIT_TRUE((cxxd_type_traits_ns::has_virtual_destructor<std::runtime_error>));
              
    BOOST_TEST_EQ(cxxd_type_traits_ns::extent<int[3]>::value,static_cast<unsigned int>(3));
    BOOST_TEST_EQ((cxxd_type_traits_ns::extent<int[3][4], 0>::value),static_cast<unsigned int>(3));
    BOOST_TEST_EQ((cxxd_type_traits_ns::extent<int[3][4], 1>::value),static_cast<unsigned int>(4));
    BOOST_TEST_EQ((cxxd_type_traits_ns::extent<int[3][4], 2>::value),static_cast<unsigned int>(0));
    BOOST_TEST_EQ(cxxd_type_traits_ns::extent<int[]>::value,static_cast<unsigned int>(0));
 
    const int ext = cxxd_type_traits_ns::extent<int[9]>();
    
    BOOST_TEST_EQ(ext,9);
    
    bool y2x = cxxd_type_traits_ns::is_convertible<Y*, X*>::value;
    bool x2y = cxxd_type_traits_ns::is_convertible<X*, Y*>::value;
    bool y2z = cxxd_type_traits_ns::is_convertible<Y*, Z*>::value;
 
    BOOST_TEST(y2x);
    CXXD_TEST_NOT(x2y);
    CXXD_TEST_NOT(y2z);
    
    BOOST_TEST_EQ(call_m<foo>(),1);
    BOOST_TEST_EQ(call_m<cxxd_type_traits_ns::add_const<foo>::type>(),0);
    
    BOOST_TEST((decay_equiv<int, int>::value));
    BOOST_TEST((decay_equiv<int&, int>::value));
    BOOST_TEST((decay_equiv<const int&, int>::value));
    BOOST_TEST((decay_equiv<int[2], int*>::value));
    BOOST_TEST((decay_equiv<int(int), int(*)(int)>::value));
  
    return boost::report_errors();
    }
