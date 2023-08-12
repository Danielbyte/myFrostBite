#compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall

#SFML Settings
SFML_INCLUDE = -I/usr/include/SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#Directories
SRC_DIR = game-source-code/Source-files
HEADER_DIR = include

#Source file and output executable
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = frostbite

#Targets and rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(EXECUTABLE)
