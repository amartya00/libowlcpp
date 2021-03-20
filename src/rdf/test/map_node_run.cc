/** @file "/owlcpp/lib/rdf/test/map_node_run.cpp"
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <memory>

#include <owlcpp/rdf/map_node.hpp>
#include <owlcpp/terms/node_tags_system.hpp>
#include <owlcpp/terms/node_tags_owl.hpp>

namespace t = owlcpp::terms;

using owlcpp::Map_node;
using owlcpp::Node_id;
using owlcpp::Ns_id;
using owlcpp::Doc_id;
using owlcpp::Node;

SCENARIO("Test map node") {

    GIVEN("I have a map node") {

        Map_node mn1 {};

        WHEN("I search for something in the empty instance") {

            REQUIRE_FALSE(mn1.find(Node_id(42)));
        }

        WHEN("I insert items into the instance") {

            const Node_id id1 {mn1.insert_iri(Ns_id(42), "blah")};
            const Node_id id2 {mn1.insert_blank(42, Doc_id(5))};
            const Node_id id3 {mn1.insert_literal("blah", Node_id(5), "en")};
            
            THEN("They should all be searchable") {
                
                REQUIRE(mn1.find(id1));
                REQUIRE(mn1.find(id2));
                REQUIRE(mn1.find(id3));
            }

            THEN("All the IDs should be unique") {
                
                REQUIRE_FALSE(id1 == id2);
                REQUIRE_FALSE(id1 == id3);
                REQUIRE_FALSE(id2 == id3);
            }

            AND_WHEN("I colone the instance into a new one") {

                Map_node mn2;
                mn2 = mn1;

                THEN("Their sizes should be equal") {

                    REQUIRE(mn1.size() == mn2.size());
                }
            }

            AND_WHEN("I remove something") {
                    
                std::unique_ptr<Node> p1 {mn1.remove(id1)};
                
                THEN("I should not be able to search for it") {

                    REQUIRE_FALSE(mn1.find(*p1));
                }
            }

            AND_WHEN("I insert with a used node ID") {

                const Node_id id4 {mn1.insert_literal("blahblah", Node_id(5), "fr")};

                THEN("The generated ID should be the same as the original node ID") {

                    REQUIRE(mn1.find(id4) );
                    REQUIRE(id1 == id4);
                }
            }
        }
    }
}

SCENARIO("Test ;literal nodes") {

    GIVEN("I have a mao node") {

        Map_node mn1;

        WHEN("I insert 2 literals with the same value") {

            const Node_id id1 {mn1.insert_literal("blah", t::empty_::id())};
            const Node_id id1a {mn1.insert_literal("blah", t::xsd_string::id())};

            THEN("The generated should be equal") {

                REQUIRE(id1 == id1a);
            }
        }
    }
}
