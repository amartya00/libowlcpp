/** @file "/owlcpp/lib/rdf/test/map_id_object_run.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <owlcpp/rdf/detail/map_id_object.hpp>
#include <owlcpp/node_id.hpp>
#include <owlcpp/ns_id.hpp>
#include <owlcpp/rdf/node_iri.hpp>
#include <owlcpp/rdf/print_node.hpp>

namespace d = owlcpp::detail;

using owlcpp::Ns_id;
using owlcpp::Node_id;
using owlcpp::Node_iri;
using owlcpp::Rdf_err;

SCENARIO("Map doc object test") {

    const Ns_id nsid1(42);
    const Ns_id nsid2(43);
    const Node_id nid0(13);
    const Node_iri n1(nsid1, "n1");
    const Node_iri n2(nsid1, "n2");
    const Node_iri n3(nsid1, "n3");

    GIVEN("I have a node ID object") {

        d::Map_id_object<Node_iri, Node_id> mio1 {nid0};

        WHEN("I try to find something in the empty map id object") {
            
            THEN("I should find nothing") {
                
                REQUIRE_FALSE(mio1.find(nid0));
            }
        }

        WHEN("I try to access something in the empty map id object") {
            
            THEN("I should get an error") {
                
                REQUIRE_THROWS_AS(mio1.at(nid0), Rdf_err);
            }
        }

        WHEN("I insert a node") {
            
            const Node_id nid1 = mio1.insert(n1);
            
            THEN("I should be able tp search for it") {
                
                REQUIRE(mio1.find(nid1));
                REQUIRE(n1 == *mio1.find(nid1));
                REQUIRE(mio1[nid1] == n1);
                REQUIRE(mio1.at(nid1) == n1);
                REQUIRE(nid1 == mio1.insert(n1));
                
                AND_WHEN("I insert another node") {
                    
                    THEN("I should be able to do so without errors") {
                        
                        const Node_id nid2 = mio1.insert(n2);
                        
                        AND_WHEN("I create another map id object from the current one (assignment operatoor)") {
                            d::Map_id_object<Node_iri, Node_id> mio2(Node_id(0));
                            mio2 = mio1;
                            
                            THEN("I should be able to work with the second one as is") {
                                
                                REQUIRE_THROWS_AS(mio2.insert(Node_id(42), n1), Rdf_err);
                                REQUIRE_THROWS_AS(mio2.insert(nid2, n3), Rdf_err);
                            }
                            
                            AND_WHEN("I do a redundant insert") {
                            
                                THEN("The resulting no-op should succeed without errors") {
                                    
                                    REQUIRE_NOTHROW(mio2.insert(nid2, n2));
                                }
                            }
                            
                            AND_WHEN("I attempt to re-insert in an existing ID") {
                                
                                THEN("The operation should return an error") {
                                    
                                    const Node_id nid01(1);
                                    REQUIRE_THROWS_AS(mio2.insert(nid01, n3), Rdf_err);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}





/**@test
*******************************************************************************/
/*
BOOST_AUTO_TEST_CASE( case01 ) {
   d::Map_id_object<Node_iri, Node_id> mio1(nid0);
   BOOST_CHECK( ! mio1.find(nid0) );
   -----------------------------------
   BOOST_CHECK_THROW(mio1.at(nid0), Rdf_err);
   ============================================
   const Node_id nid1 = mio1.insert(n1);
   BOOST_REQUIRE( mio1.find(nid1) );
   
   BOOST_CHECK_EQUAL(n1, *mio1.find(nid1));
   BOOST_CHECK_EQUAL(mio1[nid1], n1);
   BOOST_CHECK_EQUAL(mio1.at(nid1), n1);
   BOOST_CHECK_EQUAL(nid1, mio1.insert(n1));
------------------------------------
   const Node_id nid2 = mio1.insert(n2);

   d::Map_id_object<Node_iri, Node_id> mio2(Node_id(0));
   mio2 = mio1;

   //insert existing node with new ID
   BOOST_CHECK_THROW(
            mio2.insert(Node_id(42), n1),
            Rdf_err
   );

   //insert new node with existing ID
   BOOST_CHECK_THROW(
            mio2.insert(nid2, n3),
            Rdf_err
   );
   -----------------------------

   //insert existing node with its current ID (NOP)
   BOOST_CHECK_NO_THROW( mio2.insert(nid2, n2); );

   //insert new node with ID below id0
   const Node_id nid01(1);
   BOOST_CHECK_THROW(
            mio2.insert(nid01, n3),
            Rdf_err
   );
}
*/
