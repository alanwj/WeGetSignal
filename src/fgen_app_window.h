#ifndef   FGEN_APP_WINDOW_H_
#define   FGEN_APP_WINDOW_H_

#include <gtk/gtk.h>

#include "fgen_app.h"

#define FGEN_APP_WINDOW_TYPE    (fgen_app_window_get_type())
#define FGEN_APP_WINDOW(obj)    (G_TYPE_CHECK_INSTANCE_CAST((obj), FGEN_APP_WINDOW_TYPE, FGenAppWindow))

typedef struct _FGenAppWindow       FGenAppWindow;
typedef struct _FGenAppWindowClass  FGenAppWindowClass;

GType fgen_app_window_get_type(void);

FGenAppWindow *fgen_app_window_new(FGenApp *application);

#endif    // FGEN_APP_WINDOW_H_
