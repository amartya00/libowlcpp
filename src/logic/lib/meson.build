source_files = [
    'factpp/adaptor_triple.cc',
    'factpp/data_instance.cc',
    'factpp/data_property.cc',
    'factpp/data_range.cc',
    'factpp/data_type.cc',
    'factpp/expression.cc',
    'factpp/obj_property.cc',
    'factpp/obj_type.cc',
    'factpp/query_fact.cc',
    'expression_args.cc',
    'triple_to_fact.cc'
]

logic = library(
    'owlcpplogic',
    source_files,
    include_directories: [inc, logic_inc],
    dependencies: [boost, factplusplus, raptor2],
    link_with: rdf,
    install: true
)