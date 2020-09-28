
subdir-y = lxdialog

target.host-y := conf
target.host-y += mconf

conf_files-y = conf.c zconf.tab.c

mconf_files-y = mconf.c zconf.tab.c lxdialog/lxdialog.o
mconf_ldflags-y = -lncurses -ltinfo

# necessary for MINGW only
#mconf_ldflags-y += -lintl
#mconf_ldflags-$(CONFIG_PLATFORM_MINGW) += -lintl

include ../../Makefile.lib
