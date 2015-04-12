#ifndef   WGS_APP_WINDOW_H_
#define   WGS_APP_WINDOW_H_

#include <gtk/gtk.h>

#include "wgs_app.h"

#define WGS_APP_WINDOW_TYPE   (wgs_app_window_get_type())
#define WGS_APP_WINDOW(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj), WGS_APP_WINDOW_TYPE, WgsAppWindow))

typedef struct _WgsAppWindow        WgsAppWindow;
typedef struct _WgsAppWindowClass   WgsAppWindowClass;

GType wgs_app_window_get_type(void);

WgsAppWindow *wgs_app_window_new(WgsApp *application);

#endif    // WGS_APP_WINDOW_H_
