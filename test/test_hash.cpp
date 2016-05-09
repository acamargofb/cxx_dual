
//  (C) Copyright Edward Diener 2016
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <iostream>
#include <iomanip>
#include <string>
#include <boost/foreach.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <boost/cxx_dual/hash.hpp>
#include <boost/cxx_dual/unordered_set.hpp>

#include CXXD_HASH_HEADER
#include CXXD_UNORDERED_SET_HEADER
 
struct S {
    std::string first_name;
    std::string last_name;
};
bool operator==(const S& lhs, const S& rhs) {
    return lhs.first_name == rhs.first_name && lhs.last_name == rhs.last_name;
}
 
// custom hash can be a standalone function object:
template <class T> struct MyHash;
template<> struct MyHash<S>
{
    std::size_t operator()(S const& s) const 
    {
        std::size_t h1 = CXXD_HASH_NS::hash<std::string>()(s.first_name);
        std::size_t h2 = CXXD_HASH_NS::hash<std::string>()(s.last_name);
        
    #if CXXD_HAS_STD_HASH

        return h1 ^ (h2 << 1); // or use boost::hash_combine
        
    #else

        std::size_t seed = 0;
        CXXD_HASH_NS::hash_combine(seed,h1);
        CXXD_HASH_NS::hash_combine(seed,h2);
        return seed;

    #endif
        
    }
};
 
// custom specialization of CXXD_HASH_NS::hash can be injected in namespace CXXD_HASH_NS
namespace CXXD_HASH_NS
{
    template<> struct hash<S>
    {
        typedef S argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& s) const
        {
            result_type const h1 ( CXXD_HASH_NS::hash<std::string>()(s.first_name) );
            result_type const h2 ( CXXD_HASH_NS::hash<std::string>()(s.last_name) );
            
        #if CXXD_HAS_STD_HASH

            return h1 ^ (h2 << 1); // or use boost::hash_combine
            
        #else

            std::size_t seed = 0;
            CXXD_HASH_NS::hash_combine(seed,h1);
            CXXD_HASH_NS::hash_combine(seed,h2);
            return seed;

        #endif
            
        }
    };
}

int main()
  {
  
  std::string str = "Meet the new boss...";
  std::size_t str_hash = CXXD_HASH_NS::hash<std::string>()(str);
  std::cout << "hash(" << str << ") = " << str_hash << '\n';
 
  S obj = { "Hubert", "Farnsworth"};
  // using the standalone function object
  std::cout << "hash(" << obj.first_name << ',' 
            << obj.last_name << ") = "
            << MyHash<S>()(obj) << " (using MyHash)\n                           or "
            << CXXD_HASH_NS::hash<S>()(obj) << " (using " << BOOST_STRINGIZE(CXXD_HASH_NS) << "::hash) " << '\n';
 
  // custom hash makes it possible to use custom types in unordered containers
  
#if !defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) 
  
  CXXD_UNORDERED_SET_NS::unordered_set<S> names = {obj, {"Bender", "Rodriguez"}, {"Leela", "Turanga"} };
  
#else

  S obj1 = { "Bender", "Rodriguez"};
  S obj2 = { "Leela", "Turanga"};
  CXXD_UNORDERED_SET_NS::unordered_set<S> names;
  
  names.insert(obj);
  names.insert(obj1);
  names.insert(obj2);
  
#endif
  
#if !defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) && !defined(BOOST_NO_CXX11_RANGE_BASED_FOR)

  for(auto& s: names)
      std::cout << s.first_name << ' ' << s.last_name << '\n';
      
#else

  BOOST_FOREACH(const S & s,names)
      std::cout << s.first_name << ' ' << s.last_name << '\n';
  
#endif
  
  return boost::report_errors();
  }
