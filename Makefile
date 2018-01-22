CFLAGS = -g -Wall `pkg-config --cflags MLV`

main: main.o functions.o
	gcc -o main functions.o main.o `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` `pkg-config --libs-only-l MLV`

main.o: main.c functions.h
	gcc -o main.o -c main.c $(CFLAGS)

functions.o: functions.c
	gcc -o functions.o -c $< $(CFLAGS)
	# gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` functions.c `pkg-config --libs-only-l MLV` -o functions.o