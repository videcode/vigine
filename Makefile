#make config
SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .c .o .d
###


COMPILER		= clang++ -g -O0
CPP_FLAGS		= -Wall -std=c++20 -Wno-undefined-inline

DIR_PROJECT	   := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))



DIR_DEBUG_BIN = $(DIR_PROJECT)/result/Debug/bin
DIR_DEBUG_OBJ = $(DIR_PROJECT)/result/Debug/obj
APP=

# call app Makefile
ifeq ($(strip $(APP)), codevis)
    include $(DIR_PROJECT)/src/app/$(APP)/Makefile
else
    #if no app select
    all:
		@echo "--- all ---"
		@echo "nothing to build"
		@echo


    install: ;
    installdirs: ;
    install-info: ;
    uninstall: ;
    install-strip: ;
    clean: ;
    distclean: ;
    mostlyclean: ;
    maintainer-clean: ;
		@echo "--- maintainer-clean ---"
		@echo 'This command is intended for maintainers to use; it'
		@echo 'deletes files that may need special tools to rebuild.'

    TAGS: ;
    info: ;
    dist: ;
    #check: ;
    #installckeck: ;

    installdirs: ;

endif




























