# Set up project
project(
    'owlcpp', 
    'cpp',
    version : '0.0.1',
    license: 'GPLV2'
)

add_global_arguments('--std=c++17', '-Werror', language : 'cpp')


# Dependencies
boost = dependency('boost', modules : ['filesystem', 'system'])
factplusplus = dependency('factplusplus')
raptor2 = dependency('raptor2')
catch = dependency('catch2')

# Set up includes
inc = include_directories('include')

# Sub projects
subdir('src/rdf')
subdir('src/io')
subdir('src/logic')
subdir('src/libinfo')
