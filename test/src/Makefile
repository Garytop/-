CC = g++
CXX = g++
CPPFLAGS = -I../include -std=c++11 -Wall -Wextra -g
LDFLAGS = -std=c++11
LDLIBS = -lpng

EXENAME = part1 part2 part3 test

.PHONY : clean TAGS

all : $(EXENAME)
	mv $(EXENAME) ../

part1 : suan_png.o pxl.o state.o

part2 : suan_png.o pxl.o state.o

part3 : suan_png.o pxl.o state.o

clean :
	-rm -rf *.o *.dSYM $(EXENAME)

TAGS : clean all
