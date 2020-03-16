main:main.o dep1.o dep2.o
	gcc main.o dep1.o dep2.o -o main
main.o: main.c main.h dep1.h dep2.h
	gcc -c main.c -o main.o
dep1.o: dep1.c dep1.h
	gcc -c dep1.c -o dep1.o
dep2.o : dep2.c dep2.h
	gcc -c dep2.c -o dep2.o

clean:
	@echo "cleanning project"
	rm main *.o
	@echo "clean completed"

