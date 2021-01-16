/** @file "/owlcpp/lib/logic/node_property_declaration.hpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#ifndef NODE_PROPERTY_DECLARATION_HPP_
#define NODE_PROPERTY_DECLARATION_HPP_
#include<string>
#include "node_declaration.hpp"
#include "owlcpp/terms/node_tags_owl.hpp"

namespace owlcpp{ namespace logic{

/**@brief 
*******************************************************************************/
class Node_property : public Node_declaration {

   Node_property(const Refers_to ref) : Node_declaration(ref) {}

public:
   static std::string name() {return "property";}
   static Node_property object() {return Node_property(Object);}
   static Node_property data() {return Node_property(Data);}
   static Node_property annotation() {return Node_property(Annotation);}

   Node_property() : Node_declaration(None) {}

   void set(const Node_id nid) {
      using namespace owlcpp::terms;
      switch (nid()) {
      case owl_AsymmetricProperty::index:
      case owl_bottomObjectProperty::index:
      case owl_InverseFunctionalProperty::index:
      case owl_inverseOf::index:
      case owl_IrreflexiveProperty::index:
      case owl_ObjectProperty::index:
      case owl_ReflexiveProperty::index:
      case owl_SymmetricProperty::index:
      case owl_TransitiveProperty::index:
      case owl_topObjectProperty::index:
         Node_declaration::set(Object);
         break;

      case owl_bottomDataProperty::index:
      case owl_DatatypeProperty::index:
      case owl_topDataProperty::index:
         Node_declaration::set(Data);
         break;

      case owl_AnnotationProperty::index:
      case owl_OntologyProperty::index:
         Node_declaration::set(Annotation);
         break;

      //can be either object or data
      case rdfs_range::index:
      case owl_FunctionalProperty::index:
         break;
      }
   }

   bool operator==(Node_property const& nt) const { return ref_ == nt.ref_; }
   bool operator!=(Node_property const& nt) const { return ref_ != nt.ref_; }

private:
   std::string to_string_impl(const Refers_to ref) const {
      switch (ref) {
      case None:        return "undefined";
      case Object:      return "object property";
      case Data:        return "data property";
      case Annotation:  return "annotation property";
      default:          return "";
      }
   }

};


}//namespace logic
}//namespace owlcpp
#endif /* NODE_PROPERTY_DECLARATION_HPP_ */
