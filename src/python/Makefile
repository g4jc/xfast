
-include ../../.config

target_so-y = xfast.so

xfast.so_files-y = window.c \
                   xynthpy.c \
                   xynthpy.h

xfast.so_includes-y = ../lib \
                      $(CONFIG_PYTHON_INCLUDES)

xfast.so_libraries-y = ../lib

xfast.so_ldflags-y = -$(CONFIG_PYTHON_LDFLAGS) -lxfast

include ../../Makefile.lib
