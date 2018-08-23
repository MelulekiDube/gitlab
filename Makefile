#Make file for project_maker
#Created on: Thu Feb 19 00:18:08 1970

#Meluleki Dube
CPP =g++
CPPFLAGS =-std=c++11
TARGET=pca
SRCDIR =src
BINDIR =bin
OBJECT =objects
SRC=$(SRCDIR)/main.cpp
OBJECTS=$(OBJECT)/main.o 


$(TARGET): $(OBJECTS)
	$(CPP) $(OBJECTS)-o $@ $(CPPFLAGS)
	@mv $(TARGET) $(BINDIR)

$(OBJECTS): $(SRC)
	$(CPP) $< -c $(SRC) $(CPPFLAGS)
	@mv *.o $(OBJECT)

run:
	./$(BINDIR)/$(TARGET)

clean:
	@rm -f -r *.o $(OBJECT)/*.o *.exe *.out $(BINDIR)/*

# end of Makefile