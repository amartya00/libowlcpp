/** @file "/owlcpp/lib/lib_info.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#ifndef OWLCPP_SOURCE
#define OWLCPP_SOURCE
#endif
#include "owlcpp/lib_info.hpp"
#include "boost/preprocessor/stringize.hpp"

#ifndef OWLCPP_NAME
#define OWLCPP_NAME owlcpp
#endif

#ifndef OWLCPP_DESCRIPTION
#define OWLCPP_DESCRIPTION
#endif

#ifndef OWLCPP_VERSION_STR
#define OWLCPP_VERSION_STR v0.0.0-???
#endif

#ifndef OWLCPP_VERSION_1
#define OWLCPP_VERSION_1 0
#endif

#ifndef OWLCPP_VERSION_2
#define OWLCPP_VERSION_2 0
#endif

#ifndef OWLCPP_VERSION_3
#define OWLCPP_VERSION_3 0
#endif

#ifndef OWLCPP_VERSION_EXTRA
#define OWLCPP_VERSION_EXTRA ???
#endif

#ifndef OWLCPP_BUILD
#define OWLCPP_BUILD 0
#endif

namespace owlcpp {

/*
*******************************************************************************/
std::string const& Lib_info::name() {
   static const std::string s = std::string(BOOST_PP_STRINGIZE(OWLCPP_NAME));
   return s;
}

/*
*******************************************************************************/
std::string const& Lib_info::version() {
   static const std::string s = std::string(BOOST_PP_STRINGIZE(OWLCPP_VERSION_STR));
   return s;
}

/*
*******************************************************************************/
std::string const& Lib_info::description() {
   static const std::string s = std::string(BOOST_PP_STRINGIZE(OWLCPP_DESCRIPTION));
   return s;
}

/*
*******************************************************************************/
int Lib_info::version_1() {return OWLCPP_VERSION_1;}

/*
*******************************************************************************/
int Lib_info::version_2() {return OWLCPP_VERSION_2;}

/*
*******************************************************************************/
int Lib_info::version_3() {return OWLCPP_VERSION_3;}

/*
*******************************************************************************/
std::string const& Lib_info::version_e() {
   static const std::string s = std::string(BOOST_PP_STRINGIZE(OWLCPP_VERSION_EXTRA));
   return s;
}

/*
*******************************************************************************/
int Lib_info::build() {return OWLCPP_BUILD;}


}//namespace owlcpp
