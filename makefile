CC = gcc
CFLAGS = -Wall
LIBS = -lSDL
MAIN = alarm

all: $(MAIN)
	
clean:
	rm -f $(MAIN)
	rm *.o

alarmsound.o:
	$(CC) $(CFLAGS) $(LIBS) -c alarmsound.c
	
alarm.o: alarmsound.o
	$(CC) $(CFLAGS) -c alarm.c
	
$(MAIN): alarm.o
	$(CC) $(CFLAGS) $(LIBS) -o $(MAIN) alarm.o alarmsound.o
