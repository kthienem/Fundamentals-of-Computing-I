asteroid: asteroid.o gfx3.o
	gcc asteroid.o gfx3.o -lm -lX11 -o asteroid

asteroid.o: asteroid.c gfx3.h
	gcc -c asteroid.c

gfx3.o: gfx3.h
	gcc -c gfx3.c

clean:
	rm *.0 asteroid
