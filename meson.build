project('nums', 'c',
  license : 'GPL-2.0-or-later',
  version : '0.1',
  default_options : 'c_std=gnu99')

gnome = import('gnome')

deps = [
  dependency('gtk4'),
  dependency('cgs')
]

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

subdir('src')

