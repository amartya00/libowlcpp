source_files = [
    'catalog.cc',
    'input.cc',
    'raptor_wrapper.cc',
    'read_ontology_iri.cc'
]

io = library(
    'owlcppio',
    source_files,
    include_directories: [inc, io_inc],
    dependencies: [boost, raptor2],
    link_with: rdf,
    install: true
)