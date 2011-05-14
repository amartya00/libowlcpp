/** @file "/owl_cpp/include/owl_cpp/lib_info.hpp" 
part of owl_cpp project.
Distributed under GNU Lesser General Public License; see doc/license.txt.
@date 2010 @author Mikhail K Levin
*******************************************************************************/
#ifndef LIB_INFO_HPP_
#define LIB_INFO_HPP_
#include <string>
/**
@mainpage %owl_cpp -- library for working with OWL ontologies
- parsing OWL files into triple store (using Raptor)
- querying triple store
- passing triples to FaCT++ reasoner
- querying reasoner's logic

@namespace owl_cpp
@brief Main namespace of %owl_cpp library

@namespace owl_cpp::terms
@brief Definitions of standard OWL namespaces and terms
@details standard OWL namespace and term IRIs are represented by small tag classes.
Tags store namespace IRI, prefix, and name strings.
Each Tag also has a unique indices as compile-time constants.
Tag classes are generated by preprocessor macros from lists.
Tag type-lists are also generated by macros.

@namespace owl_cpp::test
@brief Namespace for unit-tests

*/



namespace owl_cpp{

/**@brief library name
*******************************************************************************/
const std::string& lib_name();

/**@brief library version
*******************************************************************************/
const std::string& version_str();

/**@brief library build number
*******************************************************************************/
const std::string& build_str();

/**@brief library code revision ID
*******************************************************************************/
const std::string& revision_str();

/**@brief
*******************************************************************************/
const std::string& lib_info_str();

}//namespace owl_cpp

#endif /* LIB_INFO_HPP_ */
