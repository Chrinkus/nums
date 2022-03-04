app_resources = gnome.compile_resources('nums_app_resources',
  'nums_app.gresource.xml',
  source_dir : '.')

executable('nums',
  'nums_data.c', 'nums_app.c', 'nums_app_win.c', 'main.c', app_resources,
  dependencies : deps)

