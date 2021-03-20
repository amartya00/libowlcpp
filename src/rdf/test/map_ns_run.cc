/** @file "/owlcpp/lib/rdf/test/map_ns_run.cpp"
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <owlcpp/rdf/map_ns.hpp>
#include <owlcpp/terms/detail/max_standard_id.hpp>

using owlcpp::Map_ns;
using owlcpp::Ns_id;

SCENARIO("Test map ns") {
    
    GIVEN("I have a map ns") {
        
        Map_ns mns1 {Ns_id(5)};
        
        THEN("The initial size should be 0") {
            
            REQUIRE(mns1.size() == 0);
        }
        
        WHEN("I insert a lieral") {
            
            const Ns_id id1 {mns1.insert("i1")};
            
            THEN("I should be able to access the inserted element") {

                REQUIRE(mns1.find("i1"));
                REQUIRE(*mns1.find("i1") == id1);
            }
        }
        
        WHEN("I set a prefix for an inserted element") {
            
            const Ns_id id2 {mns1.insert("i2")};
            mns1.set_prefix(id2, "p2");

            THEN("I should be able to search by prefix") {
                
                REQUIRE(mns1.prefix(id2) == "p2");
                REQUIRE(mns1.find_prefix("p2"));
            }

            AND_WHEN("I set an empty prefix for the same") {
                
                mns1.set_prefix(id2);
                
                THEN("The returned prefix shopuld be empty") {

                    REQUIRE(mns1.prefix(id2) == "");
                }
            }
            
            AND_WHEN("I do another isert with the same literal") {
                
                
                THEN("The returned ID shoule be the same") {

                    REQUIRE(mns1.insert("i2") == id2);
                }
            }

            AND_WHEN("I create another instance by cloning  this one") {
                
                Map_ns mns2 {mns1};
                
                THEN("Their sizes shoule be equal") {
                    
                    REQUIRE(mns1.size() == mns2.size());
                }
                
                AND_WHEN("I remove id 2 from the first map") {

                    mns1.remove(id2);

                    THEN("I shoule be unable to find them in the first map") {
                        
                        REQUIRE_FALSE(mns1.find_prefix("p2"));
                        REQUIRE_FALSE(mns1.find(id2));
                    }

                    THEN("I should still find them in the second map") {
                        
                        REQUIRE(mns2.find_prefix("p2"));
                        REQUIRE(mns2.find(id2) );
                        REQUIRE(mns2[id2] == "i2");
                        REQUIRE(mns2.prefix(id2) == "p2");
                    }
                }
            }
            
            AND_WHEN("I do some more inserts and deletes") {
                
                const auto id10 {mns1.insert("i10")};
                const auto id12 {mns1.insert("id12")};

                mns1.remove(id10);
                mns1.remove(id12);
                
                AND_WHEN("I do another insert") {
                    
                    const auto id13 {mns1.insert("i13")};
                    
                    THEN("The ids should be recycled") {
                        
                        REQUIRE((id13 == id2 || id13 == id10 || id13 == id12));
                    }
                }
            }
        }
    }
}
