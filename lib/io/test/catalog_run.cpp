/** @file "/owlcpp/lib/io/test/catalog_run.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define BOOST_TEST_MODULE catalog_run
#include "boost/test/unit_test.hpp"
#include "boost/filesystem.hpp"
#include "test/exception_fixture.hpp"
#include "test/sample_data.hpp"
#include "owlcpp/io/catalog.hpp"

namespace owlcpp{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

const std::string path1 = "version_test_b.owl";
const std::string iri1 = "http://purl.obolibrary.org/obo/ido/dev/version_test_b.owl";

/**
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Catalog cat;
//   cat.add(sample_file_path(path1));
//   Doc_id const* did1 = cat.find_doc(iri1);
//   BOOST_REQUIRE(did1);
//   BOOST_CHECK_EQUAL(cat.iri(*did1), iri1);
//   BOOST_CHECK_EQUAL(cat.path(*did1), boost::filesystem::canonical(path1).string());
}

}//namespace test
}//namespace owlcpp
