/** @file "/owl_cpp/include/owl_cpp/parse_to_triple_store.hpp" 
part of owl_cpp project.
Distributed under GNU Lesser General Public License; see doc/license.txt.
@date 2010 @author Mikhail K Levin
*******************************************************************************/
#ifndef PARSE_TO_TRIPLE_STORE_HPP_
#define PARSE_TO_TRIPLE_STORE_HPP_
#include <iosfwd>
#include <string>
#include "boost/tuple/tuple.hpp"
namespace b = boost;
#include "owl_cpp/exception.hpp"
#include "owl_cpp/catalog.hpp"

namespace owl_cpp{
class Triple_store;

struct Parse_err : public base_exception {};

/** @brief Populate triple store from a stream
@details parsing is done with
Raptor RDF Syntax Library <http://librdf.org/raptor/>
*******************************************************************************/
void load(
      std::istream& stream,
      Triple_store& store
);

/** @brief Populate triple store from a file
@details parsing is done with
Raptor RDF Syntax Library <http://librdf.org/raptor/>
*******************************************************************************/
void load(
      const std::string& file, /**< path to OWL file */
      Triple_store& store /**< store parsed ontologies */
);

/**
@param file path to ontology file
@return ontology IRI, ontology version
*******************************************************************************/
b::tuple<std::string,std::string> ontology_id(const std::string& file);


/** @brief map OWL ontologies present at the path to their IRIs
@param cat map from ontology IRI to OWL file path
@param path if file, read as ontology and determine IRI;
if directory, read all *.owl files
*******************************************************************************/
void find_ontologies(
      Catalog& cat,
      const std::string& path
);

namespace detail{
/** If not already loaded, increment n, load ontology with IRI iri,
recurse for each imported ontology
*******************************************************************************/
void load_iri(
      const std::string& iri, /**< ontology IRI */
      Triple_store& store, /**< store parsed ontologies */
      const Catalog& cat /**< path for each ontology IRI */
);
}//namespace detail

/**
*******************************************************************************/
inline void load(
      const std::string& file, /**< path to OWL file */
      Triple_store& store, /**< store parsed ontologies */
      const Catalog& cat /**< path for each ontology IRI */
) {
   const b::tuple<std::string,std::string> ts = ontology_id(file);
   if( ts.get<1>().empty() ) detail::load_iri(ts.get<0>(), store, cat);
   else detail::load_iri(ts.get<1>(), store, cat);
}

}//namespace owl_cpp

#endif /* PARSE_TO_TRIPLE_STORE_HPP_ */
