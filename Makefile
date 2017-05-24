#
# Makefile
# Kovid Goyal, 2017-05-22 11:19
#

BUILD=build
EXE=$(BUILD)/subseq-matcher
CCFLAGS=$(CFLAGS) -pthread -std=c99 -I./$(BUILD) -I. -Wall -Werror -O3
CLI=cli
SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJ=$(CLI).o $(patsubst %.c,%.o,$(SOURCES))
OBJECTS=$(addprefix $(BUILD)/,$(OBJ))

all: $(EXE)

debug: CCFLAGS += -DDEBUG -ggdb
debug: $(EXE)

%.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

$(BUILD)/%.o: %.c $(HEADERS)
	$(CC) -c $(CCFLAGS) $< -o $@

# The code generated by gengetopt has unused variables
$(BUILD)/cli.o: $(BUILD)/cli.c
	$(CC) -c $(CCFLAGS) -Wno-unused-but-set-variable $< -o $@

$(BUILD)/$(CLI).c: $(CLI).ggo
	mkdir -p build
	gengetopt -i $(CLI).ggo -F $(BUILD)/$(CLI) -u --default-optional

show-help: $(CLI).ggo
	gengetopt -i $(CLI).ggo --show-help --default-optional

$(EXE): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(EXE)

clean:
	rm -rf $(BUILD)


# vim:ft=make
