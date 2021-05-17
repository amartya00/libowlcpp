/** @file "/owlcpp/lib/rdf/test/map_triple_02_run.cpp"
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

using owlcpp::Node_id;
using owlcpp::Doc_id;
using owlcpp::Doc_tag;
using owlcpp::Map_triple;
using owlcpp::Doc_tag;
using owlcpp::Subj_tag;
using owlcpp::Pred_tag;
using owlcpp::Obj_tag;
using owlcpp::test::insert_seq;
using owlcpp::test::random_triples1;
using owlcpp::any;

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
            mpl::vector4<
               mpl::vector4<Subj_tag, Pred_tag, Obj_tag, Doc_tag>,
               mpl::vector4<Pred_tag, Subj_tag, Obj_tag, Doc_tag>,
               mpl::vector4<Obj_tag, Subj_tag, Pred_tag, Doc_tag>,
               mpl::vector4<Doc_tag, Pred_tag, Subj_tag, Obj_tag>
            >
   > map_triple;

SCENARIO("Test map triple") {

   GIVEN("I have a map triple") {
   
      map_triple tm;
   
      AND_GIVEN("I have inserted a bunch of elements in them") {
   
         insert_seq(tm, t);
   
         WHEN("I search for `any` generic triple") {
   
            auto r1 {tm.find(any, any, any, any)};
   
            THEN("It's distance should equal size") {
   
               REQUIRE(boost::distance(r1) == 7U);
            }
         }
   
         AND_WHEN("I search for a bunch of elements") {
   
            auto r2 {tm.find(Node_id(0), any, any, any)};
            auto r3 {tm.find(Node_id(0), any, Node_id(0), any)};
            auto r4 {tm.find(any, any, any, Doc_id(1))};
            auto r5 {tm.find(Node_id(0), Node_id(2), Node_id(0), Doc_id(0))};
            auto r6 {tm.find(Node_id(0), any, Node_id(2), any)};
            auto r7 {tm.find(any, any, Node_id(0), any)};
            auto r8 {tm. find(Node_id(0), Node_id(3), any, any)};
   
            THEN("I should get back distance / sizes of all of them") {
   
               REQUIRE(r2.size() == 6);
               REQUIRE(r3.size() == 5);
               REQUIRE(r4.size() == 1);
               REQUIRE(r5.size() == 1);
               REQUIRE(r6.size() == 0);
               REQUIRE(r7.size() == 6);
               REQUIRE(r8.size() == 3);
            }
         }
      }
   }
}

SCENARIO("Map triple test 2") {

   GIVEN("I have a map triple") {

      map_triple mt;

      AND_GIVEN("I have populated it with random triples") {

         insert_seq(mt, random_triples1);

         WHEN("I check the size") {

            auto sz {mt.size()};

            THEN("The size should match as expected") {

               REQUIRE(sz == 20U);
            }

            AND_WHEN("I search for a subset of triples") {

               auto r {mt.find(Node_id(6), Node_id(3), any, any)};

               THEN("Its size should match as expected") {

                  REQUIRE(r.size() == 2U);
               }
            }
         }
      }
   }
}
