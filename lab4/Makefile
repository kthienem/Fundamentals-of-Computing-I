part2: part2main.o part2fn.o
	gcc part2main.o part2fn.o -lm -o part2

part2main.o: part2main.c part2fn.h
	gcc -c part2main.c

part2fn.o: part2fn.c
	gcc -c part2fn.c

clean:
	rm *.o part2
