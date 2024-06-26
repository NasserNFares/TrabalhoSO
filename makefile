DIR100 = matriz100_100
DIR1000 = matriz1000_1000

all:
	gcc -Wall -Wextra -c -o auxFunc.o auxFunc.c -pthread 
	gcc -Wall -Wextra -c -o matriz.o matriz.c -pthread
	gcc -Wall -Wextra -c -o main.o main.c -pthread
	gcc -o programa.exe auxFunc.o matriz.o main.o

matriz100: 
	./programa.exe 1 100 $(DIR100)/arq1.dat $(DIR100)/arq2.dat $(DIR100)/arq3.dat $(DIR100)/arq4.dat $(DIR100)/arq5.dat

matriz1000:
	./programa.exe 4 1000 $(DIR1000)/arq1.dat $(DIR1000)/arq2.dat $(DIR1000)/arq3.dat $(DIR1000)/arq4.dat $(DIR1000)/arq5.dat

clean:
	rm -rf ./*.o ./*.exe $(DIR100)/arq4.dat $(DIR100)/arq5.dat $(DIR1000)/arq4.dat $(DIR1000)/arq5.dat