SOURCES:= $(wildcard src/*.c)
OBJECTS:= $(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

BIN_DIR:=bin
OBJ_DIR:=obj

CFLAGS:= -c -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -isystem include/SDL2 -Iinclude
LDFLAGS:= -Llib
LDLIBS:= -lSDL2 #-lSDL2_image

EXECUTABLE:= $(BIN_DIR)/sdl_test

# Instantly runs the game after linking
$(EXECUTABLE):  $(OBJECTS) | bin
	@echo "Linking..."
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
	@echo "Linking for target $(EXECUTABLE) succeeded!"

obj/%.o: src/%.c | obj
	@echo "Compiling:"
	$(CC) $(CFLAGS) -o $@ $<


bin:
	@echo "Creating Output Directory:"
	mkdir $(BIN_DIR)

obj:
	@echo "Creating Object Directory:"
	mkdir $(OBJ_DIR)

.PHONY: clean run

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	-rm -r $(OBJ_DIR)
	-rm -r $(BIN_DIR)