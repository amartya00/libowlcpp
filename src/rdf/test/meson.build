copy_triples_test = executable('copy_triples_test', 'copy_triples_run.cc', include_directories: [inc, rdf_inc], link_with: rdf)
id_tracker_test = executable('id_tracker_test', 'id_tracker_run.cc', include_directories: [inc, rdf_inc], link_with: rdf)
map_doc_test = executable('map_doc_test', 'map_doc_run.cc', include_directories: [inc, rdf_inc], link_with: rdf)
map_id_object_test = executable('map_id_object_test', 'map_id_object_run.cc', include_directories: [inc, rdf_inc], link_with: rdf)

test('Copy triples', copy_triples_test)
test('ID tracker', id_tracker_test)
test('Map doc', map_doc_test)
test('Mac ID object', map_id_object_test)
