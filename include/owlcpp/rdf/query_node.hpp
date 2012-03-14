/** @file "/owlcpp/include/owlcpp/rdf/query_node.hpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#ifndef QUERY_NODE_HPP_
#define QUERY_NODE_HPP_
#include "boost/lexical_cast.hpp"
#include "boost/numeric/conversion/cast.hpp"
#include "boost/type_traits/is_integral.hpp"
#include "boost/type_traits/is_unsigned.hpp"
#include "boost/type_traits/is_floating_point.hpp"
#include "owlcpp/rdf/triple_store.hpp"
#include "owlcpp/rdf/exception.hpp"
#include "owlcpp/terms/iri_tags.hpp"

namespace owlcpp{ namespace terms{

/**@brief
*******************************************************************************/
template<class T> inline std::string iri(T const&) {
   return T::ns_type::iri() + "#" + T::name();
}

}//namespace terms

/**@brief
*******************************************************************************/
std::string iri(const Node_id nid, Triple_store const& ts);

namespace detail{

template<class T> struct Converter {
   static T convert(std::string const& str) {
      if( boost::is_integral<T>::value ) {
         if( boost::is_unsigned<T>::value ) {
            return boost::numeric_cast<T>(boost::lexical_cast<unsigned long>(str));
         } else {
            return boost::numeric_cast<T>(boost::lexical_cast<long>(str));
         }
      }
      if( boost::is_floating_point<T>::value ) {
         return boost::numeric_cast<T>(boost::lexical_cast<double>(str));
      }
      return boost::lexical_cast<T>(str);
   }
};

template<> struct Converter<bool> {
   static bool convert(std::string const& str) {
      if( str == "true" ) return true;
      if( str == "false" ) return false;
      return boost::lexical_cast<bool>(str);
   }
};

}//namespace detail

/**@brief
*******************************************************************************/
template<class T> inline T value(const Node_id nid, Triple_store const& ts) {
   Node const& node = ts[nid];
   if( is_empty(node.ns_id()) ) {
      //todo: check declared type
      try {
         return detail::Converter<T>::convert(node.value_str());
      } catch(...) {
         const char* t = typeid(T).name();
         BOOST_THROW_EXCEPTION(
                  Rdf_err()
                  << Rdf_err::msg_t("conversion error")
                  << Rdf_err::str1_t(node.value_str())
                  << Rdf_err::str2_t(std::string(t))
                  << Rdf_err::nested_t(boost::current_exception())
         );
      }
   }
   BOOST_THROW_EXCEPTION(
            Rdf_err()
            << Rdf_err::msg_t("non-literal node has no value")
   );
}

}//namespace owlcpp
#endif /* QUERY_NODE_HPP_ */
