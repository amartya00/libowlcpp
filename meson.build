# Set up project
project(
    'owlcpp', 
    'cpp',
    version : '0.0.1',
    license: 'GPLV2'
)

add_global_arguments('--std=c++17', '-Werror', language : 'cpp')


# Dependencies
boost = dependency('boost', modules : ['filesystem'])
factplusplus = dependency('factplusplus')
raptor2 = dependency('raptor2')

# Set up sources
inc = include_directories('include')

# Sub projects
subdir('rdf')
subdir('io')
subdir('logic')
subdir('libinfo')
