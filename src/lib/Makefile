
-include ../../.config

#subdir-y := ./libz
#subdir-y := ./libpng
#subdir-y := ./freetype2
#subdir-y += ./expat
subdir-y := ./pixman

target_a-$(CONFIG_LIBRARY_STATIC) = libxfast.a

libxfast.a_includes-y := ./
#libxfast.a_includes-y += ./libz
#libxfast.a_includes-y += ./libpng
libxfast.a_includes-y += /usr/include/freetype2
#libxfast.a_includes-y += ./expat
libxfast.a_includes-y += ./pixman

ifeq ($(CONFIG_PLATFORM_PSPDEV), y)
	libxfast.a_includes-y += $(shell psp-config -p)/include
endif

libxfast.a_files-y = alloc.c \
                     child.c \
                     config.c \
                     debug.c \
                     driver.c \
                     event.c \
                     eventq.c \
                     font.c \
                     gettime.c \
                     grlib.c \
                     handler.c \
                     hashtable.c \
                     image.c \
                     image_gif.c \
                     image_png.c \
                     image_xpm.c \
                     list.c \
                     pipe_api.c \
                     pollfd.c \
                     region.c \
                     render.c \
                     socket.c \
                     socket_api.c \
                     surface.c \
                     thread.c \
                     timer.c \
                     window.c \
                     xml.c

#libxfast.a_files-y += ./expat/libexpat.o
#libxfast.a_files-y += ./freetype2/libfreetype2.o
#libxfast.a_files-y += ./libpng/libpng.o
#libxfast.a_files-y += ./libz/libz.o
libxfast.a_files-y += ./pixman/libpixman.o

target_so-$(CONFIG_LIBRARY_SHARED) = libxfast.so

libxfast.so_includes-y = $(libxfast.a_includes-y)
libxfast.so_ldflags-y = -lpthread \
                        -lfreetype \
			-lpng \
			-lexpat \
                        -lm
libxfast.so_files-y = $(libxfast.a_files-y)

include ../../Makefile.lib

dist:
ifeq ($(CONFIG_PLATFORM_LINUX), y)
	$(CP) xfast.h ../../dist/$(CONFIG_PATH_INCLUDE)/xfast.h
	$(CP) libxfast.a ../../dist/$(CONFIG_PATH_LIB)/libxfast.a
	$(CP) libxfast.so ../../dist/$(CONFIG_PATH_LIB)/libxfast.so
else
	@true
endif
