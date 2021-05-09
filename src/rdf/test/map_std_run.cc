/** @file "/owlcpp/lib/rdf/test/map_std_run.cpp"
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <owlcpp/rdf/map_ns.hpp>
#include <owlcpp/terms/detail/max_standard_id.hpp>

#include <owlcpp/rdf/map_std.hpp>
#include <owlcpp/rdf/nodes_std.hpp>
#include <owlcpp/rdf/node_iri.hpp>
#include <owlcpp/terms/node_tags_system.hpp>
#include <owlcpp/terms/node_tags_owl.hpp>

using owlcpp::Map_std;
using owlcpp::Node_iri;
using owlcpp::Ns_id;
using owlcpp::Node_id;
using owlcpp::Nodes_none;
using owlcpp::Nodes_owl;
using owlcpp::Rdf_err;


template<class Tag> Node_iri make_iri(Tag const&) {
   return Node_iri(Tag::ns_type::id(), Tag::fragment());
}

namespace t = owlcpp::terms;

SCENARIO("Map std test") {

   GIVEN("I have a map std") {

      Map_std const& nms0 {Map_std::get(Nodes_none())};
      Map_std const& nms1 {Map_std::get(Nodes_owl())};
      Map_std const& nms2 {Map_std::get(Nodes_owl())};
      
      THEN("The instances should be different") {
         
         REQUIRE_FALSE(&nms0 == &nms1);
         REQUIRE(&nms1 == &nms2);
      }
   }
}

SCENARIO("Misc tests") {
   
   GIVEN("I have a map std") {
      
      Map_std const& nms {Map_std::get(Nodes_owl())};
      
      THEN("It should satisfy the requirements") {
         
         REQUIRE_THROWS_AS(nms.at(Node_id(3000)), Rdf_err);
         REQUIRE_THROWS_AS(nms.at(Node_id(3)), Rdf_err);
         REQUIRE_NOTHROW(nms.at(t::empty_::id()));
         REQUIRE_NOTHROW(nms.at(t::xsd_ENTITY::id()));
         REQUIRE_NOTHROW(nms.at(t::xsd_positiveInteger::id()));
      
         REQUIRE_NOTHROW(nms.find(make_iri(t::empty_())));
         REQUIRE_NOTHROW(nms.find(make_iri(t::owl_Class())));
         REQUIRE_NOTHROW(nms.find(make_iri(t::owl_targetValue())));
         REQUIRE_NOTHROW(nms.find(make_iri(t::rdfs_Datatype())));
         REQUIRE_NOTHROW(nms.find(make_iri(t::rdf_type())));
         REQUIRE_NOTHROW(nms.find(make_iri(t::xsd_dateTime())));
      
         REQUIRE(
                  *nms.find(make_iri(t::empty_())) ==
                  t::empty_::id()
         );
      
         REQUIRE(
                  *nms.find(make_iri(t::owl_Class())) ==
                  t::owl_Class::id()
         );
      
         REQUIRE(
                  *nms.find(make_iri(t::owl_targetValue())) ==
                  t::owl_targetValue::id()
         );
      
         REQUIRE(
                  *nms.find(make_iri(t::rdfs_Datatype())) ==
                  t::rdfs_Datatype::id()
         );
      
         REQUIRE(
                  *nms.find(make_iri(t::rdf_type())) ==
                  t::rdf_type::id()
         );
      
         REQUIRE(
                  *nms.find(make_iri(t::xsd_dateTime())) ==
                  t::xsd_dateTime::id()
         );
      
         REQUIRE(
                  *nms.find(make_iri(t::xsd_positiveInteger())) ==
                  t::xsd_positiveInteger::id()
         );
      }
   }
}

