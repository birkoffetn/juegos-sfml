SOURCES= $(wildcard *.cpp)
OBJECTS= $(SOURCES:.cpp=.o)
DEPENDENCIES= $(SOURCES:.cpp=.d)
TARGET= sokoban

CXXFLAGS= -ggdb -Wall -Wextra -std=c++11
LDLIBS= -lsfml-graphics -lsfml-window -lsfml-system
CC= $(CXX)

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(DEPENDENCIES) $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDLIBS)

%.d: %.cpp
	$(CXX) -MM $< -o $@

-include $(DEPENDENCIES)

clean:
	rm -f $(DEPENDENCIES) $(TARGET) $(OBJECTS)
