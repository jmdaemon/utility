srcs = ['utility.c', 'file.c', 'command.c', 'progressbar.c']

utility = shared_library('utility',
  srcs,
  include_directories: inc,
  dependencies: deps)

dep_utility = declare_dependency(
  link_with : utility,
  include_directories: inc)
