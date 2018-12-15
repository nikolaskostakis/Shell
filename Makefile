CC = gcc
OBJ = build/main.o build/tcl.o build/readline.o build/ui.o build/io.o build/structures.o build/placement.o build/cubes.o build/sta.o

# Compilations
# Create executable
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

build/ui.o: src/ui/ui.c src/ui/ui.h
	@ mkdir -p build/ui
	$(CC) -c -g `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gthread-2.0` src/ui/ui.c -o $@ -lm `pkg-config --libs gtk+-2.0` `pkg-config --libs gthread-2.0`

build/io.o: src/io/io.c src/io/io.h
	@ mkdir -p build/io
	$(CC) -c -g src/io/io.c -o $@

build/structures.o: src/structures/structures.c src/structures/structures.h
	@ mkdir -p build/structures
	$(CC) -c -g src/structures/structures.c -o $@

build/placement.o: src/placement/placement.c src/placement/placement.h
	@ mkdir -p build/placement
	$(CC) -c -g src/placement/placement.c -o $@

build/cubes.o: src/cubes/cubes.c src/cubes/cubes.h
	@ mkdir -p build/cubes
	$(CC) -c -g src/cubes/cubes.c -o $@

build/sta.o: src/sta/sta.c src/sta/sta.h
	@ mkdir -p build/sta
	$(CC) -c -g src/sta/sta.c -o $@

.PHONY: clean clean_build clean_shell new

# Remove objects
clean_build:
	@ rm -f build/*.o build/tcl/*.o build/readline/*.o build/ui/*.o build/io/*.o build/structures/*.o build/placement/*.o build/cubes/*.o build/sta/*.o
	@ rm -rf build/tcl build/readline build/ui build/io build/structures build/placement build/cubes build/sta
	rm -rf build/

# Remove executable
clean_shell:
	rm -f shell

# Remove objects and executable 
clean: clean_build clean_shell

# Remove objects, executable and create new executable
new: clean shell
