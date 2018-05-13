CC = gcc
OBJ = build/main.o build/tcl.o build/readline.o build/ui.o build/parser.o build/structures.o

shell: $(OBJ)
	$(CC) -g `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gthread-2.0` $(OBJ) -o $@ -ltcl8.5 -lreadline -lm `pkg-config --libs gtk+-2.0` `pkg-config --libs gthread-2.0`

build/main.o: src/main.c src/main.h
	@ mkdir -p build
	$(CC) -c -g `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gthread-2.0` src/main.c -o $@ `pkg-config --libs gtk+-2.0` `pkg-config --libs gthread-2.0`

build/tcl.o: src/tcl/tcl.c src/tcl/tcl.h
	@ mkdir -p build/tcl
	$(CC) -c -g src/tcl/tcl.c -o $@

build/readline.o: src/readline/readline.c src/readline/readline.h
	@ mkdir -p build/readline
	$(CC) -c -g src/readline/readline.c -o $@

build/ui.o: src/ui/ui-scrolled-canvas-skeleton.c src/ui/ui-scrolled-canvas-skeleton.h
	@ mkdir -p build/ui
	$(CC) -c -g `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gthread-2.0` src/ui/ui-scrolled-canvas-skeleton.c -o $@ -lm `pkg-config --libs gtk+-2.0` `pkg-config --libs gthread-2.0`

build/parser.o: src/parser/parser.c src/parser/parser.h
	@ mkdir -p build/parser
	$(CC) -c -g src/parser/parser.c -o $@

build/structures.o: src/structures/structures.c src/structures/structures.h
	@ mkdir -p build/structures
	$(CC) -c -g src/structures/structures.c -o $@

.PHONY: clean clean_build clean_shell

clean_build:
	@ rm -f build/*.o build/tcl/*.o build/readline/*.o build/ui/*.o build/parser/*.o build/structures/*.o
	@ rm -rf build/tcl build/readline build/ui build/parser build/structures
	rm -rf build/

clean_shell:
	rm -f shell

clean: clean_build clean_shell
