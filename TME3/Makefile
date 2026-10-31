all:main

main : main.o entreeSortirLC.o biblioLC.o
	gcc -o main main.o entreeSortirLC.o biblioLC.o

main.o : main.c biblioLC.h entreeSortirLC.h
	gcc -c main.c

entreeSortirLC.o : entreeSortirLC.h entreeSortirLC.c biblioLC.h
	gcc -c entreeSortirLC.c

biblioLC.o: biblioLC.c biblioLC.h
	gcc -c biblioLC.c

clean:
	rm -f main *.o