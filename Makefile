binspector: main.o argparse/argparse.o
	gcc main.o argparse/argparse.o -lbfd -o binspector

main.o: main.c
	gcc -c main.c -llbfd

argparse.o: argparse/argparse.c argparse/argparse.h
	gcc -c argparse/argparse.c

clean:
	rm main.o argparse/argparse.o binspector
