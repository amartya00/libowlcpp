/** @file "/owlcpp/lib/rdf/test/map_triple_01_run.cpp"
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <iostream>
#include <owlcpp/rdf/map_triple.hpp>
#include <test_utils.hpp>

namespace mpl = boost::mpl;

using owlcpp::Map_triple;
using owlcpp::Subj_tag;
using owlcpp::Pred_tag;
using owlcpp::Obj_tag;
using owlcpp::Doc_tag;
using owlcpp::test::insert_seq;
using owlcpp::any;
using owlcpp::Node_id;
using owlcpp::test::triple;
using owlcpp::Rdf_err;

const unsigned t[][4] = {
         {0,1,0,0},
         {0,2,0,0},
         {0,3,0,0},
         {1,3,0,0},
         {0,3,1,0},
         {0,3,0,1},
         {0,4,0,0},
};

typedef Map_triple<
            mpl::vector1<
               mpl::vector4<Subj_tag, Pred_tag, Obj_tag, Doc_tag>
            >
   > map_triple;

SCENARIO("Iterator test") {

   GIVEN("I have a map triple") {

      map_triple mt;

      THEN("Its initial size should be 0") {

         REQUIRE(mt.size() == 0U);         
      }

      WHEN("I insert the sample seq") {

         insert_seq(mt, t);

         THEN("The size should increase to 7") {

            REQUIRE(mt.size() == 7U);
            REQUIRE(mt.begin() != mt.end());            
         }
      }
   }   
}


SCENARIO("Test index subject search") {

   GIVEN("I have a map triple") {

      map_triple mt;

      THEN("The initial size should be 0") {

         REQUIRE(mt.size() == 0U);      
      }

      WHEN("I insert some elements") {

         insert_seq(mt, t);

         THEN("The new size should reflect that") {

            REQUIRE(mt.size() == 7U);         
         }

         AND_WHEN("I search for some  on existant elements") {

            auto r1 {mt.find(Node_id(2), Node_id(3), any, any)};

            THEN("It should be not found") {

               REQUIRE_FALSE(r1);            
            }
         }

         AND_WHEN("I do look for something that exists") {

            auto r2 {mt.find(Node_id(0), Node_id(1), any, any)};

            THEN("It should exist") {

               REQUIRE(r2);

               AND_THEN("The distance should be 1") {

                  REQUIRE(boost::distance(r2) == 1);
               }
            }
         }

         AND_WHEN("I search for another element further away") {

            auto r3 {mt.find(any, Node_id(3), any, any)};

            THEN("The distance should be appropriate") {

               REQUIRE(boost::distance(r3) == 4);                           
            }
         }

         AND_WHEN("I try to erase something that ain't there") {

            THEN("I should get an error") {

               REQUIRE_THROWS_AS(mt.erase(triple(0,13,0,1)), Rdf_err);
            }
         }

         AND_WHEN("I do erase something that is there") {

            mt.erase(triple(0,3,0,1));

            THEN("I should be able to so so. The size reflects it.") {

                REQUIRE(mt.size() == 6U);
            }
         }

         AND_WHEN("WHEN I klear the thing") {

            mt.clear();

            THEN("Its size should go back to 0") {

               REQUIRE(mt.size() == 0U);               
            }
         }
      }
   }
}


SCENARIO("Index subject search") {

   GIVEN("I have a map triple") {

      map_triple mt;

      THEN("Its initial size should be 0") {

         REQUIRE(mt.size() == 0U);  
      }

      AND_WHEN("I insert some elements in it") {

         insert_seq(mt, t);

         THEN("The size should reflect it") {

            REQUIRE(mt.size() == 7U);
         }

         AND_WHEN("I search for non existent elements") {

            auto r1 {mt.find(Node_id(2), Node_id(3), any, any)};
   
            THEN("I should get an not-found") {
   
               REQUIRE_FALSE(r1);
            }
         }
   
         AND_WHEN("I search for elements that do exist") {
   
            auto r2 = mt.find(Node_id(0), Node_id(1), any, any);
   
            THEN("I should find them") {
   
               REQUIRE(r2);            
            }
         }
   
         AND_WHEN("I compute distances of nodes") {
   
            auto r2 = mt.find(Node_id(0), Node_id(1), any, any);
            auto r3 = mt.find(any, Node_id(3), any, any);
   
            THEN("I should get the proper distances") {
   
               REQUIRE(boost::distance(r2) == 1);
               REQUIRE(boost::distance(r3) == 4);                       
            }
         }

         AND_WHEN("I try to erase a non-existent element") {

            THEN("I should get an error") {

               REQUIRE_THROWS_AS(mt.erase(triple(0,13,0,1)), Rdf_err);
            }
         }

         AND_WHEN("I try to erase an element that does exist") {

            mt.erase(triple(0,3,0,1));

            THEN("The size should reflect that") {

               REQUIRE(mt.size() == 6U);
            }
         }

         AND_WHEN("I clear the map") {

            mt.clear();

            THEN("Its size should go to 0") {

               REQUIRE(mt.size() == 0U);  
            }
         }
      }
   }
}

SCENARIO("TEst index predicate search") {

   GIVEN("I have a map triple") {

      map_triple mt;

      AND_GIVEN("I inserted elements into it") {

         insert_seq(mt, t);

         WHEN("I try to find an element in it") {

            auto r {mt.find(any, Node_id(3), any, any)};

            THEN("I should be able to do so") {

               REQUIRE(r);
            }

            AND_THEN("I should be able to get the distance") {

               REQUIRE(boost::distance(r) == 4U);
            }
         }
      }
   }
}
