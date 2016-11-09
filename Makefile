all: linked.o concurrency.o
	gcc linked.o concurrency.o -o a.out -lpthread -lrt -lm
	
linked.o: linked.c
	gcc linked.c -c -lpthreat -lrt -lm

concurrency.o: concurrency.c
	gcc concurrency.c -c -lpthread -lrt -lm

clean:
	rm -f *.out *.o
