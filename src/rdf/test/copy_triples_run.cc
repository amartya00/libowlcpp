/** @file "/owlcpp/lib/rdf/test/copy_triples_run.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/

#define CATCH_CONFIG_MAIN

#include "test/sample_triples.hpp"
#include "owlcpp/rdf/triple_store.hpp"
#include "owlcpp/rdf/copy_triples.hpp"
#include "test_utils.hpp"

#include <catch2/catch.hpp>

#define CATCH_CONFIG_MAIN

using owlcpp::Triple_store;
using owlcpp::Nodes_none;
using owlcpp::Doc_id;
using owlcpp::test::sample_triples_01;
using owlcpp::test::sample_triples_02;
using owlcpp::test::path1;
using owlcpp::test::path2;
using owlcpp::test::doc1;
using owlcpp::test::doc2;

SCENARIO("Sample testcase.") {
    
    GIVEN("I have some triple stores") {
        
        Triple_store ts1 {Nodes_none()};
        sample_triples_01(ts1);
        Triple_store ts2 {sample_triples_02()};
        
        WHEN("I try to find relevant paths in them") {
            
            THEN("I should get back expected results") {
                
                REQUIRE( ts2.map_doc().find_path(path2) );
                REQUIRE( ts1.map_doc().find_path(path1) );
                REQUIRE( ! ts1.map_doc().find_path(path2) );
                REQUIRE( ! ts2.map_doc().find_path(path1) );
            }
        }

        AND_WHEN("I copy triples between stores") {

            const std::size_t nt1 {ts1.map_triple().size()};
            const std::size_t nt2 {ts2.map_triple().size()};
            copy_triples(ts1, ts2);

            THEN("The sizes should be as expected") {

                REQUIRE(ts2.map_triple().size() == nt1 + nt2);
            }
            
            AND_THEN("The paths should exist as expected") {

                REQUIRE( ts2.map_doc().find_path(path1) );
                REQUIRE( ts2.map_doc().find_path(path2) );
                const Doc_id did1 {ts2.map_doc().find_path(path1).front()};
                const Doc_id did2 {ts2.map_doc().find_path(path2).front()};
                REQUIRE( ts2.at(did1).path == path1 );
                REQUIRE( ts2.at(did2).path == path2 );
                REQUIRE( ts2.at(did1).ontology_iri == *ts2.find_node_iri(doc1) );
                REQUIRE( ts2.at(did2).ontology_iri == *ts2.find_node_iri(doc2) );
            }
        }
        
    }
}
