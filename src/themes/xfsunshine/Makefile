
-include ../../../.config

target_so-y = xfsunshine.so

xfsunshine.so_files-y    = xfsunshine.c
xfsunshine.so_includes-y = ../../lib ../../server

include ../../../Makefile.lib

dist:
	$(CP) xfsunshine.so ../../../dist/$(CONFIG_PATH_THEMES)/xfsunshine.so
