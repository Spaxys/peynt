CXX = g++
CXXFLAGS = -Wall -std=c++11
LDLIBS = -lglfw -lGL

OBJ_DIR = obj
LIB_DIR = -L/usr/local/lib
INC_DIR = -I/usr/include

SOURCE = main.cpp
OBJECTS = ${SOURCE:%.cpp=$(OBJ_DIR)/%.o}
EXECUTABLE = hello

all: init $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE):
	$(CXX) $(LDFLAGS) $(LIB_DIR) -o $@ $(OBJECTS) $(LDLIBS)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(INC_DIR) -c $< -o $@

init:
	@mkdir -p "$(OBJ_DIR)"

clean:
	@rm -rf $(OBJ_DIR) $(EXECUTABLE)
