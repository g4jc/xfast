
-include ../../../../.config

target_o-$(CONFIG_VIDEO_VESA) = video_vesa.o

video_vesa.o_files-y = kbd.c \
                       server.c \
                       vesa.h \
                       vbe.h

video_vesa.o_includes-y = ../../ \
                          ../../../lib \
                          ../helper/

include ../../../../Makefile.lib
