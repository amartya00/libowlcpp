/** @file "/owlcpp/lib/logic/factpp/obj_type.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#include "obj_type.hpp"
#include "boost/foreach.hpp"
#include "boost/assert.hpp"
#include "owlcpp/rdf/query_triples.hpp"
#include "owlcpp/rdf/query_node.hpp"
#include "owlcpp/rdf/print_node.hpp"
#include "node_property_declaration.hpp"
#include "node_type_declaration.hpp"
#include "find_node_declaration.hpp"
#include "Kernel.hpp"

namespace owlcpp{ namespace logic{ namespace factpp{
using namespace owlcpp::terms;

/*
*******************************************************************************/
Ot_thing::generated_t Ot_thing::get(ReasoningKernel& k ) const {
   return k.getExpressionManager()->Top();
}

/*
*******************************************************************************/
Ot_nothing::generated_t Ot_nothing::get(ReasoningKernel& k ) const {
   return k.getExpressionManager()->Bottom();
}

/*
*******************************************************************************/
Ot_declared::Ot_declared(Expression_args const& ea, Triple_store const& ts)
: iri_(to_string(ea.handle, ts))
{}

/*
*******************************************************************************/
Ot_declared::generated_t Ot_declared::get(ReasoningKernel& k ) const {
   return k.getExpressionManager()->Concept(iri_);
}

/*
*******************************************************************************/
Ot_complement::Ot_complement(Expression_args const& ea, Triple_store const& ts)
: ot_(make_expression<Obj_type>(ea.obj1, ts))
{}

/*
*******************************************************************************/
Ot_complement::Ot_complement(const Node_id nid, Triple_store const& ts)
: ot_(make_expression<Obj_type>(nid, ts))
{}

/*
*******************************************************************************/
Ot_complement::generated_t Ot_complement::get(ReasoningKernel& k ) const {
   return k.getExpressionManager()->Not(ot_->get(k));
}

/*
*******************************************************************************/
void Ot_op_restriction::init(
         const Node_id prop,
         const Node_id val,
         Triple_store const& ts
) {
   switch(restr_type_()) {

   case owl_hasValue::index:
      if( ! is_iri(ts[val].ns_id()) ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("non-IRI object node in \"x owl:hasValue y\"")
               << Err::str1_t(to_string(val, ts))
      );
      inst_ = to_string(val, ts);
      break;

   case owl_hasSelf::index:
      try{ if( value<bool>(val, ts) ) break; } catch( Rdf_err const&) {}
      BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("unexpected object in \"x owl:hasSelf \"true\"^^xsd:boolean\"")
               << Err::str1_t(to_string(val, ts))
      );
      /* no break */

   case owl_allValuesFrom::index:
   case owl_someValuesFrom::index:
      check_declaration(val, Node_type::object(), ts);
      ot_ = make_expression<Obj_type>(val, ts);
      break;

   default: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported restriction type")
            << Err::str1_t(to_string(restr_type_, ts))
   );
   /* no break */
   }

   check_declaration(prop, Node_property::object(), ts);
   op_ = make_expression<Obj_prop>(prop, ts);
}

/*
*******************************************************************************/
TDLConceptExpression* Ot_op_restriction::get(ReasoningKernel& k ) const {
   TExpressionManager& em = *k.getExpressionManager();

   switch(restr_type_()) {

   case owl_allValuesFrom::index: return em.Forall(op_->get(k), ot_->get(k));

   case owl_hasValue::index: return em.Value(op_->get(k), em.Individual(inst_));

   case owl_hasSelf::index: return em.SelfReference(op_->get(k));

   case owl_someValuesFrom::index: return em.Exists(op_->get(k), ot_->get(k));

   default: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported restriction type")
            << Err::str1_t(to_string(restr_type_))
   );
   /* no break */
   }
}

/*
*******************************************************************************/
Ot_data_has_value::Ot_data_has_value(
         Expression_args const& ea, Triple_store const& ts
) {
   BOOST_ASSERT(ea.pred2 == owl_hasValue::id());
   try{
      Node_literal const& node = to_literal(ts[ea.obj2]);
      val_str_ = node.value_str();
      dt_ = make_expression<Data_type>(node.datatype(), ts);
   }catch(base_exception &) {
      BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("error in \"x owl:hasValue y\"")
               << Err::str1_t(to_string(ea.obj2, ts))
               << Err::nested_t(boost::current_exception())
      );
   }
   check_declaration(ea.obj1, Node_property::data(), ts);
   dp_ = make_expression<Data_prop>(ea.obj1, ts);
}

