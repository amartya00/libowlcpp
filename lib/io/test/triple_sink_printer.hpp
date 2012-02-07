/** @file "/owlcpp/lib/io/test/triple_sink_printer.hpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#ifndef TRIPLE_SINK_PRINTER_HPP_
#define TRIPLE_SINK_PRINTER_HPP_
#include <iostream>
#include "raptor2.h"

namespace owlcpp{ namespace test{

/**@brief 
*******************************************************************************/
struct Triple_sink_printer {
   void insert(void const* statement) {
      const raptor_statement* rs = static_cast<const raptor_statement*>(statement);
      std::cout
      << raptor_term_to_string(rs->subject) << ' '
      << raptor_term_to_string(rs->predicate) << ' '
      << raptor_term_to_string(rs->object) << '\n'
      ;
   }
   void finalize() const {}
};


}//namespace test
}//namespace owlcpp
#endif /* TRIPLE_SINK_PRINTER_HPP_ */
