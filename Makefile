shell: build/main.o build/tcl.o build/readline.o build/ui.o build/parser.o
	gcc -g `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gthread-2.0` build/main.o build/tcl.o build/readline.o build/ui.o -o $@ -ltcl8.5 -lreadline -lm `pkg-config --libs gtk+-2.0` `pkg-config --libs gthread-2.0`

build/main.o: src/main.c src/main.h
	mkdir -p build
	gcc -c -g `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gthread-2.0` src/main.c -o $@ `pkg-config --libs gtk+-2.0` `pkg-config --libs gthread-2.0`

build/tcl.o: src/tcl/tcl.c src/tcl/tcl.h
	mkdir -p build/tcl
	gcc -c -g src/tcl/tcl.c -o $@

build/readline.o: src/readline/readline.c src/readline/readline.h
	mkdir -p build/readline
	gcc -c -g src/readline/readline.c -o $@

build/ui.o: src/ui/ui-scrolled-canvas-skeleton.c src/ui/ui-scrolled-canvas-skeleton.h
	mkdir -p build/ui
	gcc -c -g `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gthread-2.0` src/ui/ui-scrolled-canvas-skeleton.c -o $@ -lm `pkg-config --libs gtk+-2.0` `pkg-config --libs gthread-2.0`

build/parser.o: src/parser/parser.c src/parser/parser.h
	mkdir -p build/parser
	gcc -c -g src/parser/parser.c -o $@

.PHONY: clean clean_build clean_shell

clean_build:
	rm -f build/*.o build/tcl/*.o build/readline/*.o build/ui/*.o src/parser/*.o
	rm -rf build/tcl build/readline build/ui src/parser
	rm -rf build

clean_shell:
	rm -f shell

clean: clean_build clean_shell
	