/*
*******************************************************************************/
TDLConceptExpression* Ot_data_has_value::get(ReasoningKernel& k ) const {
   BOOST_ASSERT( dt_.get() );
   BOOST_ASSERT( dp_.get() );
   TExpressionManager& em = *k.getExpressionManager();
   Expression<Data_type>::generated_t dt = dt_->get(k);
   const TDLDataValue* val = em.DataValue(val_str_, dt);
   if( ! val ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("data value error")
            << Err::str1_t(val_str_)
            << Err::str2_t(dt_->string())
   );
   return em.Value(dp_->get(k), val);
}
/*
*******************************************************************************/
void Ot_dp_restriction::init(
         const Node_id prop,
         const Node_id val,
         Triple_store const& ts
) {

   switch(restr_type_()) {

   case owl_hasSelf::index: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("invalid data property restriction, owl:hasSelf")
   );
   /* no break */

   case owl_allValuesFrom::index:
   case owl_someValuesFrom::index:
      BOOST_ASSERT( declaration<Node_type>(val, ts).is_data() );
      dr_ = make_expression<Data_range>(val, ts);
      break;

   default: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported restriction type")
            << Err::str1_t(to_string(restr_type_, ts))
   );
   /* no break */
   }
   check_declaration(prop, Node_property::data(), ts);
   dp_ = make_expression<Data_prop>(prop, ts);
}

/*
*******************************************************************************/
TDLConceptExpression* Ot_dp_restriction::get(ReasoningKernel& k ) const {
   BOOST_ASSERT( dr_.get() );
   BOOST_ASSERT( dp_.get() );
   TExpressionManager& em = *k.getExpressionManager();

   switch(restr_type_()) {

   case owl_allValuesFrom::index: return em.Forall(dp_->get(k), dr_->get(k));

   case owl_someValuesFrom::index: return em.Exists(dp_->get(k), dr_->get(k));

   default: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported restriction type")
            << Err::str1_t(to_string(restr_type_))
   );
   /* no break */
   }
}

/*
*******************************************************************************/
Ot_opc_restriction::Ot_opc_restriction(Expression_args const& ea, Triple_store const& ts)
: op_( make_expression<Obj_prop>(ea.obj1, ts) ),
  ot_(
           is_empty(ea.obj2) ?
                    Expression<Obj_type>::ptr_t() :
                    make_expression<Obj_type>(ea.obj2, ts)
  ),
  card_type_(ea.cardinality),
  n_(ea.num)
{
   switch(card_type_()) {
   case owl_cardinality::index:
   case owl_maxCardinality::index:
   case owl_minCardinality::index:
   case owl_maxQualifiedCardinality::index:
   case owl_minQualifiedCardinality::index:
   case owl_qualifiedCardinality::index:
      break;
   default: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported cardinality restriction type")
            << Err::str1_t(to_string(card_type_, ts))
   );
   /* no break */
   }
}

/*
*******************************************************************************/
TDLConceptExpression* Ot_opc_restriction::get(ReasoningKernel& k ) const {
   BOOST_ASSERT( op_.get() );
   TExpressionManager& em = *k.getExpressionManager();
   switch(card_type_()) {
   case owl_cardinality::index:
      return em.Cardinality(n_, op_->get(k), em.Top());

   case owl_maxCardinality::index:
      return em.MaxCardinality(n_, op_->get(k), em.Top());

   case owl_minCardinality::index:
      return em.MinCardinality(n_, op_->get(k), em.Top());

   case owl_maxQualifiedCardinality::index:
      BOOST_ASSERT( ot_.get() );
      return em.MaxCardinality(n_, op_->get(k), ot_->get(k));

   case owl_minQualifiedCardinality::index:
      BOOST_ASSERT( ot_.get() );
      return em.MinCardinality(n_, op_->get(k), ot_->get(k));

   case owl_qualifiedCardinality::index:
      BOOST_ASSERT( ot_.get() );
      return em.Cardinality(n_, op_->get(k), ot_->get(k));

   default: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported cardinality restriction type")
            << Err::str1_t(to_string(card_type_))
   );
   /* no break */
   }
}

