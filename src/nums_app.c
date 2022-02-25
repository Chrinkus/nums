/* nums_app.c
 *
 * Copyright (C) 2022 Christopher Schick seeschickrun@gmail.com
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
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
			"application-id", "com.github.Chrinkus.nums",
			NULL);
}
