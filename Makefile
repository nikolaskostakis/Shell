shell: build/main.o build/tcl.o build/readline.o build/ui.o
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

.PHONY: clean

clean:
	rm -f build/*.o build/tcl/*.o build/readline/*.o build/ui/*.o
	rm -rf build
	rm -f shell