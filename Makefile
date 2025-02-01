.DEFAULT_GOAL := build

QMK_FIRMWARE_ROOT = $(shell qmk config -ro user.qmk_home | cut -d= -f2 | sed -e 's@^None$$@@g')
ifeq ($(QMK_FIRMWARE_ROOT),)
    $(error Cannot determine qmk_firmware location. `qmk config -ro user.qmk_home` is not set)
endif
SC2040_SYMLINK = $(QMK_FIRMWARE_ROOT)/keyboards/sofle_choc_rp2040

.PHONY: setup
setup:
	echo `qmk config -ro user.qmk_home | cut -d= -f2`
	echo "$(SC2040_SYMLINK)"
	if [ ! -L $(SC2040_SYMLINK) ] ; then echo "creating symlink $(SC2040_SYMLINK)"; ln -s `pwd`/keyboards/sofle_choc_rp2040 $(SC2040_SYMLINK);  fi

.PHONY: build
build: setup
	qmk compile -kb sofle_choc_rp2040 -km default

.PHONY: flash
flash: setup
	qmk flash -kb sofle_choc_rp2040 -km default

clean:
	qmk clean
	rm $(SC2040_SYMLINK)
