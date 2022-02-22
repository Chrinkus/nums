#include <gtk/gtk.h>

#include "nums_app.h"
#include "nums_app_win.h"

struct _NumsAppWindow {
	GtkApplicationWindow parent;
};

G_DEFINE_TYPE(NumsAppWindow, nums_app_window,
		GTK_TYPE_APPLICATION_WINDOW);

static void
nums_app_window_init(NumsAppWindow* window)
{
	// Nothing yet
}

static void
nums_app_window_class_init(NumsAppWindowClass* class)
{
	// Noting yet
}

NumsAppWindow*
nums_app_window_new(NumsApp* app)
{
	return g_object_new(NUMS_APP_WINDOW_TYPE, "application", app,
			NULL);
}

