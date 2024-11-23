all: create_build_dir build/proc

create_build_dir:
	mkdir build || exit 0

build/proc: build/procLib.o build/double_linked_list.o build/prog.o
	gcc build/prog.o build/procLib.o build/double_linked_list.o -o build/proc

build/double_linked_list.o: src/double_linked_list.c
	gcc -c src/double_linked_list.c -o build/double_linked_list.o -Iinclude

build/procLib.o: src/procLib.c
	gcc -c src/procLib.c -o build/procLib.o -Iinclude

build/prog.o: src/prog.c
	gcc -c src/prog.c -o build/prog.o -Iinclude
