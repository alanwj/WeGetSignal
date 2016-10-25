#include "function_controller.h"

#define FUNCTION_CONTROLLER_TYPE (function_controller_get_type())
#define FUNCTION_CONTROLLER(obj)                               \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), FUNCTION_CONTROLLER_TYPE, \
                              FunctionController))

typedef struct _FunctionController FunctionController;
typedef struct _FunctionControllerClass FunctionControllerClass;

struct _FunctionController {
  GtkBin parent;
};

struct _FunctionControllerClass {
  GtkBinClass parent_class;
};

G_DEFINE_TYPE(FunctionController, function_controller, GTK_TYPE_BIN)

static void function_controller_init(FunctionController* self) {
  gtk_widget_init_template(GTK_WIDGET(self));
}

static void function_controller_class_init(FunctionControllerClass* klass) {
  gtk_widget_class_set_template_from_resource(
      GTK_WIDGET_CLASS(klass),
      "/com/alanwj/WeGetSignal/function-controller.ui");
}

GtkWidget* NewFunctionController(void) {
  return g_object_new(FUNCTION_CONTROLLER_TYPE, NULL);
}
