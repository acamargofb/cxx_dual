
//  (C) Copyright Edward Diener 2016
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <map>
#include <typeinfo>
#include <string>
#include <boost/cxx_dual/shared_ptr.hpp>
#include <boost/cxx_dual/type_index.hpp>
#include <boost/detail/lightweight_test.hpp>

#include CXXD_SHARED_PTR_ONLY_HEADER
#include CXXD_TYPE_INDEX_HEADER
 
struct A {
    virtual ~A() {}
};
 
struct B : A {};
struct C : A {};

int main()
    {
  
    std::map<CXXD_TYPE_INDEX_NS::type_index, std::string> type_names;
 
    type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(int))] = "int";
    type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(double))] = "double";
    type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(A))] = "A";
    type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(B))] = "B";
    type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(C))] = "C";
 
    int i;
    double d;
    A a;
 
    // note that we're storing pointer to type A
    CXXD_SHARED_PTR_NS::shared_ptr<A> b(new B);
    CXXD_SHARED_PTR_NS::shared_ptr<A> c(new C);
    
    BOOST_TEST_EQ(type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(i))],"int");
    BOOST_TEST_EQ(type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(d))],"double");
    BOOST_TEST_EQ(type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(a))],"A");
    BOOST_TEST_EQ(type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(*b))],"B");
    BOOST_TEST_EQ(type_names[CXXD_TYPE_INDEX_NS::type_index(typeid(*c))],"C");
 
    return boost::report_errors();
    }   
