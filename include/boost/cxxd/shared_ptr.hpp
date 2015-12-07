//  (C) Copyright Edward Diener 2015. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CXXD_SHARED_PTR_ERROR)
	#if (defined(CXXD_SHARED_PTR_USE_BOOST) || defined(CXXD_USE_BOOST)) && (defined(CXXD_SHARED_PTR_USE_STD) || defined(CXXD_USE_STD))
		#define CXXD_SHARED_PTR_ERROR
		#error CXXD: Using C++ standard and using Boost are both defined for shared pointer
	#elif defined(CXXD_HAS_STD_SHARED_PTR) && !defined(CXXD_ALLOW_CHANGE)
        #if CXXD_HAS_STD_SHARED_PTR && (defined(CXXD_SHARED_PTR_USE_BOOST) || defined(CXXD_USE_BOOST))
            #define CXXD_SHARED_PTR_ERROR
            #error CXXD: Previous use of C++ standard shared pointer erroneously overridden
        #elif !CXXD_HAS_STD_SHARED_PTR && (defined(CXXD_SHARED_PTR_USE_STD) || defined(CXXD_USE_STD))
            #define CXXD_SHARED_PTR_ERROR
            #error CXXD: Previous use of Boost shared pointer erroneously overridden
        #endif
    #elif !defined(CXXD_HAS_STD_SHARED_PTR) || defined(CXXD_SHARED_PTR_USE_BOOST) || defined(CXXD_USE_BOOST) || defined(CXXD_SHARED_PTR_USE_STD) || defined(CXXD_USE_STD)
        #include <boost/config.hpp>
        #if defined(BOOST_NO_CXX11_SMART_PTR) || defined(CXXD_SHARED_PTR_USE_BOOST) || defined(CXXD_USE_BOOST)
            #if defined(CXXD_SHARED_PTR_USE_STD) || defined(CXXD_USE_STD)
                #define CXXD_SHARED_PTR_ERROR
                #error CXXD: C++ standard shared pointer is not available
            #else
                #if defined(CXXD_HAS_STD_SHARED_PTR)
                    #undef CXXD_HAS_STD_SHARED_PTR
                    #undef CXXD_SHARED_PTR_NS
                    #undef CXXD_SHARED_PTR_HEADER
                #endif
                #define CXXD_HAS_STD_SHARED_PTR 0
                #define CXXD_SHARED_PTR_NS boost
                #define CXXD_SHARED_PTR_HEADER <boost/shared_ptr.hpp>
            #endif
        #else
            #if defined(CXXD_HAS_STD_SHARED_PTR)
                #undef CXXD_HAS_STD_SHARED_PTR
                #undef CXXD_SHARED_PTR_NS
                #undef CXXD_SHARED_PTR_HEADER
            #endif
            #define CXXD_HAS_STD_SHARED_PTR 1
            #define CXXD_SHARED_PTR_NS std
            #define CXXD_SHARED_PTR_HEADER <memory>
        #endif
    #endif
#endif