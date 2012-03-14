/** @file "/owlcpp/lib/rdf/test/query_node_run.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define BOOST_TEST_MODULE query_node_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "owlcpp/rdf/query_node.hpp"
#include "owlcpp/terms/node_tags_owl.hpp"

namespace owlcpp{ namespace test{
using namespace owlcpp::terms;

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Triple_store ts;
   const Node_id nid1 = ts.insert_lit_node("1", iri(T_xsd_boolean()));
   BOOST_CHECK( value<bool>(nid1, ts) );

   const Node_id nid2 = ts.insert_lit_node("true", iri(T_xsd_boolean()));
   BOOST_CHECK( value<bool>(nid2, ts) );

   const Node_id nid3 = ts.insert_lit_node("TrUe", iri(T_xsd_boolean()));
   BOOST_CHECK_THROW( value<bool>(nid3, ts), Rdf_err );

   const Node_id nid4 = ts.insert_lit_node("10e300", iri(T_xsd_double()));
   BOOST_CHECK_THROW( value<bool>(nid4, ts), Rdf_err );
   BOOST_CHECK_THROW( value<float>(nid4, ts), Rdf_err );
   BOOST_CHECK( value<double>(nid4, ts) == 10e300 );

   const Node_id nid5 = ts.insert_lit_node("255", iri(T_xsd_double()));
   BOOST_CHECK_THROW( value<bool>(nid5, ts), Rdf_err );
   BOOST_CHECK_THROW( value<char>(nid5, ts), Rdf_err );
   BOOST_CHECK( value<double>(nid5, ts) == 255 );
   BOOST_CHECK( value<unsigned char>(nid5, ts) == 255 );

   const Node_id nid6 = ts.insert_lit_node("-10", iri(T_xsd_double()));
   BOOST_CHECK_THROW( value<unsigned>(nid6, ts), Rdf_err );
   BOOST_CHECK( value<int>(nid6, ts) == -10 );
}

}//namespace test
}//namespace owlcpp
