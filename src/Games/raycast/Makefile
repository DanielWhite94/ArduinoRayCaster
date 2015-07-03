CPP = clang++

CFLAGS = -Wall -std=c++11 -O2 -I../../sdl
LFLAGS = -lSDL2 -lm -lSDL2_gfx

OBJS = ../../sdl/Esplora.o colour.o fixed.o main.o ray.o renderer.o viewpoint.o

ALL: $(OBJS)
	$(CPP) $(CFLAGS) $(LFLAGS) $(OBJS) -o main

extra:
	make CFLAGS="$(CFLAGS) -DEXTRA"

%.o: %.cpp %.h
	$(CPP) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)