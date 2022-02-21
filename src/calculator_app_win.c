#include <gtk/gtk.h>

#include "calculator_app.h"
#include "calculator_app_win.h"

struct _CalculatorAppWindow {
	GtkApplicationWindow parent;
};

G_DEFINE_TYPE(CalculatorAppWindow, calculator_app_window,
		GTK_TYPE_APPLICATION_WINDOW);

static void
calculator_app_window_init(CalculatorAppWindow* window)
{
	// Nothing yet
}

static void
calculator_app_window_class_init(CalculatorAppWindowClass* class)
{
	// Noting yet
}

CalculatorAppWindow*
calculator_app_window_new(CalculatorApp* app)
{
	return g_object_new(CALCULATOR_APP_WINDOW_TYPE, "application", app,
			NULL);
}

