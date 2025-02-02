LIB_NAME = libimgui.a
CXX = g++
CXXFLAGS = -Wall -Wextra -O2

SRC_DIR = src

INCLUDE = 	-I include \
			-I ../include
LIB = 	-L ../lib/linux_x86/ \
		-l SDL3

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))


all: $(LIB_NAME)

$(LIB_NAME): $(OBJ_FILES)
	ar rcs $@ $^

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) ${INCLUDE} -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(LIB_NAME)

.PHONY: all clean