.DEFAULT_GOAL := build
.PHONY: *

QMK_FIRMWARE_ROOT = $(shell qmk config -ro user.qmk_home | cut -d= -f2 | sed -e 's@^None$$@@g')
ifeq ($(QMK_FIRMWARE_ROOT),)
    $(error Cannot determine qmk_firmware location. `qmk config -ro user.qmk_home` is not set)
endif

SC2040_SYMLINK = $(QMK_FIRMWARE_ROOT)/keyboards/sofle_choc_rp2040
ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

setup:
	@if [ ! -L $(SC2040_SYMLINK) ] ; then \
		echo "creating symlink $(SC2040_SYMLINK)"; \
		ln -s $(ROOT_DIR)/keyboards/sofle_choc_rp2040 $(SC2040_SYMLINK);\
	fi

build: setup
	qmk compile -kb sofle_choc_rp2040 -km default

flash: setup
	qmk flash -kb sofle_choc_rp2040 -km default

clean:
	qmk clean
	@if [ -L $(SC2040_SYMLINK) ]; then rm $(SC2040_SYMLINK); fi
