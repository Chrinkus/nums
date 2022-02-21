#include <gtk/gtk.h>

#include "calculator_app.h"
#include "calculator_app_win.h"

struct _CalculatorApp {
	GtkApplication parent;
};

G_DEFINE_TYPE(CalculatorApp, calculator_app, GTK_TYPE_APPLICATION);

static void
calculator_app_init(CalculatorApp* app)
{
	// Nothing yet
}

static void
calculator_app_activate(GApplication* app)
{
	CalculatorAppWindow* window;

	window = calculator_app_window_new(CALCULATOR_APP(app));
	gtk_window_present(GTK_WINDOW(window));
}

static void
calculator_app_class_init(CalculatorAppClass* class)
{
	G_APPLICATION_CLASS(class)->activate = calculator_app_activate;
}

CalculatorApp*
calculator_app_new(void)
{
	return g_object_new(CALCULATOR_APP_TYPE,
			"application-id", "com.github.Chrinkus",
			"flags", G_APPLICATION_HANDLES_OPEN,
			NULL);
}
