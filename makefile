# Copyright (c) 2025 Quinn
# Licensed under the MIT Licence. See LICENSE for details

# dependencies:
#  - make
#  - C compiler
#  - glfw3 (install glfw3:x64-mingw-dynamic via vcpkg for cross compilation)
#  - xxd (tinyxxd recommended; faster)
#  - (windows) git bash (recommended)

# build configuration, information about the current build process
NAME    := sudoku-algo
DEBUG   ?= 0
CC      ?= cc
LD      ?= ld
CFLAGS  += -c -std=gnu99 -Wall -Wextra -Wpedantic -Ilib -MMD -MP
LDFLAGS += -flto -lm

# profiles
ifeq ($(DEBUG),1)         # check whether we're debugging
CFLAGS  += -UNDEBUG -Og -g
PROF    := dbg
else                      # otherwise, assume release
CFLAGS  += -DNDEBUG -O2
PROF    := rel
endif

# build directory structure
DIR_BIN := bin/$(PROF)
DIR_OBJ := obj/$(PROF)

# get source files
SRC := $(shell find src/ -name '*.c')

# output files
BIN := $(DIR_BIN)/$(NAME)
OBJ := $(SRC:%.c=$(DIR_OBJ)/%.o) $(RES:%=$(DIR_OBJ)/%.o)
DEP := $(OBJ:.o=.d)

COMPILE_COMMANDS := $(DIR_OBJ)/compile_commands.json

.PHONY: run compile echo
run:     echo compile_commands $(BIN); $(BIN)
compile: echo compile_commands $(BIN)
echo:
	$(info $(shell printf "\033[36m")using compiler: $(CC)$(shell printf "\033[0m"))

# creates the binary (linking step)
$(BIN): $(OBJ)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(LDFLAGS)

# compilation rule
$(DIR_OBJ)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY .NOTPARALLEL:
clean:
	rm -rf obj bin compile_commands.json

# update compile commands if the makefile has been updated (for linting)
compile_commands: # default, empty rule
ifneq ($(shell which bear),)
ifneq ($(COMPILE_COMMANDS),)
ifeq ($(NOCMDS),)
.PHONY .NOTPARALLEL:
compile_commands: $(COMPILE_COMMANDS)
	ln -sf $< compile_commands.json

.NOTPARALLEL:
$(COMPILE_COMMANDS): makefile
	@$(warning regenerating compile_commands.json thus recompiling.)
	@mkdir -p ${@D} # ensure the target directory exists
	@touch $@       # create the file so it isn't retriggered (will just change modification time if already exists)
	@bear --output $@ -- make -B compile NOCMDS=1 # rebuild the current target using bear, to create the compile commands
endif
endif
endif

-include $(DEP)
