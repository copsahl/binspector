binspector: main.o
	gcc main.o -lbfd -o binspector

main.o: main.c
	gcc -c main.c -llbfd

clean:
	rm main.o binspector
