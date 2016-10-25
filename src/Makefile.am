bin_PROGRAMS = WeGetSignal

WeGetSignal_CFLAGS = @GTK_CFLAGS@ -std=c99 -Wall -Werror -pedantic
WeGetSignal_LDADD = @GTK_LIBS@

WeGetSignal_SOURCES = \
    function.h \
    function.c \
    function_display.h \
    function_display.c \
    resources.c \
    sine.h \
    sine.c \
    weighted_sum.h \
    weighted_sum.c \
    wgs.c \
    wgs_app.h \
    wgs_app.c \
    wgs_app_window.h \
    wgs_app_window.c

BUILT_SOURCES = resources.c
CLEANFILES = $(BUILT_SOURCES)

resources.c: wgs.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies wgs.gresource.xml)
	$(GLIB_COMPILE_RESOURCES) $(srcdir)/wgs.gresource.xml --target=$@ --sourcedir=$(srcdir) --generate-source
