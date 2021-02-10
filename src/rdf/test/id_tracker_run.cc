/** @file "/owlcpp/lib/rdf/test/id_tracker_run.cpp" 
part of %owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2011
*******************************************************************************/

#define CATCH_CONFIG_MAIN

#include "owlcpp/detail/id_tracker.hpp"
#include "owlcpp/ns_id.hpp"

#include <catch2/catch.hpp>
#include <iostream>

using owlcpp::detail::Id_tracker;
using owlcpp::Ns_id;

SCENARIO("ID tracker test") {
    
    GIVEN("I have an ID tracker") {

        Id_tracker<Ns_id> tracker {Ns_id {12}};
        const Ns_id refId13 {13};
        const Ns_id refId14 {14};
        
        WHEN("I extract more IDs") {

            auto id13 {tracker.get()};
            auto id14 {tracker.get()};

            THEN("The IDs should be sequential") {
                
                REQUIRE(id13 == refId13);
                REQUIRE(id14 == refId14);
            }
        }
        
        AND_WHEN("I push the last 2 IDs and re-get") {

            tracker.get();
            tracker.get();
            
            tracker.push(refId14);
            tracker.push(refId13);
            
            auto id13 {tracker.get()};
            auto id14 {tracker.get()};

            THEN("I should get the same IDs on get again") {

                REQUIRE(id13 == refId13);
                REQUIRE(id14 == refId14);
            }
        }
    }
}

