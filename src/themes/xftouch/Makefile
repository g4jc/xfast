
-include ../../../.config

target_so-y = xftouch.so

xftouch.so_files-y    = xftouch.c
xftouch.so_includes-y = ../../lib ../../server

include ../../../Makefile.lib

dist:
	$(CP) xftouch.so ../../../dist/$(CONFIG_PATH_THEMES)/xftouch.so
