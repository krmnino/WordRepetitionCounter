CXX = g++
CXXFLAGS = -g -Wall -std=c++17

TARGET = wordcounts

OFILES = WordRepetitionCounter.o

$(TARGET): 	$(OFILES)
			$(CXX) $(CXXFLAGS) $(OFILES) -o $(TARGET)

$(OFILES):	WordRepetitionCounter.cpp
			$(CXX) $(CXXFLAGS) -c $<

clean:
		rm -f *.o $(TARGET)
