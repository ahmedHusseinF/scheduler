CC=g++
CFLAGS=-I. -g
GENDEPS = includes/common.hpp includes/generator.hpp
SCHDEPS = includes/common.hpp includes/scheduler.hpp
GENOBJ = src/genMain.o src/generator.o 
SCHOBJ = src/schMain.o src/scheduler.o

%.o: %.c $(GENDEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

generator: $(GENOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(SCHDEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

scheduler: $(SCHOBJ)
	$(CC) -o $@ $^ $(CFLAGS)