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

enum { NUMS_DATA_MAXBUFF = 16 };

struct nums_data {
	char buffer[NUMS_DATA_MAXBUFF];
};

static void
nums_data_init(struct nums_data* data)
{
	strcpy(data->buffer, "0");
}

static void
nums_data_clear(struct nums_data* data)
{
	strcpy(data->buffer, "0");
}

static void
nums_data_append_number(struct nums_data* data, const char* digit)
{
	if (strcmp(data->buffer, "0") == 0) {
		strcpy(data->buffer, digit);
	} else if (strlen(data->buffer) < NUMS_DATA_MAXBUFF - 1) {
		strcat(data->buffer, digit);
	}
}

static void
nums_data_append_decimal(struct nums_data* data)
{
	char* s = data->buffer;
	int len = strlen(s);
	if (!strchr(s, '.') && len < NUMS_DATA_MAXBUFF - 1) {
		s[len++] = '.';
		s[len] = '\0';
	}
}

static void
nums_data_change_sign(struct nums_data* data)
{
	char* s = data->buffer;
	if (s[0] == '-') {
		for (char* p = s+1; *s; ++s, ++p)
			*s = *p;
	} else if (strlen(s) < NUMS_DATA_MAXBUFF - 1) {
		for (char a = '-', b = *s; a; *s = a, a = b, ++s)
			b = b ? *s : b;	// change b until it is '\0'
		*s = '\0';
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 

struct _NumsAppWindow {
	GtkApplicationWindow parent;

	GtkLabel* display;

	struct nums_data* state;
};

G_DEFINE_TYPE(NumsAppWindow, nums_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void
update_display(GtkLabel* display, struct nums_data* state)
{
	const char* format = "<span size=\"x-large\">%s</span>";
	char* markup = g_markup_printf_escaped(format, state->buffer);

	gtk_label_set_markup(GTK_LABEL(display), markup);

	g_free(markup);
}

static void
clear_cb(GtkWidget* w, gpointer p)
{
	NumsAppWindow* window = NUMS_APP_WINDOW(p);

	nums_data_clear(window->state);
	update_display(window->display, window->state);
}

static void
number_cb(GtkWidget* w, gpointer p)
{
	NumsAppWindow* window = NUMS_APP_WINDOW(p);

	const char* digit = gtk_button_get_label(GTK_BUTTON(w));
	nums_data_append_number(window->state, digit);
	update_display(window->display, window->state);
}

static void
decimal_cb(GtkWidget* w, gpointer p)
{
	NumsAppWindow* window = NUMS_APP_WINDOW(p);

	nums_data_append_decimal(window->state);
	update_display(window->display, window->state);
}

static void
change_sign_cb(GtkWidget* w, gpointer p)
{
	NumsAppWindow* window = NUMS_APP_WINDOW(p);
	nums_data_change_sign(window->state);
	update_display(window->display, window->state);
}

static void
nums_app_window_init(NumsAppWindow* window)
{
	gtk_widget_init_template(GTK_WIDGET(window));

	window->state = malloc(sizeof(struct nums_data));
	nums_data_init(window->state);

	gtk_widget_set_halign(GTK_WIDGET(window->display), GTK_ALIGN_END);
	update_display(window->display, window->state);
}

static void
nums_app_window_dispose(GObject* obj)
{
	NumsAppWindow* window = NUMS_APP_WINDOW(obj);

	free(window->state);

	G_OBJECT_CLASS(nums_app_window_parent_class)->dispose(obj);
}

static void
nums_app_window_class_init(NumsAppWindowClass* klass)
{
	G_OBJECT_CLASS(klass)->dispose = nums_app_window_dispose;

	gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass),
			"/com/github/Chrinkus/nums/window.ui");

	gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(klass),
			NumsAppWindow, display);

	gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(klass),
			clear_cb);
	gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(klass),
			number_cb);
	gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(klass),
			decimal_cb);
	gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(klass),
			change_sign_cb);
}

NumsAppWindow*
nums_app_window_new(NumsApp* app)
{
	return g_object_new(NUMS_APP_WINDOW_TYPE, "application", app, NULL);
}

