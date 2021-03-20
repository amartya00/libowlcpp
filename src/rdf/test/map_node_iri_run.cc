/** @file "/owlcpp/lib/rdf/test/map_node_iri_run.cpp"
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <owlcpp/rdf/map_node_iri.hpp>
#include <owlcpp/terms/node_tags_system.hpp>
#include <owlcpp/terms/node_tags_owl.hpp>
#include <owlcpp/terms/detail/max_standard_id.hpp>
#include <owlcpp/rdf/print_node.hpp>

namespace t = owlcpp::terms;

using owlcpp::Ns_id;
using owlcpp::Node_id;
using owlcpp::Node_iri;
using owlcpp::Map_node_iri;

SCENARIO("Map node IRI test") {

    const Ns_id nsid2(42);
    const Ns_id nsid3(43);
    const Node_id nid0(13);
    const Node_id nid1(42);
    const Node_iri n2(nsid2, "blah");

    GIVEN("I have a map node IRI") {
        
        Map_node_iri mni1 {nid0};
        
        WHEN("I try to find something in this empry object") {
            
            THEN("It should return nothing") {
                
                REQUIRE_FALSE(mni1.find(nid1));
            }
        }
        
        WHEN("I insert a node into the instance") {
            
            const Node_id nid2 {mni1.insert(n2)};
            
            AND_WHEN("I search for it") {
                
                THEN("I shoule find it") {
                    
                    REQUIRE(mni1.find(nid2));
                    REQUIRE(mni1[nid2] == n2);
                }
            }
            
            AND_WHEN("I try to insert other nodes with same IRI") {
                
                const Node_id nid2a {mni1.insert_iri(nsid2, "blah")};
                const Node_id nid3 {mni1.insert_iri(nsid3, "blah")};

                THEN("The returned ID should be the same") {
                    
                    REQUIRE(mni1.find(nid2a));
                    REQUIRE(nid2a == nid2);

                    REQUIRE( mni1.find(nid3) );
                    REQUIRE_FALSE(nid2 == nid3);
                }
                
                AND_WHEN("I clone the IRI") {
                    
                    Map_node_iri mni2;
                    mni2 = mni1;
                    
                    THEN("They should have the same size") {
                        
                        REQUIRE(mni1.size() == mni2.size());
                    }
                    
                    AND_WHEN("I remove some items from the original (to test data independence)") {
                        
                        mni1.remove(nid2);
                        
                        THEN("The new one should not be effected") {

                            REQUIRE_FALSE(mni1.find(n2));
                            REQUIRE_FALSE(mni1.find(nid2) );

                            REQUIRE(   mni2.find(n2) );
                            REQUIRE(   mni2.find(nid2) );
                            REQUIRE(mni2[nid2].ns_id() == nsid2);
                            REQUIRE(mni2[nid2] == n2);
                        }

                        AND_WHEN("I try to insert something that should cause the id to get recycled") {
                            
                            const Node_id id4 {mni1.insert_iri(Ns_id(13), "blahblah")};
                            
                            THEN("I ID should get recycled") {
                                
                                REQUIRE( mni1.find(id4) );
                                REQUIRE(nid2 == id4);
                            }
                        }
                    }
                }
            }
        }
    }
}
