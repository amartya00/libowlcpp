source_files = [
    'any_triple_element.cc',
    'literal_datatypes.cc',
    'nodes_std.cc',
    'print_id.cc',
    'print_node.cc',
    'query_triple_any.cc'
]

rdf = library(
    'owlcpprdf',
    source_files,
    include_directories: [inc, rdf_inc],
    dependencies: [boost, raptor2],
    install: true
)