# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = sfml-app

# Build rule
$(TARGET): main.o
	$(CXX) main.o -o $(TARGET) $(LDFLAGS)

# Compile main.cpp → main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean compiled files
clean:
	rm -f *.o $(TARGET)

# Run the program (after building)
run: $(TARGET)
	./$(TARGET)
