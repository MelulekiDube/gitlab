#Make file for project_maker
#Created on: Thu Feb 19 00:18:08 1970

#Meluleki Dube
CPP =g++
CPPFLAGS =-std=c++11
TARGET=pca.out
SRCDIR =src
BINDIR =bin
SRC=$(SRCDIR)/main.cpp
OBJECTS=$(BINDIR)/main.o 


$(TARGET): $(OBJECTS)
	$(CPP) $(OBJECTS)-o $@ $(CPPFLAGS)

$(OBJECTS): $(SRC)
	$(CPP) $< -c $(SRC) $(CPPFLAGS)
	@mv *.o $(BINDIR)

run:
	./$(TARGET)

clean:
	@rm -f -r *.o bin/*.o *.exe *.out

# end of Makefile