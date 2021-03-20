/** @file "/owlcpp/lib/rdf/test/map_doc_run.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/

#define CATCH_CONFIG_MAIN

#include <iterator>
#include <catch2/catch.hpp>

#include <test/sample_triples.hpp>
#include <boost/range/algorithm.hpp>
#include <owlcpp/rdf/map_doc.hpp>

using owlcpp::Node_id;
using owlcpp::Map_doc;
using owlcpp::Doc_id;
using owlcpp::test::path1;

namespace t = owlcpp::terms;

SCENARIO("Map doc test") {

    const std::string path1 = "path1";
    const std::string path2 = "path2";
    const std::string path3 = "path3";
    const std::string path4 = "path4";
    const Node_id nid1(12);
    const Node_id nid2(13);
    const Node_id nid3(42);
    const Node_id nid4(41);

    GIVEN("I have a map doc") {
        Map_doc md;
        
        WHEN("I get the initial size") {
            
            THEN("The initial size should be 0") {
                REQUIRE(md.size() == 0);
            }
        }
        
        WHEN("I insert an empty with an ontology") {
            
            THEN("I should get a map dox error") {
                
                REQUIRE_THROWS_AS(md.insert(t::empty_::id(), path1, nid1), Map_doc::Err);
            }
        }
        
        WHEN("I do some inserts") {
            
            THEN("The sizes should be updated as expected") {
                
                REQUIRE(md.size() == 0U);
                const auto [did1, _] {md.insert(nid3, path1, t::empty_::id())};
                REQUIRE(md.size() == 1U);
                REQUIRE(*md.begin() == did1);
                const auto [did2, res] {md.insert(nid3, path1)};
                REQUIRE_FALSE(res);
                REQUIRE(did2 == did1);
                
                AND_WHEN("I try to insert another with a different IRI but same path") {
                    
                    THEN("I should get an error") {
                        
                        REQUIRE_THROWS_AS(md.insert(nid1, path1, t::empty_::id()),Map_doc::Err);
                    }
                }
            }
        }
        
        WHEN("I attempt to insert items with empty paths") {
            
            THEN("I should be able to do so") {
                
                const auto [did1, res1] {md.insert(nid2)};
                REQUIRE(res1);
                const auto [did2, res2] {md.insert(nid2)};
                REQUIRE_FALSE(res2);
                REQUIRE(did1 == did2);
                const auto [did3, res3] {md.insert(nid1)};
                REQUIRE(res3);
                REQUIRE(did1 != did3);
            }
        }

        WHEN("I insert some items") {

            const auto [did2, _] {md.insert(nid2, path2, nid3)};

            THEN("I should be able to find it by node ID") {

                Map_doc::iri_range ir1 = md.find_iri(nid2);
                REQUIRE(ir1);
                const Doc_id did2a = ir1.front();
                REQUIRE(did2a == did2);
                REQUIRE(nid2 == md[did2a].ontology_iri);

                REQUIRE(md[did2a].version_iri != t::empty_::id());
                REQUIRE(nid3 == md[did2a].version_iri);
            }
            
        }
    }
}


SCENARIO("Map doc search") {
    
    const std::string path1 = "path1";
    const std::string path2 = "path2";
    const std::string path3 = "path3";
    const std::string path4 = "path4";
    const Node_id nid1(12);
    const Node_id nid2(13);
    const Node_id nid3(42);
    const Node_id nid4(41);
    
    GIVEN("I have a map doc") {
        
        Map_doc md;
        
        WHEN("I test the initial state") {
            
            THEN("The begin and end should be the same (empty).") {
                
                REQUIRE(md.begin() == md.end());
            }
        }
        
        WHEN("I do an insert") {
            
            const auto [did1, _] = md.insert(nid1, path1, nid2);
            
            THEN("I shoule be able to iterate over it") {
                
                REQUIRE( *md.begin() == did1 );
            }
            
            THEN("I should be able to search for it") {
                
                REQUIRE(md.find_iri(nid1).front() == did1);
            }
            
            AND_WHEN("I do another insert") {
                
                const auto [did2, _] = md.insert(nid2, path2, nid3);
                
                THEN("I should be able to search for it as well") {

                    REQUIRE(md.find_iri(nid2).front() == did2);
                    REQUIRE(boost::distance(md.find_iri(nid1)) == 1);
                    REQUIRE_FALSE( md.find_iri(nid4) );
                }
            }
        }
    }
}
