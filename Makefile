
-include .config

help:
	@echo ""
	@echo "make help         - this text"
	@echo "make menuconfig   - open menu configuration"
	@echo "make all          - build everything"
	@echo "make dist         - install everything to dist path"
	@echo "make install      - install everything to install path"
	@echo ""
	@echo "make doxy-doc     - build doxygen documentation"
	@echo ""
	@echo "make clean        - clean everything"
	@echo "make distclean    - clean much more"
	@echo ""
	@echo "make linux        - linux default configuration"
	@echo "make linux-single - linux single app configuration"
	@echo "make mingw        - mingw default configuration"
	@echo "make pspdev       - pspdev default configuration"
	@echo "make gp2x         - gp2x default configuration"
	@echo ""

check_goal := $(filter-out menuconfig, $(MAKECMDGOALS))
check_goal := $(filter-out doxy-doc, $(checkgoal))
check_goal := $(filter-out distclean, $(check_goal))
check_goal := $(filter-out clean, $(check_goal))
check_goal := $(filter-out linux, $(check_goal))
check_goal := $(filter-out linux-single, $(check_goal))
check_goal := $(filter-out mingw, $(check_goal))
check_goal := $(filter-out pspdev, $(check_goal))
check_goal := $(filter-out gp2x, $(check_goal))
check_goal := $(strip $(check_goal))

ifneq ($(check_goal),)
ifneq "$(CONFIG_CONFIGURED)" "y"
    $(error You must first run make menuconfig)
endif
endif

subdir-y := tools/config
subdir-y += src
subdir-n := tools/theme
subdir-n += tools/optimize

include Makefile.lib

.PHONY: linux linux-single mingw pspdev gp2x
linux linux-single mingw pspdev gp2x:
	$(CP) configs/$@.config .config
	$(CP) configs/$@.h src/lib/config.h
	if [ -e "src/configs/$@.conf" ]; then $(CP) src/configs/$@.conf src/configs/xfast.conf; fi

.PHONY: menuconfig
menuconfig: tools/config_all
	tools/config/mconf configs/Config

.PHONY: distclean
distclean: clean
	@$(RM) .config .config.cmd .config.old .kconfig.d .tmpconfig.h .tmpconfig src/lib/config.h dist doc

.PHONY: distdirs
distdirs: __FORCE
	$(MKDIR) dist
	$(MKDIR) dist/$(CONFIG_PATH_BIN)
	$(MKDIR) dist/$(CONFIG_PATH_LIB)
	$(MKDIR) dist/$(CONFIG_PATH_LIB)/pkgconfig
	$(MKDIR) dist/$(CONFIG_PATH_INCLUDE)
	$(MKDIR) dist/$(CONFIG_PATH_SHARE)
	$(MKDIR) dist/$(CONFIG_PATH_FONTS)
	$(MKDIR) dist/$(CONFIG_PATH_CONFIGS)
	$(MKDIR) dist/$(CONFIG_PATH_THEMES)

.PHONY: xfast.pc
xfast.pc: xfast.pc.in
	$(SED) -e 's,@prefix@,$(CONFIG_PATH_INSTALL)/,g' \
	       -e 's,@version@,0.9.00,g' \
	       -e 's,@widget_libs@,-lwidget,g' \
	       xfast.pc.in > dist/$(CONFIG_PATH_LIB)/pkgconfig/xfast.pc

.PHONY: dist
dist: distdirs xfast.pc
	@true

.PHONY: install
install: dist
ifeq ($(CONFIG_PLATFORM_PSPDEV), y)
	$(MKDIR) dist/psp/game
	$(CP) dist/bin/xfast dist/psp/game
	$(CP) dist/bin/xfast% dist/psp/game
	$(CP) dist/share dist/psp/game/xfast
	$(RM) dist/$(CONFIG_PATH_BIN)
	$(RM) dist/$(CONFIG_PATH_LIB)
	$(RM) dist/$(CONFIG_PATH_INCLUDE)
	$(RM) dist/share
else
	$(CP) ./dist/* $(CONFIG_PATH_INSTALL)/
endif

.PHONY: doxy-doc
doxy-doc:
	SRCDIR='.' \
	PROJECT='xfast' \
	DOCDIR='doc' \
	VERSION='0.9.00' \
	PERL_PATH='/usr/bin/perl' \
	HAVE_DOT='NO' \
	GENERATE_MAN='NO' \
	GENERATE_RTF='NO' \
	GENERATE_XML='NO' \
	GENERATE_HTMLHELP='NO' \
	GENERATE_CHI='NO' \
	GENERATE_HTML='YES' \
	GENERATE_LATEX='NO' \
	EXCLUDE_PATTERNS='dist ports tools demo expat freetype2 libpng libz pixman pthread_w32' \
	/usr/bin/doxygen \
	./doxygen.cfg
