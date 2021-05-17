/** @file "/owlcpp/lib/rdf/test/member_iterator_run.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <map>
#include <vector>

#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <owlcpp/detail/member_iterator.hpp>
#include <owlcpp/detail/iterator_member_pair.hpp>
#include <boost/multi_index/detail/hash_index_iterator.hpp>

using owlcpp::Iterator_member_pair;
using owlcpp::Member_iterator;

typedef std::map<int, double> map_t;
typedef Iterator_member_pair<map_t::const_iterator, const double, 2> iter_t;
typedef boost::iterator_range<iter_t> range_t;

SCENARIO("Pair iterator test") {

   GIVEN("I have initialized a map") {

      map_t map {
         {1, 2.5},
         {42, 42}
      };

      THEN("The ranges shoukd be as expected") {

         range_t r1(map.begin(), map.end());
         range_t r2(map.end(), map.end());

         REQUIRE(boost::distance(r1) == 2);
         REQUIRE(boost::distance(r2) == 0);
      }
   }
}

SCENARIO("Test custom struct iter") {

   GIVEN("I have a custom struct") {

      struct A {int a; double b;};
      typedef std::vector<A> vector_t;
      typedef Member_iterator<
               vector_t::const_iterator,
               const double,
               &A::b
               > iter_t;
      typedef boost::iterator_range<iter_t> range_t;

      AND_GIVEN("I have a vector of type A") {

         vector_t v {A(), A()};

         THEN("The ranges should work correctly") {

            range_t r1(v.begin(), v.end());
            range_t r2(v.end(), v.end());

            REQUIRE(boost::distance(r1) == 2);
            REQUIRE(boost::distance(r2) == 0);
         }
      }
   }
}
