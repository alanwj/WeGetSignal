bin_PROGRAMS = WeGetSignal

WeGetSignal_CFLAGS = @GTK_CFLAGS@ -std=c99 -Wall -Werror -pedantic
WeGetSignal_LDADD = @GTK_LIBS@

WeGetSignal_SOURCES = \
    function_display.c \
    function_display.h \
    resources.c \
    signal_function.c \
    signal_function.h \
    sin_function.c \
    sin_function.h \
    wgs.c \
    wgs_app.c \
    wgs_app.h \
    wgs_app_window.c \
    wgs_app_window.h

BUILT_SOURCES = resources.c
CLEANFILES = $(BUILT_SOURCES)

resources.c: wgs.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies wgs.gresource.xml)
	$(GLIB_COMPILE_RESOURCES) $(srcdir)/wgs.gresource.xml --target=$@ --sourcedir=$(srcdir) --generate-source
