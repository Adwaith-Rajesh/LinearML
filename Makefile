BUILD_DIR=./build
LIB_DIR=$(BUILD_DIR)/lib
SRC_DIR=./src

SHARED_LIB=$(LIB_DIR)/liblinearml.so
CODEDIRS=$(SRC_DIR)/ds $(SRC_DIR)/ml $(SRC_DIR)/model $(SRC_DIR)/parsers $(SRC_DIR)/preprocessing $(SRC_DIR)/stats $(SRC_DIR)/utils
INCDIRS=./include ./src $(GSLPATH)/include
LIBDIRS=-L$(GSLPATH)/lib

CC=gcc
OPT=-O0
DEPFLAGS=-MD -MP
CFLAGS=-Wall -Wextra -g -std=c11 $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS) -lm -lgsl -lgslcblas $(LIBDIRS)

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))

OBJECTS=$(patsubst %.c,%.o,$(CFILES))
# OBJECTS=$(foreach D,$(CFILES),$(OUT_DIR)/$(patsubst %.c,%.o,$(notdir $(D))))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

.PHONY: all
all: $(SHARED_LIB)

$(SHARED_LIB): $(OBJECTS)
	mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

.PHONY: diff
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(DEPFILES) $(OBJECTS)

# include the dependencies
-include $(DEPFILES)
