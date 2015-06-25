CPP = clang++

CFLAGS = -Wall -std=c++11 -O2 -I sdl
LFLAGS = -lSDL2 -lm

OBJS = sdl/Esplora.o main.o renderer.o viewpoint.o

ALL: $(OBJS)
	$(CPP) $(CFLAGS) $(LFLAGS) $(OBJS) -o main

%.o: %.cpp %.h
	$(CPP) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)