#pragma once

#include <gtk/gtk.h>
#include "nums_app.h"

#define NUMS_APP_WINDOW_TYPE (nums_app_window_get_type())
G_DECLARE_FINAL_TYPE(NumsAppWindow, nums_app_window, NUMS,
		APP_WINDOW, GtkApplicationWindow);

NumsAppWindow* nums_app_window_new(NumsApp* app);

