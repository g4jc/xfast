
-include ../../.config

ifeq ($(CONFIG_SINGLE_APPLICATION), y)
target-n = xfastlogout
target_o-y = single_xfastlogout.o
else
target-y = xfastlogout
target_o-n = single_xfastlogout.o
endif

xfastlogout_files-y     = xfastlogout.c
xfastlogout_includes-y  = ../../src/lib
xfastlogout_libraries-y = ../../src/lib/
xfastlogout_ldflags-y   = -lxfast -lz -lpng -lfreetype -lexpat

single_xfastlogout.o_files-y    = xfastlogout.c
single_xfastlogout.o_includes-y = ../../src/lib
single_xfastlogout.o_cflags-y   = -Dmain=xfastlogout_main

include ../../Makefile.lib

ifneq ($(CONFIG_SINGLE_APPLICATION), y)
dist:
	$(CP) xfastlogout ../../dist/$(CONFIG_PATH_BIN)/xfastlogout
endif
