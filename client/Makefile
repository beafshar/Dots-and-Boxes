all: Client

Client: Client.o Map.o Tools.o
	gcc Client.o Map.o Tools.o -o Client

Client.o: Client.c Map.h
	gcc -c Client.c

Map.o: Map.c Map.h
	gcc -c Map.c


Tools.o: Tools.c Map.h
	gcc -c Tools.c


clean:
	rm *.o
	rm game.out