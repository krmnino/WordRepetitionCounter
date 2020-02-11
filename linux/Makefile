CXX = g++
CSSFLAGS = -g -Wall -std=c++17

OFILES = main.o

TARGET = wordcounts

all:		$(TARGET)
$(TARGET):	$(OFILES)
		$(CXX) $(OFILES) -o $@

clean:
		rm -f *.o $(TARGET)
