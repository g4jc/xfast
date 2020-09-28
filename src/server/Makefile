
-include ../../.config

subdir-$(CONFIG_VIDEO_FBDEV)    = ./video/fb
subdir-$(CONFIG_VIDEO_SDL)     += ./video/sdl
subdir-$(CONFIG_VIDEO_SVGALIB) += ./video/svga
subdir-$(CONFIG_VIDEO_VESA)    += ./video/vesa
subdir-$(CONFIG_VIDEO_PSPDEV)  += ./video/pspdev
subdir-$(CONFIG_VIDEO_GDI)     += ./video/gdi
subdir-$(CONFIG_VIDEO_GP2X)    += ./video/gp2x
subdir-$(CONFIG_VIDEO_NULL)    += ./video/null
subdir-$(CONFIG_VIDEO_HELPER)  += ./video/helper

target-y  = xfast

xfast_files-y = event.c \
                id.c \
                irr.c \
                kbd.c \
                mouse.c \
                priority.c \
                server.c \
                single.c \
                socket.c \
                start.c \
                surface.c \
                theme.c \
                window.c \
                window_handler.c \
                window_move_resize.c

xfast_files-$(CONFIG_VIDEO_FBDEV)   += ./video/fb/video_fb.o
xfast_files-$(CONFIG_VIDEO_SDL)     += ./video/sdl/video_sdl.o
xfast_files-$(CONFIG_VIDEO_SVGALIB) += ./video/svga/video_svga.o
xfast_files-$(CONFIG_VIDEO_VESA)    += ./video/vesa/video_vesa.o
xfast_files-$(CONFIG_VIDEO_PSPDEV)  += ./video/pspdev/video_pspdev.o
xfast_files-$(CONFIG_VIDEO_GDI)     += ./video/gdi/video_gdi.o
xfast_files-$(CONFIG_VIDEO_GP2X)    += ./video/gp2x/video_gp2x.o
xfast_files-$(CONFIG_VIDEO_NULL)    += ./video/null/video_null.o
xfast_files-$(CONFIG_VIDEO_HELPER)  += ./video/helper/video_helper.o

ifeq ($(CONFIG_SINGLE_APPLICATION), y)
xfast_files-$(CONFIG_DEMO_CHILD)    += ../../demo/child/single_child.o
xfast_files-$(CONFIG_DEMO_DESKTOP)  += ../../demo/desktop/single_desktop.o
xfast_files-$(CONFIG_DEMO_HIDE)     += ../../demo/hide/single_hide.o
xfast_files-$(CONFIG_DEMO_LOAD)     += ../../demo/load/single_load.o
xfast_files-$(CONFIG_DEMO_SIMPLE)   += ../../demo/simple/single_simple.o
xfast_files-$(CONFIG_DEMO_OBJECT)   += ../../demo/object/single_object.o
xfast_files-$(CONFIG_DEMO_TEMP)     += ../../demo/temp/single_temp.o
xfast_files-$(CONFIG_DEMO_TERM)     += ../../demo/term/single_term.o
xfast_files-$(CONFIG_DEMO_TIMER)    += ../../demo/timer/single_timer.o
xfast_files-$(CONFIG_DEMO_LOGOUT)   += ../../demo/xfastlogout/single_xfastlogout.o
xfast_files-$(CONFIG_DEMO_IMAGE)    += ../../demo/img/single_img.o
xfast_files-$(CONFIG_DEMO_ONSCREENKEYBOARD) += ../../demo/onscreenkeyboard/single_onscreenkeyboard.o
xfast_files-$(CONFIG_DEMO_WIDGETX)  += ../../demo/widgetx/single_widgetx.o
endif

xfast_includes-$(CONFIG_VIDEO_PSPDEV) += $(shell psp-config -p)/include
xfast_includes-y  += ./ ../lib

xfast_libraries-y += ../lib
xfast_libraries-$(CONFIG_VIDEO_PSPDEV) += $(shell psp-config -p)/lib

xfast_ldflags-y += -lxfast
xfast_ldflags-y += -lm
xfast_ldflags-y += -lz
xfast_ldflags-y += -lpng
xfast_ldflags-y += -lexpat
xfast_ldflags-y += -lfreetype
xfast_ldflags-$(CONFIG_VIDEO_SDL)   += $(shell sdl-config --libs)
xfast_ldflags-$(CONFIG_VIDEO_SVGALIB)  += -lvga
xfast_ldflags-$(CONFIG_VIDEO_VESA) += -llrmi
xfast_ldflags-$(CONFIG_PLATFORM_MINGW) += -lgdi32
xfast_ldflags-$(CONFIG_PLATFORM_MINGW) += -lintl

ifeq ($(CONFIG_WIDGET_LIBRARY), y)
xfast_libraries-y += ../widget
xfast_ldflags-y   += -lwidget
endif

ifeq ($(CONFIG_THEME_PLUGIN), y)
xfast_ldflags-y   += -ldl
endif

xfast_ldflags-$(CONFIG_VIDEO_PSPDEV) += -lpspdebug \
                                        -lpspdisplay \
                                        -lpspge \
                                        -lpspctrl \
                                        -lpspsdk \
                                        -lc \
                                        -lpspnet \
                                        -lpspnet_inet \
                                        -lpsputility \
                                        -lpspuser \
                                        -lpspkernel

include ../../Makefile.lib

dist:
ifeq ($(CONFIG_PLATFORM_PSPDEV), y)
	psp-fixup-imports xfast
	mksfo 'XFast Windowing System' param.sfo
	$(MKDIR) ../../dist/$(CONFIG_PATH_BIN)/xfast
	psp-strip xfast -o ../../dist/$(CONFIG_PATH_BIN)/xfast/eboot.pbp
	$(MKDIR) ../../dist/$(CONFIG_PATH_BIN)/xfast%
	pack-pbp ../../dist/$(CONFIG_PATH_BIN)/xfast%/eboot.pbp \
	         param.sfo \
	         ../../tools/pspdev/icon0.png \
	         NULL \
	         NULL \
	         ../../tools/pspdev/pic1.png \
	         NULL \
	         NULL \
	         NULL
	rm param.sfo
else
ifneq ($(CONFIG_PLATFORM_MINGW), y)
	strip xfast
endif	
	$(CP) xfast ../../dist/$(CONFIG_PATH_BIN)/xfast
	$(CP) startxfast ../../dist/$(CONFIG_PATH_BIN)/startxfast
endif
