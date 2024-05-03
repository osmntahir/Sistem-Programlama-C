all: program run clean
program: main.c
	cd Libfdr/ && make
	gcc -g -o program main.c Libfdr/lib/libfdr.a -lm
run: program
	./program
clean:
	rm -f program
