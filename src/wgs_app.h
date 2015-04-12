#ifndef   WGS_APP_H_
#define   WGS_APP_H_

#include <gtk/gtk.h>

#define WGS_APP_TYPE    (wgs_app_get_type())
#define WGS_APP(obj)    (G_TYPE_CHECK_INSTANCE_CAST((obj), WGS_APP_TYPE, WgsApp))

typedef struct _WgsApp        WgsApp;
typedef struct _WgsAppClass   WgsAppClass;

GType wgs_app_get_type(void);

WgsApp *wgs_app_new(void);

#endif    // WGS_APP_H_
