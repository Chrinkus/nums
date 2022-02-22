#include <gtk/gtk.h>

#include "nums_app.h"
#include "nums_app_win.h"

struct _NumsApp {
	GtkApplication parent;
};

G_DEFINE_TYPE(NumsApp, nums_app, GTK_TYPE_APPLICATION);

static void
nums_app_init(NumsApp* app)
{
	// Nothing yet
}

static void
nums_app_activate(GApplication* app)
{
	NumsAppWindow* window;

	window = nums_app_window_new(NUMS_APP(app));
	gtk_window_present(GTK_WINDOW(window));
}

static void
nums_app_class_init(NumsAppClass* class)
{
	G_APPLICATION_CLASS(class)->activate = nums_app_activate;
}

NumsApp*
nums_app_new(void)
{
	return g_object_new(NUMS_APP_TYPE,
			"application-id", "com.github.Chrinkus",
			"flags", G_APPLICATION_HANDLES_OPEN,
			NULL);
}
