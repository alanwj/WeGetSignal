bin_PROGRAMS = fgen

fgen_CFLAGS = @GTK_CFLAGS@ -std=c99 -Wall -Werror -pedantic
fgen_LDADD = @GTK_LIBS@

fgen_SOURCES = fgen.c \
               fgen_app.c \
               fgen_app.h \
               fgen_app_window.c \
               fgen_app_window.h \
               resources.c

BUILT_SOURCES = resources.c
CLEANFILES = $(BUILT_SOURCES)

resources.c: fgen.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies fgen.gresource.xml)
	$(GLIB_COMPILE_RESOURCES) $(srcdir)/fgen.gresource.xml --target=$@ --sourcedir=$(srcdir) --generate-source
