/* nums_app_win.c
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 

enum { NUMS_DISPLAY_MAXBUFF = 10 };

struct nums_display {
	GtkLabel* screen;
	char buffer[NUMS_DISPLAY_MAXBUFF];
};

static void
nums_display_update(struct nums_display* display)
{
	const char* format = "<span size=\"x-large\">%s</span>";
	char* markup = g_markup_printf_escaped(format, display->buffer);

	gtk_label_set_markup(GTK_LABEL(display->screen), markup);

	g_free(markup);
}

static void
nums_display_clear(struct nums_display* display)
{
	strcpy(display->buffer, "0");
	nums_display_update(display);
}

static void
nums_display_init(struct nums_display* display)
{
	gtk_widget_set_halign(GTK_WIDGET(display->screen), GTK_ALIGN_END);
	nums_display_clear(display);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 

struct _NumsAppWindow {
	GtkApplicationWindow parent;

	struct nums_display display;
};

G_DEFINE_TYPE(NumsAppWindow, nums_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void
nums_app_window_init(NumsAppWindow* window)
{
	gtk_widget_init_template(GTK_WIDGET(window));
	nums_display_init(&window->display);
}

static void
nums_app_window_class_init(NumsAppWindowClass* class)
{
	gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class),
			"/com/github/Chrinkus/nums/window.ui");

	gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class),
			NumsAppWindow, display);
}

NumsAppWindow*
nums_app_window_new(NumsApp* app)
{
	return g_object_new(NUMS_APP_WINDOW_TYPE, "application", app, NULL);
}

