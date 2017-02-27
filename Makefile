##### global settings #####

CC := gcc
LD := ld
CFLAGS := -MMD -Wall -Werror -c

LIB_COMMON_DIR := lib-common
LIBC_INC_DIR := $(LIB_COMMON_DIR)/uclibc/include
LIBC_LIB_DIR := $(LIB_COMMON_DIR)/uclibc/lib
LIBC := $(LIBC_LIB_DIR)/libc.a
#FLOAT := obj/$(LIB_COMMON_DIR)/FLOAT/FLOAT.a

include config/Makefile.git
include config/Makefile.build

all: nemu


##### rules for building the project #####

include nemu/Makefile.part
include testcase/Makefile.part
include lib-common/FLOAT/Makefile.part
include kernel/Makefile.part
include game/Makefile.part


nemu: $(nemu_BIN)
testcase: $(testcase_BIN)
kernel: $(kernel_BIN)
game: $(game_BIN)

$(testcase_OBJ_DIR)/game: $(game_BIN)
	mkdir -p $(@D)
	ln -sf $(abspath $<) $@

.PHONY: nemu testcase kernel game

##### rules for cleaning the project #####

clean-nemu:
	-rm -rf obj/nemu 2> /dev/null

clean-testcase:
	-rm -rf obj/testcase 2> /dev/null

clean-kernel:
	-rm -rf obj/kernel 2> /dev/null

clean-game:
	-rm -rf obj/game 2> /dev/null

clean:
	-rm -rf obj 2> /dev/null
	-rm -f *log.txt entry $(FLOAT) 2> /dev/null

.PHONY: clean-nemu clean-testcase clean-kernel clean-game clean

##### some convinient rules #####

PROG ?= mov
PROG_PATH := $(testcase_OBJ_DIR)/$(PROG)

entry: $(PROG_PATH)
	objcopy -S -O binary $< $@

run: $(nemu_BIN) $(PROG_PATH) entry
	$(call git_commit, "run")
	$(nemu_BIN) $(PROG_PATH)

gdb: $(nemu_BIN) $(PROG_PATH) entry
	$(call git_commit, "gdb")
	gdb -s $(nemu_BIN) --args $(nemu_BIN) $(PROG_PATH)

run-all: $(nemu_BIN) $(testcase_BIN) entry
	$(call git_commit, "run-all")
	@bash run-all.sh $(testcase_BIN)

submit: clean
	git gc
	cd .. && tar cvj $(shell pwd | grep -o '[^/]*$$') > $(STU_ID).tar.bz2

.PHONY: run gdb run-all submit