/*
*******************************************************************************/
Ot_dpc_restriction::Ot_dpc_restriction(Expression_args const& ea, Triple_store const& ts)
: dp_( make_expression<Data_prop>(ea.obj1, ts) ),
  dt_(
           is_empty(ea.obj2) ?
                    Expression<Data_type>::ptr_t() :
                    make_expression<Data_type>(ea.obj2, ts)
  ),
  card_type_(ea.cardinality),
  n_(ea.num)
{
   switch(card_type_()) {
   case owl_cardinality::index:
   case owl_maxCardinality::index:
   case owl_minCardinality::index:
   case owl_maxQualifiedCardinality::index:
   case owl_minQualifiedCardinality::index:
   case owl_qualifiedCardinality::index:
      break;
   default: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported cardinality restriction type")
            << Err::str1_t(to_string(card_type_, ts))
   );
   /* no break */
   }
}

/*
*******************************************************************************/
TDLConceptExpression* Ot_dpc_restriction::get(ReasoningKernel& k ) const {
   BOOST_ASSERT( dp_.get() );
   TExpressionManager& em = *k.getExpressionManager();
   switch(card_type_()) {
   case owl_cardinality::index:
      return em.Cardinality(n_, dp_->get(k), em.DataTop());

   case owl_maxCardinality::index:
      return em.MaxCardinality(n_, dp_->get(k), em.DataTop());

   case owl_minCardinality::index:
      return em.MinCardinality(n_, dp_->get(k), em.DataTop());

   case owl_maxQualifiedCardinality::index:
      BOOST_ASSERT( dt_.get() );
      return em.MaxCardinality(n_, dp_->get(k), dt_->get(k));

   case owl_minQualifiedCardinality::index:
      BOOST_ASSERT( dt_.get() );
      return em.MinCardinality(n_, dp_->get(k), dt_->get(k));

   case owl_qualifiedCardinality::index:
      BOOST_ASSERT( dt_.get() );
      return em.Cardinality(n_, dp_->get(k), dt_->get(k));

   default: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported cardinality restriction type")
            << Err::str1_t(to_string(card_type_))
   );
   /* no break */
   }
}

/*
*******************************************************************************/
void Ot_type_list::init(const Node_id nid, Triple_store const& ts) {
   switch(type_()) {
   case owl_intersectionOf::index:
   case owl_unionOf::index:
      break;
   default:
      BOOST_THROW_EXCEPTION(
                  Err()
                  << Err::msg_t("unsupported predicate")
                  << Err::str1_t(to_string(type_, ts))
         );
         /* no break */
   }

   const std::vector<Node_id> seq =
            boost::copy_range<std::vector<Node_id> >(rdf_list(nid, ts));

   check_seq_declaration(seq, Node_type::object(), ts);

   BOOST_FOREACH(const Node_id nid, seq) otl_.push_back(make_expression<Obj_type>(nid, ts));
}

/*
*******************************************************************************/
TDLConceptExpression* Ot_type_list::get(ReasoningKernel& k ) const {
   TExpressionManager& em = *k.getExpressionManager();

   switch(type_()) {

   case owl_intersectionOf::index:
      if( otl_.empty() ) return k.getExpressionManager()->Top();
      if( otl_.size() == 1U ) return otl_[0].get(k);
      em.newArgList();
      //BOOST_FOREACH(Expression<Obj_type> const& ote, otl_) em.addArg( ote.get(k) );
      for(std::size_t n = 0; n != otl_.size(); ++n) em.addArg(otl_[n].get(k));
      return em.And();

   case owl_unionOf::index:
      if( otl_.empty() ) return k.getExpressionManager()->Bottom();
      if( otl_.size() == 1U ) return otl_[0].get(k);
      em.newArgList();
      //BOOST_FOREACH(Expression<Obj_type> const& ote, otl_) em.addArg( ote.get(k) );
      for(std::size_t n = 0; n != otl_.size(); ++n) em.addArg(otl_[n].get(k));
      return em.Or();

   default: BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported predicate")
            << Err::str1_t(to_string(type_))
   );
   /* no break */
   }
}

/*
*******************************************************************************/
TDLConceptExpression* Ot_instance_list::get(ReasoningKernel& k ) const {
   TExpressionManager& em = *k.getExpressionManager();
   if( il_.empty() ) return em.Bottom();
   em.newArgList();
   BOOST_FOREACH(std::string const& iri, il_) em.addArg( em.Individual(iri) );
   return em.OneOf();
}

/*
*******************************************************************************/
void Ot_instance_list::make_sequence(const Node_id seq, Triple_store const& ts) {
   BOOST_FOREACH(const Node_id nid, rdf_list(seq, ts)) {
      if( ! is_iri(ts[nid].ns_id()) ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("non-IRI node for instance declaration")
               << Err::str1_t(to_string(nid, ts))
      );
      il_.push_back(to_string(nid, ts));
   }
}

}//namespace factpp
}//namespace logic
}//namespace owlcpp
