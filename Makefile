shell: build/main.o build/tcl.o build/readline.o
	gcc -g build/main.o build/tcl.o build/readline.o -o $@ -ltcl -lreadline

build/main.o: 
	mkdir -p build
	gcc -c -g src/main.c  -o $@

build/tcl.o: 
	mkdir -p build/tcl
	gcc -c -g src/tcl/tcl.c  -o $@

build/readline.o: 
	mkdir -p build/readline
	gcc -c -g src/readline/readline.c -o $@

.PHONY: clean

clean:
	rm -f build/*.o build/tcl/*.o build/readline/*.o
	rm -rf build
	rm -f shell