bin_PROGRAMS = WeGetSignal

WeGetSignal_CFLAGS = @GTK_CFLAGS@ -std=c99 -Wall -Werror -pedantic
WeGetSignal_LDADD = @GTK_LIBS@

WeGetSignal_SOURCES = \
    function.h \
    function.c \
    function_controller.h \
    function_controller.c \
    function_display.h \
    function_display.c \
    sine.h \
    sine.c \
    weighted_sum.h \
    weighted_sum.c \
    wgs.c \
    wgs_app.h \
    wgs_app.c \
    wgs_app_window.h \
    wgs_app_window.c

nodist_WeGetSignal_SOURCES = $(BUILT_SOURCES)

BUILT_SOURCES = resources.c
CLEANFILES = $(BUILT_SOURCES)

resources.c: wgs.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies wgs.gresource.xml)
	$(GLIB_COMPILE_RESOURCES) $(srcdir)/wgs.gresource.xml --target=$@ --sourcedir=$(srcdir) --generate-source

EXTRA_DIST = \
    function-controller.ui \
    main-window.ui \
    wgs.gresource.xml
