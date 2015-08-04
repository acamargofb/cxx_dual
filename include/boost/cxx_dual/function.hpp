//  (C) Copyright Edward Diener 2015. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/* Multiple inclusion must be allowed */

#if !defined(CXXD_FUNCTION_ERROR)
	#if defined(CXXD_HAS_STD_FUNCTION)
		#if CXXD_HAS_STD_FUNCTION && (defined(CXXD_FUNCTION_USE_BOOST) || defined(CXXD_USE_BOOST))
			#define CXXD_FUNCTION_ERROR
			#error CXXD: Previous use of C++ standard function erroneously overridden
		#elif !CXXD_HAS_STD_FUNCTION && (defined(CXXD_FUNCTION_USE_STD) || defined(CXXD_USE_STD))
			#define CXXD_FUNCTION_ERROR
			#error CXXD: Previous use of Boost function erroneously overridden
		#endif
	#elif (defined(CXXD_FUNCTION_USE_BOOST) || defined(CXXD_USE_BOOST)) && (defined(CXXD_FUNCTION_USE_STD) || defined(CXXD_USE_STD))
		#define CXXD_FUNCTION_ERROR
		#error CXXD: Using C++ standard and using Boost are both defined for function
	#else
		#include <boost/config.hpp>
		#if defined(BOOST_NO_CXX11_HDR_FUNCTIONAL) || defined(CXXD_FUNCTION_USE_BOOST) || defined(CXXD_USE_BOOST)
			#if defined(CXXD_FUNCTION_USE_STD) || defined(CXXD_USE_STD)
				#define CXXD_FUNCTION_ERROR
				#error CXXD: C++ standard function is not available
			#else
				#define CXXD_HAS_STD_FUNCTION 0
				#define CXXD_FUNCTION_NS boost
				#define CXXD_FUNCTION_HEADER <boost/function.hpp>
			#endif
		#else
			#define CXXD_HAS_STD_FUNCTION 1
			#define CXXD_FUNCTION_NS std
			#define CXXD_FUNCTION_HEADER <functional>
		#endif
	#endif
#endif
