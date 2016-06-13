//  (C) Copyright Edward Diener 2016.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CXXD_DETAIL_UNORDERED_MAP_HPP)
#define CXXD_DETAIL_UNORDERED_MAP_HPP

#if CXXD_HAS_STD_UNORDERED_MAP

#define CXXD_UNORDERED_MAP_NS std
#include <unordered_map>
namespace cxxd_unordered_map_ns = std ;

#else

#define CXXD_UNORDERED_MAP_NS boost
#include <boost/unordered_map.hpp>
namespace cxxd_unordered_map_ns = boost ;

#endif

#endif // !defined(CXXD_DETAIL_UNORDERED_MAP_HPP)