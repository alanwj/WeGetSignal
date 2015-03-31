#ifndef   FGEN_APP_H_
#define   FGEN_APP_H_

#include <gtk/gtk.h>

#define FGEN_APP_TYPE   (fgen_app_get_type())
#define FGEN_APP(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj), FGEN_APP_TYPE, FGenApp))

typedef struct _FGenApp       FGenApp;
typedef struct _FGenAppClass  FGenAppClass;

GType fgen_app_get_type(void);

FGenApp *fgen_app_new(void);

#endif    // FGEN_APP_H_
