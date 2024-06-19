all:
	gcc -Wall -Wextra -c -o matriz.o matriz.c -pthread
	gcc -Wall -Wextra -c -o main.o main.c -pthread
	gcc -o programa.exe main.o matriz.o

run: 
	./programa.exe 2 1000 arq1.dat arq2.dat arq3.dat arq4.dat arq5.dat

clean:
	rm -rf ./*.o ./*.exe ./arq4.dat ./arq5.dat